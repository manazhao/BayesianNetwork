/*
 * DistParam.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: manazhao
 */

#include "DistParamBundle.h"
#include <assert.h>

namespace prob {

DistParamBundle::DistParamBundle(size_t const& numParams, bool isCanonical)
:m_params(numParams)
,m_num_params(numParams)
,m_is_canonical(isCanonical){
}

DistParam& DistParamBundle::operator[] (size_t const& idx){
	assert(idx < m_params.size());
	return m_params[idx];
}

DistParam const& DistParamBundle::operator[] (size_t const& idx)const{
	assert(idx < m_params.size());
	return m_params[idx];
}


DistParamBundle DistParamBundle::operator+ (DistParamBundle const& rhs) const{
	/// addition of two Distribution arguments
	/// it ONLY happens when model is expressed under natural parameters
	/// the same number of parameters
	if(rhs.size() == 0)
		return *this;
	if(size() == 0)
		return rhs;
	assert(m_num_params == rhs.m_num_params && !(m_is_canonical ^ rhs.m_is_canonical));
	DistParamBundle result(m_num_params,m_is_canonical);
	for(size_t i = 0; i < m_num_params; i++){
		result[i] = m_params[i] + rhs.m_params[i];
	}
	return result;
}

DistParamBundle& DistParamBundle::operator+= (DistParamBundle const& rhs){
	*this = (*this) + rhs;
	return *this;
}

DistParamBundle::~DistParamBundle() {
	// TODO Auto-generated destructor stub
}

ostream& operator << (ostream& oss, DistParamBundle const& distParam){
	oss << "# of parameters:" << distParam.m_num_params << endl;
	for(size_t i = 0; i < distParam.m_num_params; i++){
		oss << "[" << i << "]:" << distParam[i] << endl;
	}
	oss << endl;
	return oss;
}

}
