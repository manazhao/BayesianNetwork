/*
 * ArmadilloSerialization_test.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: manazhao
 */

#include "ArmadilloSerialization.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>

using namespace std;
namespace ba = boost::archive;

namespace prob{

void test_armadillo_serialization(){
	arma::vec v(10,fill::randn);
	/// write to text file
	ofstream ofs("./arma_vec.txt");
	{
		ba::text_oarchive oa(ofs);
		oa & v;
	}
	arma::vec v1;
	{
		ifstream ifs("./arma_vec.txt");
		ba::text_iarchive ia(ifs);
		ia & v1;
	}
	float diffSum = arma::accu(v - v1);
	cout << "diff sum:" << diffSum << endl;
}

}
