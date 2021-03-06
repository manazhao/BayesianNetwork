/*
 * MVInverseGamma.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: qzhao2
 */

#include "MVInverseGamma.h"
#include <boost/math/special_functions/digamma.hpp>

namespace prob {

MVInverseGamma::MVInverseGamma(DistParamBundle const& paramBundle):m_dim(0){
	m_is_canonical = paramBundle.m_is_canonical;
	assert(paramBundle.size() == 2);
	m_dim = paramBundle[0].size();
	vec alpha = paramBundle[0];
	vec beta = paramBundle[1];
	m_alpha_vec = alpha;
	m_beta_vec = beta;
	m_ss_cache = mat(m_dim,2);
	m_is_updated = true;
}

void MVInverseGamma::to_non_canonical() {
	if (m_is_canonical) {
		(*this) = !(*this);
	}
}
void MVInverseGamma::reset() {
	m_alpha_vec.fill(0);
	m_beta_vec.fill(0);
	m_is_canonical = true;
	m_is_updated = true;
}

/**
 * \brief return the first and second  moments of x
 *
 * the first moment(mean value of x) is computed as,
 * moment(x,1) = (\beta)/(\alpha - 1) in original parameters or
 * moment(x,1) = (\eta_2)/(\eta_1 + 1) in canonical natural parameter
 *
 * the second moment(expectation of x^2) is computed as,
 * moment(x,2) = moment(x,1)^2 + \beta^2/((\alpha-1)^2(\alpha-2)) in original parameter or
 * moment(x,2) = moment(x,1)^2 + \eta_2^2/((\eta_1+2)^2(\eta_1+3)) in canonical parameters
 */
MVInverseGamma::moment_type MVInverseGamma::moment(size_t const& order) {
	assert(order == 1 || order == 2);
	vec mVal;
	if (is_observed()) {
		/// simply return the value itself
		switch (order) {
		case 1:
			mVal = m_value;
			break;
		case 2:
			mVal = m_value % m_value;
			break;
		}
	} else {
		to_non_canonical();
		vec& a = m_alpha_vec;
		vec& b = m_beta_vec;
		switch (order) {
		case 1:
			mVal = b / (a - 1);
			break;
		case 2:
			mVal = (b % b) / ((a - 1) % (a - 2));
			break;
		}
	}
	return DistParam(mVal);
}

/**
 * \brief calculate the expectation of the sufficient statistics where are
 * [ln(x),1/x]
 *
 * the expectation of the sufficient statiscs are computed as,
 * E(ln(x)) = ln(\alpha) - digamma(\beta) (Note: digamma is the logarithm gamma derivative, namely, digamma(x) = gamma'(x)/gamma(x)
 * E(1/x) = \alpha/\beta
 */
MVInverseGamma::suff_mean_type MVInverseGamma::suff_mean(size_t const& idx) {
	assert(idx == 1 || idx == 2);
	updateSSCache();
	return vec(m_ss_cache.col(idx - 1));
}

void MVInverseGamma::updateSSCache(){
	if(m_is_updated){
		if(is_observed()){
			m_ss_cache.col(0) = log(m_value);
			m_ss_cache.col(1) = 1/m_value;
		}else{
			to_non_canonical();
			vec& a = m_alpha_vec;
			vec& b = m_beta_vec;
			for(size_t i = 0; i < m_alpha_vec.size(); i++){
				m_ss_cache(i,0) = log(b(i)) - boost::math::digamma(a(i));
			}
			m_ss_cache.col(1) = a / b;
		}
		m_is_updated = false;
	}
}


MVInverseGamma& MVInverseGamma::operator=(DistParamBundle const& paramBundle) {
	assert(paramBundle.size() == 2);
	m_is_canonical = paramBundle.m_is_canonical;
	vec alpha = paramBundle[0];
	vec beta = paramBundle[1];
	m_alpha_vec = alpha;
	m_beta_vec = beta;
	m_is_updated = true;
	return *this;
}

MVInverseGamma::operator DistParamBundle()const {
	DistParamBundle pb(2,m_is_canonical);
	pb[0] = m_alpha_vec;
	pb[1] = m_beta_vec;
	return pb;
}

 MVInverseGamma MVInverseGamma::operator!() const {
	MVInverseGamma invParam(*this);
	invParam.m_is_canonical = !m_is_canonical;
	invParam.m_alpha_vec = -m_alpha_vec - 1;
	invParam.m_beta_vec = -m_beta_vec;
	return invParam;
}

MVInverseGamma MVInverseGamma::operator+(MVInverseGamma const& rhs) const {
	MVInverseGamma resultParam = (m_is_canonical ? *this : !(*this));
	MVInverseGamma rhs1 = (rhs.m_is_canonical ? rhs : !rhs);
	resultParam.m_alpha_vec += rhs1.m_alpha_vec;
	resultParam.m_beta_vec += rhs1.m_beta_vec;
	resultParam.m_is_updated = true;
	return resultParam;
}

MVInverseGamma& MVInverseGamma::operator+=(MVInverseGamma const& rhs) {
	(*this) = (*this) + rhs;
	return *this;
}

ostream& operator<<(ostream& oss, MVInverseGamma const& dist){
	oss << "-----------------------------------------" << endl;
	oss << "alpha: " << (DistParam)dist.m_alpha_vec << ", beta:" << (DistParam)dist.m_beta_vec
			<< ", is natural:" << dist.m_is_canonical << endl;
	oss << "-----------  moment ----------------" << endl;
	MVInverseGamma& dist1 = const_cast<MVInverseGamma&>(dist);
	for (size_t i = 1; i <= 2; i++) {
		oss << i << " moment:" << dist1.moment(i) << endl;
	}
	oss << "-----------  ss mean ----------------" << endl;
	for (size_t i = 1; i <= 2; i++) {
		oss << i << " ss:" << dist1.suff_mean(i) << endl;
	}
	return oss;

}

} /* namespace prob */
