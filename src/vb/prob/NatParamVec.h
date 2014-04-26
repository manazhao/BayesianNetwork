/*
 * NatParamVec.h
 *
 *  Created on: Mar 20, 2014
 *      Author: qzhao2
 */

#ifndef NATPARAMVEC_H_
#define NATPARAMVEC_H_

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <armadillo>
#include "ArmadilloSerialization.h"
using namespace boost;
using namespace arma;
using namespace std;

namespace prob {

struct DistParam {
	vec m_vec;
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version){
		ar & m_vec;
	}
public:
	DistParam(vec const& v = vec()):m_vec(v) {
	}
	DistParam(mat const& m) :
			m_vec(vectorise(m)) {
	}
	DistParam(float const& val) :
			m_vec(1){
		m_vec[0] = val;
	}
	DistParam(size_t const& sz) :
			m_vec(sz,fill::zeros){
	}
	DistParam& operator= (vec const& v){
		m_vec = v;
		return *this;
	}
	DistParam& operator= (mat const& m){
		m_vec = vectorise(m);
		return *this;
	}

	DistParam& operator=(float const& val){
		m_vec = vec(1);
		m_vec(0) = val;
		return *this;
	}

	DistParam operator+(vec const& v) const{
		DistParam result = *this;
		if(v.size() > 0){
			if(m_vec.size() == 0){
				result.m_vec = v;
			}else{
				assert(m_vec.size() == v.size());
				result.m_vec += v;
			}
		}
		return result;
	}

	DistParam operator+(float v) const{
		DistParam result = *this;
		if(result.size() == 0){
			result.m_vec = vec(1);
		}else{
			assert(result.size() == 1);
		}
		result.m_vec(0) += v;
		return result;
	}

	DistParam& operator+= (vec const& v){
		if(v.size() > 0){
			if(m_vec.size() == 0){
				m_vec = v;
			}else{
				assert(m_vec.size() == v.size());
				m_vec += v;
			}
		}
		return *this;
	}

	DistParam& operator+= (float const& v){
		if(size() == 0){
			m_vec = vec(1);
		}else{
			assert(m_vec.size() == 1);
		}
		m_vec(0) += v;
		return *this;
	}

	DistParam operator+(DistParam const& rhs) const {
		DistParam result = *this;
		result += rhs.m_vec;
		return result;
	}

	inline bool is_empty() const {
		return size() == 0;
	}

	DistParam& operator+=(DistParam const& rhs) {
		(*this) += rhs.m_vec;
		return *this;
	}

	size_t size() const {
		return m_vec.size();
	}

	vec::elem_type& operator[](size_t idx) {
		return m_vec[idx];
	}

	vec::elem_type const& operator[](size_t idx) const {
		return m_vec[idx];
	}

	operator vec() {
		return m_vec;
	}

	operator const vec() const{
		return m_vec;
	}

	operator const float() {
		return m_vec(0);
	}

	operator const float() const{
		return m_vec(0);
	}

	DistParam& reset(){
		m_vec.fill(0);
		return *this;
	}

};

ostream& operator<<(ostream& oss, DistParam const& param);

}




#endif /* NATPARAMVEC_H_ */
