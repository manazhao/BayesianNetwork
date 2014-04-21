/*
 * InverseGamma.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: qzhao2
 */

#include "InverseGamma.h"

namespace prob {

void test_inverse_gamma() {
	InverseGamma ig(3, 3);
	cout << ig << endl;
	DistParamBundle fp = (DistParamBundle) ig;
	cout << "fp:" << fp << endl;
	InverseGamma ig1(fp);
	cout << "ig1:" << ig1 << endl;
	InverseGamma ig2 = !ig1;
	cout << "ig2:" << ig2 << endl;
	cout << "---- test moments and expectation of sufficient statistics ----"
			<< endl;
	InverseGamma::moment_type firstMoment = ig2.moment(1);
	InverseGamma::moment_type secondMoment = ig2.moment(2);
	cout << "first moment:" << firstMoment << ", second moment:" << secondMoment
			<< endl;
	DistParam suffMean1 = ig2.suff_mean(1);
	DistParam suffMean2 = ig2.suff_mean(2);
	cout << "sufficient mean:" << suffMean1 << endl << suffMean2 << endl;
}

ostream& operator<<(ostream& oss, InverseGamma const& dist) {
	oss << "-----------------------------------------" << endl;
	oss << "alpha: " << dist.m_alpha << ", beta:" << dist.m_beta
			<< ", is natural:" << dist.m_is_canonical << endl;
	oss << "-----------  moment ----------------" << endl;
	InverseGamma& dist1 = const_cast<InverseGamma&>(dist);
	for (size_t i = 1; i <= 2; i++) {
		oss << i << " moment:" << dist1.moment(i) << endl;
	}
	return oss;
}

} /* namespace mf */
