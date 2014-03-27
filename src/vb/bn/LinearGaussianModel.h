/*
 * LinearGaussianModel.h
 *
 *  Created on: Feb 25, 2014
 *      Author: qzhao2
 */

#ifndef LINEARGAUSSIANMODEL_H_
#define LINEARGAUSSIANMODEL_H_

#include "Model.h"

namespace bn {

/**
 * \brief a linear Gaussian model
 *
 * Let $a, b$ be two random vectors of the same dimension and assume each component of the
 * vector is independent w.r.t other components. Let c be the inner product of a and b and
 * the product is further corrupted by a Gaussian noise with $0$ mean and $\sigma^2$ variance.
 * The product is a Gaussian distribution with mean a.b and $\sigma^2$ variance.
 * It can be shown that under variational Bayesian paradigm, the posterior distribution
 * of the product and each component of a and b is also Gaussian distribution. Let $a_i$ be
 * the $i$-th compoent of a, its natural statistics is,
 *
 * $[(y-<c_{\i}>)<b_i> -1/2<b_i^2>]^T [a_i a_i^2]$
 *
 * where <> denotes expectation w.r.t the distribution of the random variable involved
 * in the bracket. By taking advantage of the symmetry between $a$ and $b, The natural
 * statistics of $b_i$ is easily obtained as,
 *
 * $[(y-<c_{\i}>)<a_i> -1/2<a_i^2>]^T [b_i b_i^2]$
 */
template<class T = float>
class LinearGaussianModel: public bn::ProbModel {
public:
	typedef T dist_type;
	typedef Variable<T> var_type;
	enum role_type {
		COND_A = 1, COND_B, COND_VAR
	};
protected:
	vector<string> m_aVec;
	vector<string> m_bVec;
protected:
	virtual NatParamVec _update_from_parent();
public:
	LinearGaussianModel(string const& id, string const& name,
			dist_type const& distVal, bool isObserved = false) :
			ProbModel(var_ptr_type(new var_type(id, name, distVal)),
					isObserved){

	}

	virtual void add_parent_var(string const& varId, size_t role) {
		ProbModel::add_parent_var(varId, role);
		/// track the mapping between vector components
		switch (role) {
		case LinearGaussianModel<>::COND_A: {
			m_aVec.push_back(varId);
		}
			break;
		case LinearGaussianModel<>::COND_B: {
			m_bVec.push_back(varId);
		}
			break;
		}
	}
	virtual NatParamVec to_parent_message(string const& varId);
	virtual ~LinearGaussianModel() {
	}
};

} /* namespace bn */

#endif /* LINEARGAUSSIANMODEL_H_ */
