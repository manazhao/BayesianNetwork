/*
 * Distribution.h
 *
 *  Created on: Feb 20, 2014
 *      Author: qzhao2
 */

#ifndef DISTRIBUTION_H_
#define DISTRIBUTION_H_
#include <boost/shared_ptr.hpp>
#include <boost/serialization/base_object.hpp>
#include <iostream>
#include <armadillo>
#include "NatParamVec.h"
#include "ArmadilloSerialization.h"

using namespace boost;
using namespace arma;
using namespace std;

namespace prob {
template<class T>
class Distribution {
public:
	typedef T value_type;
	/// moment
	typedef DistParam moment_type;
	/// sufficient statistic expectation
	typedef DistParam suff_mean_type;
protected:
	/// observed value
	value_type m_value;
	bool m_is_canonical;
	bool m_is_updated;
	bool m_is_observed;

private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned version){
		ar & m_value & m_is_canonical & m_is_updated & m_is_observed;
	}
public:
	Distribution(bool isCanonical = false) :
			m_is_canonical(isCanonical), m_is_updated(true), m_is_observed(false) {
	}
	Distribution(T const& value) :
			m_value(value), m_is_canonical(false), m_is_updated(true), m_is_observed(
					true) {
	}

	value_type const& get_value() const {
		return m_value;
	}

	inline bool is_observed() {
		return m_is_observed;
	}
};

}

#endif /* DISTRIBUTION_H_ */
