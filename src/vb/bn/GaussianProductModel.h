/*
 * GaussianProductModel.h
 *
 *  Created on: Feb 25, 2014
 *      Author: qzhao2
 */

#ifndef GAUSSIANPRODUCTMODEL_H_
#define GAUSSIANPRODUCTMODEL_H_

#include "Model.h"

/**
 * \brief Modeling the product of two (scalar) random variables
 *
 * Let $a,b$ be two scalar random variables and $c$ be the product of
 * $a,b$. $c$ is further corrupted by additive Gaussian noise with $0$ mean
 * and $\sigma^2$ variance. Namely,
 * $c \sim N(a.b,\sigma^2)$. It can be shown that under variational Bayesian
 * paradigm, the posterior distribution of $a$ and $b$ are Gaussian with the
 * following natural statistics,
 * $[<b><y>, -0.5<b^2>]^T [a,a^2]$ where <> denotes the expectation for the
 * random variable involved in the bracket.
 * The natural statistics for the target variable $c$ is,
 * $[<ab> -0.5]^T [y,y^2]$
 */
namespace bn {

template<class T=float>
class GaussianProductModel: public bn::ProbModel {
public:
	typedef T dist_type;
	typedef Variable<T> var_type;
	enum role_type {
		COND_A, COND_B, COND_VAR
	};
protected:
	virtual NatParamVec _update_from_parent();
public:
	GaussianProductModel(string const& id, string const& name,
			dist_type const& distVal, bool isObserved) :
			ProbModel(var_ptr_type(new var_type(id, name, distVal), isObserved)) {
	}
	virtual NatParamVec to_parent_message(string const& varId);
	virtual ~GaussianProductModel(){}
};

} /* namespace bn */

#endif /* GAUSSIANPRODUCTMODEL_H_ */
