/*
 * MVInverseGammaModel.h
 *
 *  Created on: Mar 21, 2014
 *      Author: qzhao2
 */

#ifndef MVINVERSEGAMMAMODEL_H_
#define MVINVERSEGAMMAMODEL_H_

#include "Model.h"

namespace bn {

class MVInverseGammaModel: public bn::ProbModel {
public:
	typedef MVInverseGamma dist_type;
	typedef Variable<MVInverseGamma> var_type;
	typedef typename dist_type::value_type value_type;
public:
	enum role_type{
		COND_ALPHA, COND_BETA
	};
protected:
	virtual DistParamBundle _update_from_parent();
public:
	MVInverseGammaModel(string const& id, string const& name);
	MVInverseGammaModel(string const& id, string const& name, value_type const& value) :
			ProbModel(var_ptr_type(new var_type(id, name, dist_type::observation(value))),true) {

	}

	virtual DistParamBundle to_parent_message(string const& varId) {
		return DistParamBundle();
	}

	virtual ~MVInverseGammaModel();
};

} /* namespace bn */

#endif /* MVINVERSEGAMMAMODEL_H_ */
