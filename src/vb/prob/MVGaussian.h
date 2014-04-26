/*
 * MVGaussian.h
 *
 *  Created on: Apr 20, 2014
 *      Author: manazhao
 */

#ifndef MVGAUSSIAN_H_
#define MVGAUSSIAN_H_
#include "Distribution.h"
#include "DistParamBundle.h"
#include <exception>

namespace prob {

class MVGaussian : public Distribution<vec>{
protected:
	colvec m_mean;
	mat m_cov;
	/// whether cache sufficient statistics
	bool m_cache_suff;
	/// second order moment cache (sufficient cache)
	vec m_som_cache;
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version){
		ar & boost::serialization::base_object<Distribution<vec> >(*this);
		ar & m_mean;
		ar & m_cov;
		ar & m_cache_suff;
		ar & m_som_cache;
	}
protected:
	MVGaussian(vec const& value, bool isSample, bool cacheSuff = false) :
			Distribution<vec>(value),m_cache_suff(cacheSuff) {
	}
public:
	MVGaussian(colvec const& mean = colvec(), mat const& cov = mat(),
			bool is_canonical = false, bool cacheSuff = false) :
			Distribution<vec>(is_canonical), m_mean(mean), m_cov(cov),m_cache_suff(cacheSuff) {

	}
	MVGaussian(size_t const& dim, bool cacheSuff = false) :
			Distribution<vec>(false), m_mean(dim), m_cov(dim,dim),m_cache_suff(cacheSuff) {
	}

	size_t size()const{
		return m_mean.size();
	}

	static MVGaussian observation(vec const& value, bool cacheSuff = false) {
		return MVGaussian(value, true, cacheSuff);
	}

	static MVGaussian const& diffuse_prior(size_t const& dim, bool cacheSuff = false) {
		static MVGaussian dDMVG(colvec(dim, arma::fill::zeros),
				mat(dim, dim, arma::fill::zeros), true, cacheSuff);
		return dDMVG;
	}
	void reset();
	void to_non_canonical();
	moment_type moment(size_t const& order = 1);
	suff_mean_type suff_mean(size_t const& idx = 1);
	MVGaussian(DistParamBundle const& paramBundle);
	MVGaussian& operator=(DistParamBundle const& paramBundle);
	MVGaussian(DistParam const& paramVec);
	MVGaussian& operator=(DistParam const& paramVec);
	operator DistParamBundle() const;
	operator DistParam();
	MVGaussian operator!() const;
	MVGaussian operator+(MVGaussian const& rhs) const;
	MVGaussian& operator+=(MVGaussian const& rhs);
	friend ostream& operator<<(ostream&, MVGaussian const&);
	MVGaussian();
	virtual ~MVGaussian();
};

}

#endif /* MVGAUSSIAN_H_ */
