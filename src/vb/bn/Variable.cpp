/*
 * Variable.cpp
 *
 *  Created on: Feb 22, 2014
 *      Author: qzhao2
 */

#include "Variable.h"

namespace bn {

using namespace prob;
using namespace std;

void test_variable() {
	cout << "--- test Gaussian variable ---" << endl;
	Variable<Gaussian> var1("g_1", "g1", Gaussian(2, 3));
	cout << var1 << endl;
}


ostream& operator<<(ostream& oss,BaseVariable & var){
	return var.print(oss);
}

template <typename T>
ostream& operator<<(ostream & oss, Variable<T>& var){
	oss << endl;
	oss << "---- dump of variable: " << var.m_name << " ----";
	oss << endl;
	oss << var.m_var;
	oss << endl;
	oss << "first moment: " << var.moment(1);
	oss << endl;
	oss << "second moment: " << var.moment(2);
	oss << endl;
	oss << "sufficient stat expectation:" << endl;
	oss << var.suff_mean();
	oss << endl;
	return oss;
}

}

