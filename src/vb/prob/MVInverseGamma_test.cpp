/*
 * MVInverseGamma_test.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: qzhao2
 */

#include "MVInverseGamma.h"

namespace prob {

void test_MVInverseGamma(){
	vec alpha_vec(3);
	alpha_vec.fill(3);
	vec beta_vec(3);
	beta_vec.fill(1);
	MVInverseGamma mvg(alpha_vec,beta_vec);
	MVInverseGamma mvg1(alpha_vec * 2, beta_vec * 2);
//	mvg = !mvg;
//	mvg1 = !mvg1;
	MVInverseGamma mvg2 = mvg + mvg1;
	cout << "mvg:" << endl << mvg << endl;
	cout << "mvg1:" << endl << mvg1 << endl;
	cout << "mvg2:" << endl << mvg2 << endl;
}

} /* namespace prob */
