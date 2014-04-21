/*
 * NatParamVec.cpp
 *
 *  Created on: Mar 20, 2014
 *      Author: qzhao2
 */

#include "NatParamVec.h"

namespace prob {

ostream& operator<<(ostream& oss, DistParam const& param) {
	for(size_t i = 0; i < param.m_vec.size(); i++){
		oss << (i == 0? "" :",") << param[i];
	}
	return oss;
}

}





