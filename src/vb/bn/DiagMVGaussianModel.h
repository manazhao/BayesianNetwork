/*
 * DiagMVGaussianModel.h
 *
 *  Created on: Mar 18, 2014
 *      Author: qzhao2
 */

#ifndef DIAGMVGAUSSIANMODEL_H_
#define DIAGMVGAUSSIANMODEL_H_
#include "Model.h"

namespace bn {
/**
 * by default the node is a observed one with
 * vector as observed value
 */
class DiagMVGaussianModel: public ProbModel {
public:
	typedef DiagMVGaussian dist_type;
	typedef Variable<DiagMVGaussian> var_type;
	/// define the node types: target variable, conditional variables mean and variance
	enum role_type {
		COND_MEAN = 1, COND_COV
	};

protected:
	virtual NatParamVec _update_from_parent();

public:
	DiagMVGaussianModel(string const& id, string const& name,
			size_t const& dim) :
			ProbModel(var_ptr_type(new var_type(id, name, dist_type(dim))), false) {
	}
	DiagMVGaussianModel(string const& id, string const& name,
			dist_type::value_type const& val, bool isObserved = false) :
			ProbModel(var_ptr_type(new var_type(id, name, dist_type::observation(val))), true) {
	}

	virtual NatParamVec to_parent_message(string const& varId);
	virtual ~DiagMVGaussianModel() {
	}
};

} /* namespace bn */

#endif /* DIAGMVGAUSSIANMODEL_H_ */
