/*
 * MVGaussian.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: manazhao
 */

#include "MVGaussian.h"

namespace prob {

void MVGaussian::reset() {
	m_mean.fill(0);
	m_cov.fill(0);
	m_is_canonical = true;
	m_is_updated = true;
}

void MVGaussian::to_non_canonical() {
	if (m_is_canonical) {
		(*this) = !(*this);
	}
}

MVGaussian::moment_type MVGaussian::moment(size_t const& order) {
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
			if(m_cache_suff){
				/// try to use the cached result
				if(m_is_updated){
					m_som_cache = vectorise(m_value * m_value.t());
					m_is_updated = false;
				}
				mVal = (vec)vectorise(m_som_cache);
			}else{
				/// evaluate the second order moment
				mVal = (vec)vectorise(m_value * m_value.t());
			}
		} else {
			if(m_cache_suff){
				if(m_is_updated){
					m_som_cache = vectorise(m_mean * m_mean.t() + m_cov);
					m_is_updated = false;
				}
				mVal = (vec)vectorise(m_som_cache);
			}else{
				mVal = (vec)vectorise(m_mean * m_mean.t() + m_cov);
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

MVGaussian::suff_mean_type MVGaussian::suff_mean(size_t const& idx) {
	return moment(idx);
}

MVGaussian::MVGaussian(DistParamBundle const& paramBundle) {
	m_is_canonical = paramBundle.m_is_canonical;
	vec mean = paramBundle[0];
	vec cov = paramBundle[1];
	m_mean = mean;
	m_cov = cov;
	m_is_updated = true;
}

MVGaussian& MVGaussian::operator=(DistParamBundle const& paramBundle) {
	MVGaussian mvg(paramBundle);
	*this = mvg;
	return *this;
}

MVGaussian::operator DistParamBundle() const{
	size_t dim = m_mean.size();
	vec flatVec(dim * (dim + 1));
	DistParamBundle fp(2,m_is_canonical);
	fp[0] = m_mean;
	fp[1] = m_cov;
	return fp;
}

MVGaussian MVGaussian::operator!() const {
	MVGaussian invParam(*this);
	invParam.m_is_canonical = !m_is_canonical;
	if (m_is_canonical) {
		/// simply elementwise division
		invParam.m_cov = -0.5 * inv(m_cov);
		/// elementwise multiplication
		invParam.m_mean = invParam.m_cov * m_mean;
	} else {
		invParam.m_cov = inv(m_cov);
		invParam.m_mean = invParam.m_cov * m_mean;
		invParam.m_cov *= -0.5;
	}
	return invParam;
}

MVGaussian MVGaussian::operator+(MVGaussian const& rhs) const {
	MVGaussian resultParam = (m_is_canonical ? *this : !(*this));
	MVGaussian rhs1 = (rhs.m_is_canonical ? rhs : !rhs);
	resultParam.m_mean += rhs1.m_mean;
	resultParam.m_cov += rhs1.m_cov;
	resultParam.m_is_updated = true;
	return resultParam;
}

MVGaussian& MVGaussian::operator+=(MVGaussian const& rhs) {
	(*this) = (*this) + rhs;
	return *this;
}

MVGaussian::~MVGaussian() {
	// TODO Auto-generated destructor stub
}

}
