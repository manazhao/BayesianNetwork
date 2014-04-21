/*
 * DistParam_test.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: manazhao
 */

#include "DistParamBundle.h"

namespace prob{
void test_DistParamBundle(){
	DistParamBundle scalarParam1(2);
	scalarParam1[0] = (float)1;
	scalarParam1[1] = (float)2;
	DistParamBundle scalarParam2(2,true);
	scalarParam2[0] = (float)2;
	scalarParam2[1] = (float)3;
	DistParamBundle scalarSum = scalarParam1 + scalarParam2;
	cout << "scalar param1:" << endl << scalarParam1 << endl;
	cout << "scalar param2:" << endl << scalarParam2 << endl;
	cout << "sum of param1 and param2 :" << endl << scalarSum << endl;
	/// test vector
	DistParamBundle vecParam1(2);
	vecParam1[0] = vec(3,fill::randn);
	vecParam1[1] = vec(2,fill::randn);
	DistParamBundle vecParam2(2);
	vecParam2[0] = vec(2,fill::randn);
	vecParam2[1] = vec(2,fill::randn);

	DistParamBundle vecSum = vecParam1 + vecParam2;

	cout << "vec param1:" << endl << vecParam1 << endl;
	cout << "vec param2:" << endl << vecParam2 << endl;
	cout << "vec param sum:" << endl << vecSum << endl;

}

}
