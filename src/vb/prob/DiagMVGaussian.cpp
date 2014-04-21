/*
 * DiagMVGaussian.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: manazhao
 */

#include "DiagMVGaussian.h"

namespace prob {

void DiagMVGaussian::reset() {
	m_mean.fill(0);
	m_cov.fill(0);
	m_is_canonical = true;
	m_is_updated = true;
}

void DiagMVGaussian::to_non_canonical() {
	if (m_is_canonical) {
		(*this) = !(*this);
	}
}

DiagMVGaussian::moment_type DiagMVGaussian::moment(size_t const& order) {
	assert(order == 1 || order == 2);
	moment_type mVal;
	to_non_canonical();
	switch (order) {
	case 1:
		if (is_observed()) {
			mVal = m_value;
		} else {
			mVal = m_mean;
		}
		break;
	case 2:
		if (is_observed()) {
			if (m_cache_suff) {
				/// try to use the cached result
				if (m_is_updated) {
					m_som_cache = vectorise(m_value * m_value.t());
				}
				mVal = (vec) vectorise(m_som_cache);
			} else {
				/// evaluate the second order moment
				mVal = (vec) vectorise(m_value * m_value.t());
			}
		} else {
			if (m_cache_suff) {
				if (m_is_updated) {
					m_som_cache = vectorise(m_mean * m_mean.t()
							+ arma::diagmat(m_cov));
				}
				mVal = (vec) vectorise(m_som_cache);
			} else {
				mVal = (vec) vectorise(m_mean * m_mean.t() + arma::diagmat(
						m_cov));
			}
		}
		break;
	}
	return mVal;
}

/**
 * \brief return the expectation of sufficient statistics which are
 * [x, xx^T]. Let K be the mean vector dimension, the result is
 * K*(K+1) dimension vector
 */

DiagMVGaussian::suff_mean_type DiagMVGaussian::suff_mean(size_t const& idx) {
	return moment(idx);
}

DiagMVGaussian::DiagMVGaussian(DistParamBundle const& paramBundle) {
	m_is_canonical = paramBundle.m_is_canonical;
	DistParam const& firstComponent = paramBundle[0];
	DistParam const& secondComponent = paramBundle[1];
	size_t dim = firstComponent.size();
	///the second component could be a full covariance matrix
	if (m_is_canonical && secondComponent.size() == dim * dim) {
		mat covMat(secondComponent.m_vec);
		covMat.reshape(dim, dim);
		mat covMatInv = -0.5 * inv(covMat);
		vec mean = firstComponent;
		m_mean = covMatInv * mean;
		m_cov = covMatInv.diag();
		m_is_canonical = false;
	}else if(secondComponent.size() == dim * dim){
		/// only keep the diagonal elements
		vec mean = paramBundle[0];
		m_mean = mean;
		vec cov = paramBundle[1];
		mat covMat(cov);
		covMat.reshape(dim,dim);
		/// drop the off diagonal elements
		m_cov = mat(cov).diag();
	}else{
		vec mean = paramBundle[0];
		vec cov = paramBundle[1];
		m_mean = mean;
		m_cov = cov;
	}
	m_is_updated = true;
}

DiagMVGaussian& DiagMVGaussian::operator=(DistParamBundle const& paramBundle) {
	DiagMVGaussian mvg(paramBundle);
	*this = mvg;
	return *this;
}

DiagMVGaussian::operator DistParamBundle() const{
	DistParamBundle pb(2,m_is_updated);
	pb[0] = m_mean;
	pb[1] = m_cov;
	return pb;
}

DiagMVGaussian DiagMVGaussian::operator!() const {
	DiagMVGaussian invParam(*this);
	invParam.m_is_canonical = !m_is_canonical;
	if (m_is_canonical) {
		/// simply elementwise division
		invParam.m_cov = -0.5 / m_cov;
		/// elementwise multiplication
		invParam.m_mean = invParam.m_cov % m_mean;
	} else {
		invParam.m_cov = 1 / m_cov;
		invParam.m_mean = invParam.m_cov % m_mean;
		invParam.m_cov *= -0.5;
	}
	return invParam;
}

DiagMVGaussian DiagMVGaussian::operator+(DiagMVGaussian const& rhs) const {
	DiagMVGaussian resultParam = (m_is_canonical ? *this : !(*this));
	DiagMVGaussian rhs1 = (rhs.m_is_canonical ? rhs : !rhs);
	resultParam.m_mean += rhs1.m_mean;
	resultParam.m_cov += rhs1.m_cov;
	resultParam.m_is_updated = true;
	return resultParam;
}

DiagMVGaussian& DiagMVGaussian::operator+=(DiagMVGaussian const& rhs) {
	(*this) = (*this) + rhs;
	return *this;
}

ostream& operator<<(ostream& oss, DiagMVGaussian const& dist) {
	oss << "-----------------------------------------" << endl;
	oss << "mean:" << (DistParam) dist.m_mean << endl << "var:"
			<< (DistParam) dist.m_cov << endl << "is canonical:"
			<< dist.m_is_canonical << endl;
	oss << "moment >>>" << endl;
	DiagMVGaussian& dist1 = const_cast<DiagMVGaussian&>(dist);
	for (size_t i = 1; i <= 2; i++) {
		oss << i << " moment:" << (DistParam) dist1.moment(i) << endl;
	}
	return oss;
}


}
