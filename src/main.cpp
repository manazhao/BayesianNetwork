/*
 * main.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: qzhao2
 */

#include "vb/prob/DistParamBundle.h"
#include "vb/bn/VBMEngine.h"
#include "vb/prob/ArmadilloSerialization.h"

using namespace bn;
using namespace prob;

#define __TEST_ENGINE__

void test(){
#ifdef __TEST_DIST__
	test_DistParamBundle();
#endif
#ifdef __TEST_ENGINE__
//	test_engine();
	test_armadillo_serialization();
#endif

}

int main(int argc, char** argv){
	test();
	return 0;
}
