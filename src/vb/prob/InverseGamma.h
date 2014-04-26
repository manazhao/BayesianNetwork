/*
 * InverseGamma.h
 *
 *  Created on: Feb 21, 2014
 *      Author: qzhao2
 */

#ifndef INVERSEGAMMA_H_
#define INVERSEGAMMA_H_
#include "Distribution.h"
#include "DistParamBundle.h"
#include <boost/math/special_functions/digamma.hpp>

namespace prob {

void test_inverse_gamma();

class InverseGamma: public Distribution<float> {
protected:
	float m_alpha;
	float m_beta;
	float m_ss_cache[2];
private:
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned version){
		ar & boost::serialization::base_object<Distribution<float> >(*this);
		ar & m_alpha & m_beta & m_ss_cache[0] & m_ss_cache[1];
	}
protected:
	InverseGamma(float const& val) :
			Distribution<float>(val), m_alpha(0), m_beta(0) {
	}
public:
	InverseGamma(float const& alpha, float const& beta,
			bool isCanonical = false) :
			Distribution<float>(isCanonical), m_alpha(alpha), m_beta(beta) {
	}

	InverseGamma() :
			Distribution<float>(false), m_alpha(1), m_beta(1) {

	}

	static InverseGamma observation(value_type const& value) {
		return InverseGamma(value);
	}

	static InverseGamma const& diffuse_prior() {
		static InverseGamma dIG(1, 1, false);
		return dIG;
	}

	void update_ss_cache() {
		if (m_is_updated) {
			if (is_observed()) {
				m_ss_cache[0] = log(m_value);
				m_ss_cache[1] = 1 / m_value;
			} else {
				to_non_canonical();
				float b = m_beta;
				float a = m_alpha;
				m_ss_cache[0] = log(b) - boost::math::digamma(a);
				m_ss_cache[1] = a / b;
			}
			m_is_updated = false;
		}
	}

	InverseGamma(DistParamBundle const& paramBundle){
		m_is_canonical = paramBundle.m_is_canonical;
		assert(paramBundle.m_num_params == 2);
		m_alpha = paramBundle[0];
		m_beta = paramBundle[1];
		m_is_updated = true;
	}
	void to_non_canonical() {
		if (m_is_canonical) {
			(*this) = !(*this);
		}
	}
	void reset() {
		m_alpha = 0;
		m_beta = 0;
		m_is_canonical = true;
		m_is_updated = true;
	}

	size_t size() const{
		return 1;
	}
	/**
	 * \brief return the first and second  moments of x
	 *
	 * the first moment(mean value of x) is computed as,
	 * moment(x,1) = (\beta)/(\alpha - 1) in original parameters or
	 * moment(x,1) = (\eta_2)/(\eta_1 + 1) in canonical natural parameter
	 *
	 * the second moment(expectation of x^2) is computed as,
	 * moment(x,2) = moment(x,1)^2 + \beta^2/((\alpha-1)^2(\alpha-2)) in original parameter or
	 * moment(x,2) = moment(x,1)^2 + \eta_2^2/((\eta_1+2)^2(\eta_1+3)) in canonical parameters
	 */
	moment_type moment(size_t const& order) {
		assert(order == 1 || order == 2);
		moment_type mVal;
		if (is_observed()) {
			/// simply return the value itself
			switch (order) {
			case 1:
				mVal = m_value;
				break;
			case 2:
				mVal = m_value * m_value;
				break;
			}
		} else {
			to_non_canonical();
			float a = m_alpha;
			float b = m_beta;
			switch (order) {
			case 1:
				mVal = b / (a - 1);
				break;
			case 2:
				mVal = (b * b) / ((a - 1) * (a - 2));
				break;
			}
		}

		return mVal;
	}
	/**
	 * \brief calculate the expectation of the sufficient statistics where are
	 * [ln(x),1/x]
	 *
	 * the expectation of the sufficient statiscs are computed as,
	 * E(ln(x)) = ln(\alpha) - digamma(\beta) (Note: digamma is the logarithm gamma derivative, namely, digamma(x) = gamma'(x)/gamma(x)
	 * E(1/x) = \alpha/\beta
	 */
	suff_mean_type suff_mean(size_t const& idx) {
		assert(idx == 1 || idx == 2);
		update_ss_cache();
		return m_ss_cache[idx - 1];
	}

	InverseGamma& operator= (DistParamBundle const& paramBundle) {
		m_is_canonical = paramBundle.m_is_canonical;
		assert(paramBundle.m_num_params == 2);
		m_alpha = paramBundle[0];
		m_beta = paramBundle[1];
		m_is_updated = true;
		return *this;
	}

	operator DistParamBundle() const {
		DistParamBundle fp(2, m_is_canonical);
		fp[0] = m_alpha;
		fp[1] = m_beta;
		return fp;
	}

	InverseGamma operator!() const {
		InverseGamma invParam(*this);
		invParam.m_is_canonical = !m_is_canonical;
		invParam.m_alpha = -m_alpha - 1;
		invParam.m_beta = -m_beta;
		return invParam;
	}

	InverseGamma operator+(InverseGamma const& rhs) const {
		InverseGamma resultParam = (m_is_canonical ? *this : !(*this));
		InverseGamma rhs1 = (rhs.m_is_canonical ? rhs : !rhs);
		resultParam.m_alpha += rhs1.m_alpha;
		resultParam.m_beta += rhs1.m_beta;
		resultParam.m_is_updated = true;
		return resultParam;
	}

	InverseGamma& operator+=(InverseGamma const& rhs) {
		(*this) = (*this) + rhs;
		return *this;
	}

	friend ostream& operator<<(ostream&, InverseGamma const&);
};

ostream& operator<<(ostream&, InverseGamma const&);

} /* namespace mf */

#endif /* INVERSEGAMMA_H_ */
