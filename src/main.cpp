/*
 * main.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: qzhao2
 */

#include "vb/prob/DistParamBundle.h"
#include "vb/bn/VBMEngine.h"

using namespace bn;
using namespace prob;

#define __TEST_ENGINE__

void test(){
#ifdef __TEST_DIST__
	test_DistParamBundle();
#endif
#ifdef __TEST_ENGINE__
	test_engine();
#endif

}

int main(int argc, char** argv){
	test();
	return 0;
}
