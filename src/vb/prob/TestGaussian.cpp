/*
 * TestGaussian.cpp
 *
 *  Created on: Mar 18, 2014
 *      Author: qzhao2
 */

#include "TestGaussian.h"
#include "DistParamBundle.h"
#include "DiagMVGaussian.h"

using namespace prob;
/// testing cases
void test_MVGaussian() {
	colvec mean = randn<colvec>(2);
	mat cov(2, 2);
	cov.eye();
//	MVGaussian param(mean, cov);
//	MVGaussian nParam = !param;
//	cout << "param:" << endl;
//	cout << param << endl;
//	/// testing the addition
//	mean *= 2;
//	MVGaussian param2(mean, cov * 2);
//	cout << "param2:" << endl;
//	cout << param2 << endl;
//	MVGaussian param3 = nParam + param2;
//	cout << "param3:" << endl;
//	cout << param3 << endl;
//	NatParamVec fp = param3;
//	MVGaussian param4(fp);
//	cout << "param4 from param3's natural parameter:" << endl;
//	cout << param4 << endl;
//	MVGaussian param4Inv = !!param4;
//	NatParamVec param4Vec = param4Inv;
//	MVGaussian param4Recover(param4Vec);
//	cout << "param4 recovered from double inverse:" << endl << param4Recover << endl;
}

void test_DiagMVGaussian() {
	colvec mean = randn<colvec>(2);
	colvec cov(2, arma::fill::ones);
	DiagMVGaussian dg(mean, cov);
	DiagMVGaussian invDg = !dg;
	DiagMVGaussian dg1(randn<colvec>(2), cov * 2);
	DiagMVGaussian dg2 = dg + dg1;
	cout << "dg" << endl;
	cout << dg << endl;
	cout << "invDg" << endl;
	cout << invDg << endl;
	cout << "dg1" << endl;
	cout << dg1 << endl;
	cout << "invDg1" << endl;
	cout << !dg1 << endl;
	cout << "dg2 = dg + dg1" << endl;
	cout << dg2 << endl;
	DistParamBundle dgNP = (DistParamBundle) dg;
	DiagMVGaussian dgRecover(dgNP);
	cout << "dg recovered from natural parameter:" << dgRecover << endl;
	DiagMVGaussian dgRecoverInv((DistParamBundle) !dgRecover);
	dgRecover = dgNP;
	cout << "dg recovered from inverted natural parameter:" << dgRecover
			<< endl;

}

void test_Gaussian() {
	Gaussian param1(0, 1);
	Gaussian param2(1, 5);
	Gaussian param3 = param1 + param2;
	cout << "param1:" << endl << param1 <<endl;
	cout << "param2:" << endl << param2 <<endl;
	cout << "param1 inv:" << endl << !param1 << endl;
	cout << "param2 inv:" << endl << !param2 << endl;
	cout << "param3=param1+param2: " <<endl<< param3 << endl;
	cout << "param3 inv:" << endl << !param3 << endl;
	DistParamBundle param1Nat = (DistParamBundle)param1;
	Gaussian param1Recover(param1Nat);
	Gaussian param1RecoverInv((DistParamBundle)!param1);
	cout << "param1 recover from nat stat:" << endl << param1Recover << endl;
	cout << "param1 recover from inv nat stat:" << endl << param1RecoverInv << endl;
}




