/*
 * MVInverseGamma.h
 *
 *  Created on: Mar 21, 2014
 *      Author: qzhao2
 */

#ifndef MVINVERSEGAMMA_H_
#define MVINVERSEGAMMA_H_

#include "Distribution.h"

namespace prob {

class MVInverseGamma: public prob::Distribution<vec> {
	friend ostream& operator<<(ostream&, MVInverseGamma const&);
protected:
	vec m_alpha_vec;
	vec m_beta_vec;
	//// cache the sufficient statistics
	mat m_ss_cache;
	size_t m_dim;
protected:
	MVInverseGamma(vec const& value, bool) :
			Distribution<vec>(value),m_ss_cache(value.size(),2),m_dim(value.size()) {
	}
public:
	MVInverseGamma(vec const& alphaVec = vec(), vec const& betaVec = vec(),
			bool isCanonical = false);

	MVInverseGamma(size_t const& dim) :
			Distribution<vec>(false), m_alpha_vec(dim), m_beta_vec(dim), m_ss_cache(
					dim, 2),m_dim(dim) {
	}

	static MVInverseGamma observation(vec const& val){
		static MVInverseGamma mvIG(val,true);
		return mvIG;
	}

	size_t size(){
		return m_dim;
	}

	MVInverseGamma(NatParamVec const& paramVec);
	void toNonCanonical();
	void reset();
	size_t size() const{
		return m_alpha_vec.size();
	}
	moment_type moment(size_t const& order);
	suff_mean_type suff_mean(size_t const& idx) ;
	static MVInverseGamma const& diffuse_prior(size_t const& dim) {
		static MVInverseGamma dMVIG(vec(dim, arma::fill::ones),
				vec(dim, arma::fill::ones));
		return dMVIG;
	}
	void updateSSCache();
	MVInverseGamma& operator=(NatParamVec const& paramVec);
	operator NatParamVec();
	MVInverseGamma operator!() const;
	MVInverseGamma operator+(MVInverseGamma const& rhs) const;
	MVInverseGamma& operator+=(MVInverseGamma const& rhs);
	virtual ~MVInverseGamma();
};
ostream& operator<<(ostream&, MVInverseGamma const&);
void test_MVInverseGamma();

} /* namespace prob */

#endif /* MVINVERSEGAMMA_H_ */
