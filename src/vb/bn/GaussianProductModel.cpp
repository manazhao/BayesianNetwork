/*
 * GaussianProductModel.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: qzhao2
 */

#include "GaussianProductModel.h"
#include "VBMEngine.h"

namespace bn {

template<class T>
NatParamVec GaussianProductModel<T>::_update_from_parent() {
	VBMEngine& ENGINE = VBMEngine::get_engine();
	var_ptr_type& aVarPtr = ENGINE.get_variable(get_var_by_role(GaussianProductModel<>::COND_A));
	var_ptr_type& bVarPtr = ENGINE.get_variable(get_var_by_role(GaussianProductModel<>::COND_B));
	var_ptr_type& varianceVarPtr = ENGINE.get_variable(get_var_by_role(GaussianProductModel<>::COND_VAR));
//	NatParamVec vSuffMean = varianceVarPtr->suff_mean();

}

template<class T>
NatParamVec GaussianProductModel<T>::to_parent_message(string const& varId) {
	VBMEngine& ENGINE = VBMEngine::get_engine();
	size_t varRole = m_varRoleMap[varId];

	assert(varRole);
	NatParamVec message((size_t)2,true);
	switch (varRole) {
	case GaussianProductModel<>::COND_A:{
		/// evaluate the natural statistics for variable $a$
		var_ptr_type& bVar = ENGINE.get_variable(get_var_by_role(GaussianProductModel<>::COND_B));
		message[0] = (float)bVar->moment(1) * (float)m_targetVarPtr->moment(1);
		message[1] = -0.5 * (float)bVar->moment(2);
	}
		break;
	case GaussianProductModel<>::COND_B:{
		var_ptr_type& aVar = ENGINE.get_variable(get_var_by_role(GaussianProductModel<>::COND_A));
		message[0] = (float)aVar->moment(1) * (float)m_targetVarPtr->moment(1);
		message[1] = -0.5 * (float)aVar->moment(2);
	}
		break;
	}
	return message;
}

} /* namespace bn */
