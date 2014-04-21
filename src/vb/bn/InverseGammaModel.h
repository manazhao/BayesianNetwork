/*
 * InverseGammaModel.h
 *
 *  Created on: Feb 24, 2014
 *      Author: qzhao2
 */

#ifndef INVERSEGAMMAMODEL_H_
#define INVERSEGAMMAMODEL_H_

#include "Model.h"

namespace bn {

class InverseGammaModel: public bn::ProbModel {
public:
	typedef InverseGamma dist_type;
	typedef Variable<InverseGamma> var_type;
	typedef typename dist_type::value_type value_type;
public:
	/// define the node types: target variable, conditional variables mean and variance
	enum role_type {
		COND_ALPHA, COND_BETA
	};
protected:
	virtual DistParamBundle _update_from_parent();
	virtual void _process_child_message(DistParamBundle& message);
public:
	InverseGammaModel(string const& id, string const& name) :
			ProbModel(var_ptr_type(new var_type(id, name, dist_type())),false) {

	}

	InverseGammaModel(string const& id, string const& name, value_type const& value) :
			ProbModel(var_ptr_type(new var_type(id, name, dist_type::observation(value))),true) {

	}

	virtual DistParamBundle to_parent_message(string const& varId) {
		return DistParamBundle();
	}

	virtual ~InverseGammaModel(){}
};

} /* namespace bn */

#endif /* INVERSEGAMMAMODEL_H_ */
