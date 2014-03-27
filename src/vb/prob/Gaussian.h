/*
 * Gaussian.h
 *
 *  Created on: Feb 21, 2014
 *      Author: qzhao2
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_
#include "Distribution.h"
#include <exception>

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
protected:
	colvec m_mean;
	colvec m_cov;
	/// compact second order moment cache
	vec m_sm_cache;
protected:
	DiagMVGaussian(vec const& value, bool isSample) :
			Distribution<vec>(value) {
	}
public:
	DiagMVGaussian(colvec const& mean = colvec(), colvec const& cov = mat(),
			bool is_canonical = false) :
			Distribution<vec>(is_canonical), m_mean(mean), m_cov(cov) {

	}

	DiagMVGaussian(size_t const& dim) :
			Distribution<vec>(false), m_mean(dim), m_cov(dim) {
	}

	static DiagMVGaussian observation(vec const& value) {
		return DiagMVGaussian(value, true);
	}

	static DiagMVGaussian const& diffuse_prior(size_t const& dim) {
		static DiagMVGaussian dDMVG(colvec(dim, arma::fill::zeros),
				colvec(dim, arma::fill::zeros), true);
		return dDMVG;
	}
	void reset();
	size_t size() const {
		return m_mean.size();
	}
	vec updateSSCache();
	void toNonCanonical();
	moment_type moment(size_t const& order = 1);
	suff_mean_type suff_mean(size_t const& idx = 1);
	DiagMVGaussian(NatParamVec const& paramVec);
	DiagMVGaussian& operator=(NatParamVec const& paramVec);
	operator NatParamVec();
	DiagMVGaussian operator!() const;
	DiagMVGaussian operator+(DiagMVGaussian const& rhs) const;
	DiagMVGaussian& operator+=(DiagMVGaussian const& rhs);
	friend ostream& operator<<(ostream&, DiagMVGaussian const&);
};


class Gaussian: public Distribution<float> {
protected:
	float m_mean;
	float m_var;
protected:
	Gaussian(float const& value) :
			Distribution<float>(value), m_mean(value), m_var(0) {
	}
public:
	Gaussian(float const& mean, float const& var, bool is_canonical = false) :
			Distribution<float>(is_canonical), m_mean(mean), m_var(var) {

	}

	Gaussian() :
			Distribution<float>(false), m_mean(0), m_var(1e6) {

	}

	static Gaussian const& diffuse_prior() {
		static Gaussian dGaussian(0, 1e6, false);
		return dGaussian;
	}

	static Gaussian observation(value_type const& value) {
		return Gaussian(value);
	}

	void toNonCanonical() {
		if (m_is_canonical) {
			(*this) = !(*this);
		}
	}
	void reset();
	size_t size() const {
		return 1;
	}
	moment_type moment_compact(size_t const& order) {
		return moment(order);
	}
	moment_type moment(size_t const& order);
	suff_mean_type suff_mean_compact(size_t const& idx) {
		return suff_mean(idx);
	}
	/**
	 * return the expectation of the sufficient statistics which are,
	 * x and
	 * x*x
	 */
	suff_mean_type suff_mean(size_t const& idx);
	Gaussian(NatParamVec const& paramVec);
	Gaussian& operator=(NatParamVec const& paramVec);
	operator NatParamVec();
	Gaussian operator!() const;
	Gaussian operator+(Gaussian const& rhs) const;
	Gaussian& operator+=(Gaussian const& rhs);
	friend ostream& operator<<(ostream&, Gaussian const&);
};

/// testing function declaration

//ostream& operator<<(ostream&, MVGaussian const&);
ostream& operator<<(ostream&, Gaussian const&);

}

#endif /* GAUSSIAN_H_ */
