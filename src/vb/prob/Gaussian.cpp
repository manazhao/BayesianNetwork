/*
 * Gaussian.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: qzhao2
 */

#include "Gaussian.h"

namespace prob {

void Gaussian::reset() {
	m_mean = 0;
	m_var = 0;
	m_is_canonical = true;
}

Gaussian::moment_type Gaussian::moment(size_t const& order) {
	assert(order == 1 || order == 2);
	to_non_canomical();
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

Gaussian::Gaussian(DistParamBundle const& paramBundle) {
	m_is_canonical = paramBundle.m_is_canonical;
	assert(paramBundle.m_num_params == 2);
	m_mean = (float)paramBundle[0];
	m_var = (float)paramBundle[1];
	m_is_updated = true;
}

Gaussian& Gaussian::operator=(DistParamBundle const& paramBundle) {
	m_is_canonical = paramBundle.m_is_canonical;
	assert(paramBundle.m_num_params == 2);
	m_mean = (float)(paramBundle[0]);
	m_var = (float)paramBundle[1];
	m_is_updated = true;
	return *this;
}

Gaussian::operator DistParamBundle() const {
	DistParamBundle pb(2,m_is_canonical);
	pb[0] = m_mean;
	pb[1] = m_var;
	return pb;
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

