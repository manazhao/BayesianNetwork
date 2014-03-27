/*
 * HyperParamModel.h
 *
 *  Created on: Feb 25, 2014
 *      Author: qzhao2
 */

#ifndef HYPERPARAMMODEL_H_
#define HYPERPARAMMODEL_H_

#include "Model.h"

namespace bn {

template<class T = Gaussian>
class HyperParameter: public bn::ProbModel {
	typedef T dist_type;
	typedef Variable<dist_type> var_type;
	typedef typename T::value_type dist_val_type;
protected:
	virtual NatParamVec _update_from_parent() {
		return NatParamVec();
	}
public:
	HyperParameter(string const& id, string const& name, dist_val_type const& distVal) :
			ProbModel(
					var_ptr_type(
							new var_type(id, name, dist_type::observation(distVal))),
					true) {

	}
	virtual NatParamVec to_parent_message(string const& varId) {
		return NatParamVec();
	}
	virtual ~HyperParameter() {
	}
};

} /* namespace bn */

#endif /* HYPERPARAMMODEL_H_ */
