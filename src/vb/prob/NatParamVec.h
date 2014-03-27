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
using namespace boost;
using namespace arma;
using namespace std;

namespace prob {

struct NatParamVec {
	vec m_vec;
	bool m_is_canonical;

	NatParamVec(vec const& vec = vec(), bool is_canonical = false) :
			m_vec(vec), m_is_canonical(is_canonical) {
	}

	NatParamVec(mat const& m, bool is_canonical = false) :
			m_vec(vectorise(m)), m_is_canonical(is_canonical) {
	}

	NatParamVec(float const& val, bool is_canonical = false) :
			m_vec(1), m_is_canonical(is_canonical) {
		m_vec[0] = val;
	}

	NatParamVec(size_t const& sz, bool is_canonical = false) :
			m_vec(sz), m_is_canonical(is_canonical) {
	}

	NatParamVec operator+(NatParamVec const& rhs) const {
		assert(rhs.size() == size() || rhs.size() == 0);
		NatParamVec result = *this;
		if (rhs.size() > 0) {
			for (size_t i = 0; i < size(); i++) {
				result[i] += rhs[i];
			}
		}
		return result;
	}

	inline bool is_empty() const {
		return size() == 0;
	}

	NatParamVec& operator+=(NatParamVec const& rhs) {
		if (is_empty()) {
			*this = rhs;
		} else if (!rhs.is_empty()) {
			assert(size() == rhs.size());
			for (size_t i = 0; i < size(); i++) {
				(*this)[i] += rhs[i];
			}
		}
		return *this;
	}

	vec range_slice(size_t from, size_t to) {
		return m_vec.subvec(from, to);
	}
	void range_assign(size_t from, vec const& vals) {
		assert(from + vals.size() <= m_vec.size());
		for (size_t i = 0; i < vals.size(); i++) {
			m_vec(i + from) = vals[i];
		}
	}

	void range_assign(size_t from, float& val) {
		m_vec(from) = val;
	}

	void range_assign(size_t from, mat const& vals) {
		assert(from + vals.size() <= m_vec.size());
		for (size_t i = 0; i < vals.size(); i++) {
			m_vec(i + from) = vals(i);
		}
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

	operator float() {
		return m_vec[0];
	}

};

ostream& operator<<(ostream& oss, NatParamVec const& param);

}




#endif /* NATPARAMVEC_H_ */
