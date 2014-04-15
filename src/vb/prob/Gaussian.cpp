/*
 * Gaussian.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: qzhao2
 */

#include "Gaussian.h"

namespace prob {

void DiagMVGaussian::reset() {
	m_mean.fill(0);
	m_cov.fill(0);
	m_is_canonical = true;
	m_is_updated = true;
}

vec DiagMVGaussian::updateSSCache() {
	if (m_is_updated) {
		if (is_observed()) {
			m_sm_cache = vectorise(m_value % m_value);
		} else {
			toNonCanonical();
			m_sm_cache = vectorise(m_mean % m_mean + m_cov);
		}
		m_is_updated = false;
	}
	return m_sm_cache;
}

void DiagMVGaussian::toNonCanonical() {
	if (m_is_canonical) {
		(*this) = !(*this);
	}
}

DiagMVGaussian::moment_type DiagMVGaussian::moment(size_t const& order) {
	assert(order == 1 || order == 2);
	moment_type mVal;
	toNonCanonical();
	if(order == 2){
		mVal = updateSSCache();
	}else{
		if(is_observed())
			mVal = m_value;
		else
			mVal = m_mean;
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

DiagMVGaussian::DiagMVGaussian(NatParamVec const& paramVec) {
	m_is_canonical = paramVec.m_is_canonical;
	size_t vecSize = paramVec.m_vec.size();
	/// divide by 2
	size_t probDim = vecSize >> 1;
	m_mean = paramVec.m_vec.rows(0,probDim - 1);
	m_cov = paramVec.m_vec.rows(probDim, 2 * probDim - 1);
	m_is_updated = true;
}

DiagMVGaussian& DiagMVGaussian::operator=(NatParamVec const& paramVec) {
	DiagMVGaussian mvg(paramVec);
	*this = mvg;
	return *this;
}

DiagMVGaussian::operator NatParamVec() {
	vec flatVec(m_mean.size() * 2);
	NatParamVec fp(flatVec, m_is_canonical);
	fp.m_vec.rows(0,m_mean.size() - 1) = m_mean;
	fp.m_vec.rows(m_mean.size(), m_mean.size() * 2 - 1) = m_cov;
	return fp;
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


void Gaussian::reset() {
	m_mean = 0;
	m_var = 0;
	m_is_canonical = true;
}

Gaussian::moment_type Gaussian::moment(size_t const& order) {
	assert(order == 1 || order == 2);
	toNonCanonical();
	moment_type mVal;
	switch (order) {
	case 1:
		mVal = m_mean;
		break;
	case 2:
		mVal = m_mean * m_mean + m_var;
		break;
	}
	return mVal;
}

Gaussian::suff_mean_type Gaussian::suff_mean(size_t const& idx) {
	return moment(idx);
}

Gaussian::Gaussian(NatParamVec const& paramVec) {
	m_is_canonical = paramVec.m_is_canonical;
	if (paramVec.m_vec.size() != 2) {
		throw std::exception();
	}
	m_mean = paramVec.m_vec[0];
	m_var = paramVec.m_vec[1];
	m_is_updated = true;
}

Gaussian& Gaussian::operator=(NatParamVec const& paramVec) {
	m_is_canonical = paramVec.m_is_canonical;
	if (paramVec.m_vec.size() != 2) {
		throw std::exception();
	}
	m_mean = paramVec.m_vec[0];
	m_var = paramVec.m_vec[1];
	m_is_updated = true;
	return *this;
}

Gaussian::operator NatParamVec() {
	NatParamVec fp(vec(2), m_is_canonical);
	fp.m_vec(0) = m_mean;
	fp.m_vec(1) = m_var;
	return fp;
}

Gaussian Gaussian::operator!() const {
	Gaussian invParam(*this);
	invParam.m_is_canonical = !m_is_canonical;
	if (m_is_canonical) {
		invParam.m_var = -0.5 / m_var;
		invParam.m_mean = invParam.m_var * m_mean;
	} else {
		invParam.m_var = 1 / m_var;
		invParam.m_mean = invParam.m_var * m_mean;
		invParam.m_var *= -0.5;
	}
	return invParam;
}

Gaussian Gaussian::operator+(Gaussian const& rhs) const {
	Gaussian resultParam = (m_is_canonical ? *this : !(*this));
	Gaussian rhs1 = (rhs.m_is_canonical ? rhs : !rhs);
	resultParam.m_mean += rhs1.m_mean;
	resultParam.m_var += rhs1.m_var;
	resultParam.m_is_updated = true;
	return resultParam;
}

Gaussian& Gaussian::operator+=(Gaussian const& rhs) {
	(*this) = (*this) + rhs;
	return *this;
}

ostream& operator<<(ostream& oss, DiagMVGaussian const& dist) {
	oss << "-----------------------------------------" << endl;
	oss << "mean:" << (NatParamVec) dist.m_mean << endl << "var:"
			<< (NatParamVec) dist.m_cov << endl << "is canonical:"
			<< dist.m_is_canonical << endl;
	oss << "moment >>>" << endl;
	DiagMVGaussian& dist1 = const_cast<DiagMVGaussian&>(dist);
	for (size_t i = 1; i <= 2; i++) {
		oss << i << " moment:" << (NatParamVec) dist1.moment(i) << endl;
	}
	return oss;
}

ostream& operator<<(ostream& oss, Gaussian const& dist) {
	oss << "-----------------------------------------" << endl;
	oss << "mean:" << endl << dist.m_mean << endl << "var:" << endl
			<< dist.m_var << endl << "is canonical:" << dist.m_is_canonical
			<< endl;
	oss << "-----------  moment ----------------" << endl;
	Gaussian& dist1 = const_cast<Gaussian&>(dist);
	for (size_t i = 1; i <= 2; i++) {
		oss << i << " moment:" << dist1.moment(i) << endl;
	}
	return oss;
}

}

