/*
 * Gaussian.h
 *
 *  Created on: Feb 21, 2014
 *      Author: qzhao2
 */

#ifndef GAUSSIAN_H_
#define GAUSSIAN_H_
#include "Distribution.h"
#include "DistParamBundle.h"
#include <exception>

namespace prob {
class Gaussian: public Distribution<float> {
protected:
	float m_mean;
	float m_var;
protected:
	Gaussian(float const& value) :
			Distribution<float>(value), m_mean(value), m_var(0) {
	}
private:
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version){
		/// call base class serialization
		ar & boost::serialization::base_object<Distribution<float> >(*this) & m_mean & m_var;
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

	void to_non_canomical() {
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
	Gaussian(DistParamBundle const& paramBundle);
	Gaussian& operator=(DistParamBundle const& paramBundle);
	operator DistParamBundle() const;
	Gaussian operator!() const;
	Gaussian operator+(Gaussian const& rhs) const;
	Gaussian& operator+=(Gaussian const& rhs);
	friend ostream& operator<<(ostream&, Gaussian const&);
};

/// testing function declaration

ostream& operator<<(ostream&, Gaussian const&);

}

#endif /* GAUSSIAN_H_ */
