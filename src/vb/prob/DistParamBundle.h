/*
 * DistParam.h
 *
 *  Created on: Apr 20, 2014
 *      Author: manazhao
 */

#ifndef DISTPARAM_H_
#define DISTPARAM_H_

#include <vector>
#include <ostream>
#include <armadillo>
#include "NatParamVec.h"
#include <boost/serialization/vector.hpp>

using namespace std;
using namespace arma;

namespace prob {

/**
 * \brief wrap parameters for all distributions
 */
class DistParamBundle {
	friend class MVGaussian;
	friend class DiagMVGaussian;
	friend class Gaussian;
	friend class MVInverseGamma;
	friend class InverseGamma;
	friend ostream& operator << (ostream& oss, DistParamBundle const& distParam);
protected:
	vector<DistParam> m_params;
	size_t m_num_params;
	bool m_is_canonical;
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version){
		ar & m_params;
		ar & m_num_params;
		ar & m_is_canonical;
	}
public:
	DistParamBundle(size_t const& numParams = 0, bool isCanonical = true);
	size_t size() const{
		return m_num_params;
	}
	void set_canonical(bool isCanonical){
		m_is_canonical  = isCanonical;
	}
	DistParam& operator[] (size_t const& idx);
	DistParam const& operator[] (size_t const& idx) const;
	DistParamBundle operator+ (DistParamBundle const& rhs) const;
	DistParamBundle& operator+= (DistParamBundle const& rhs);
	virtual ~DistParamBundle();
};

void test_DistParamBundle();
ostream& operator << (ostream& oss, DistParamBundle const& distParam);


}

#endif /* DISTPARAM_H_ */
