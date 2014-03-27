/*
 * GaussianModel.h
 *
 *  Created on: Feb 23, 2014
 *      Author: qzhao2
 */

#ifndef GAUSSIANMODEL_H_
#define GAUSSIANMODEL_H_

#include "Model.h"

namespace bn {

class GaussianModel: public ProbModel {
public:
	typedef Gaussian dist_type;
	typedef typename dist_type::value_type value_type;
	typedef Variable<Gaussian> var_type;
public:
	/// define the node types: target variable, conditional variables mean and variance
	enum role_type {
		COND_MEAN = 1, COND_VAR
	};
protected:
	virtual NatParamVec _update_from_parent();
	virtual void _process_child_message(NatParamVec& message);
public:
	/**
	 * create an hidden Gaussian random variable
	 */
	GaussianModel(string const& id, string const& name) :
			ProbModel(var_ptr_type(new var_type(id, name, dist_type())), false) {
	}
	/**
	 * create an observed Gaussian variable
	 */
	GaussianModel(string const& id, string const& name, value_type const& val) :
			ProbModel(
					var_ptr_type(
							new var_type(id, name, dist_type::observation(val))),true) {
	}
	virtual NatParamVec to_parent_message(string const& varId);
};

}

#endif /* GAUSSIANMODEL_H_ */
