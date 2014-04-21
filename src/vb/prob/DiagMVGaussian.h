/*
 * DiagMVGaussian.h
 *
 *  Created on: Apr 20, 2014
 *      Author: manazhao
 */

#ifndef DIAGMVGAUSSIAN_H_
#define DIAGMVGAUSSIAN_H_
#include <iostream>
#include "Distribution.h"
#include "DistParamBundle.h"

namespace prob {
/**
 * \brief definition of diagonal multivariate Gaussian distribution
 *
 * Diagonal Gaussian distribution only has non-zero values on the diagonal entries.
 * The covariance matrix reduces to vector. Due to the independence between vector
 * components, each component has independent conjugate priors which are single variate
 * Gaussian  distribution and Inverse Gamma distribution for the mean and variance accordingly.
 */
class DiagMVGaussian: public Distribution<vec> {
public:
	vec m_mean;
	vec m_cov;
	/// whether cache sufficient statistics
	bool m_cache_suff;
	/// second order moment cache (sufficient cache)
	vec m_som_cache;

protected:
	DiagMVGaussian(vec const& value, bool isSample, bool cacheSuff = false) :
		Distribution<vec> (value),m_cache_suff(cacheSuff) {
	}
public:
	DiagMVGaussian(vec const& mean = colvec(), vec const& cov = vec(),
			bool is_canonical = false, bool cacheSuff = false) :
		Distribution<vec> (is_canonical), m_mean(mean), m_cov(cov),m_cache_suff(cacheSuff) {
	}

	DiagMVGaussian(size_t const& dim, bool cacheSuff = false) :
		Distribution<vec> (false), m_mean(dim), m_cov(dim),m_cache_suff(cacheSuff) {
	}

	size_t size() const {
		return m_mean.size();
	}
	static DiagMVGaussian observation(vec const& value, bool cacheSuff = false) {
		return DiagMVGaussian(value, true, cacheSuff);
	}

	static DiagMVGaussian const& diffuse_prior(size_t const& dim, bool cacheSuff = false) {
		static DiagMVGaussian dDMVG(colvec(dim, arma::fill::zeros), mat(dim,
				dim, arma::fill::zeros), true,cacheSuff);
		return dDMVG;
	}

	void reset();
	void to_non_canonical();
	moment_type moment(size_t const& order = 1);
	suff_mean_type suff_mean(size_t const& idx = 1);
	DiagMVGaussian(DistParamBundle const& paramBundle);
	DiagMVGaussian& operator=(DistParamBundle const& paramBundle);
	operator DistParamBundle() const;
	DiagMVGaussian operator!() const;
	DiagMVGaussian operator+(DiagMVGaussian const& rhs) const;
	DiagMVGaussian& operator+=(DiagMVGaussian const& rhs);
	friend ostream& operator<<(ostream&, DiagMVGaussian const&);
};

ostream& operator<<(ostream& oss, DiagMVGaussian const& dist);
}
#endif /* DIAGMVGAUSSIAN_H_ */
