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
	virtual DistParamBundle _update_from_parent() {
		return DistParamBundle();
	}
public:
	HyperParameter(string const& id, string const& name, dist_val_type const& distVal) :
			ProbModel(
					var_ptr_type(
							new var_type(id, name, dist_type::observation(distVal))),
					true) {

	}
	virtual DistParamBundle to_parent_message(string const& varId) {
		return DistParamBundle();
	}
	virtual ~HyperParameter() {
	}
};

} /* namespace bn */

#endif /* HYPERPARAMMODEL_H_ */
