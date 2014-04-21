/*
 * DiagMVGaussianModel.cpp
 *
 *  Created on: Mar 18, 2014
 *      Author: qzhao2
 */

#include "DiagMVGaussianModel.h"
#include "VBMEngine.h"

namespace bn {

DistParamBundle DiagMVGaussianModel::_update_from_parent() {
	/// update the natural statistics by incorporating sufficient
	/// statistic information of parent nodes
	/// note: the covariance matrix reduces to a vector
	VBMEngine& ENGINE = VBMEngine::get_engine();
	var_ptr_type& meanVar = ENGINE.get_variable(get_var_by_role(
			DiagMVGaussianModel::COND_MEAN));
	var_ptr_type& varianceVar = ENGINE.get_variable(get_var_by_role(
			DiagMVGaussianModel::COND_COV));
	DistParam vSS2 = varianceVar->suff_mean(2);
	DistParam mSS1 = meanVar->moment(1);
	size_t dim = m_targetVarPtr->size();
	DistParamBundle parentMessage(2, true);
	if (vSS2.m_vec.size() == 1) {
		repeat_vector(vSS2.m_vec, dim);
	}
	if (mSS1.m_vec.size() == 1) {
		repeat_vector(mSS1.m_vec, dim);
	}
	parentMessage[0] = (vec)(-0.5 * vSS2.m_vec);
	parentMessage[1] = (vec)(mSS1.m_vec % vSS2.m_vec);
	return parentMessage;
}

DistParamBundle DiagMVGaussianModel::to_parent_message(string const& varId) {
	VBMEngine& ENGINE = VBMEngine::get_engine();
	size_t varRole = m_varRoleMap[varId];
	assert(varRole);
	var_ptr_type& targetVar = m_targetVarPtr;
	var_ptr_type& meanVar = ENGINE.get_variable(get_var_by_role(
			DiagMVGaussianModel::COND_MEAN));
	var_ptr_type& varianceVar = ENGINE.get_variable(get_var_by_role(
			DiagMVGaussianModel::COND_COV));
	size_t dim = targetVar->size();
	DistParamBundle message(2, true);

	switch (varRole) {
	case DiagMVGaussianModel::COND_MEAN: {
		/// get the natural statistics from variance variable and use the second component
		vec vSS2 = varianceVar->suff_mean(2).m_vec;
		if (vSS2.size() == 1)
			repeat_vector(vSS2, dim);
		DistParam yMean = targetVar->moment(1);
		message[0] = (vec)(yMean.m_vec % vSS2);
		message[1] = (vec)(-0.5 * vSS2);
	}
		break;
	case DiagMVGaussianModel::COND_COV: {
		vec v(dim);
		v.fill(-0.5);
		message[0] = v;

		vec ySS1 = targetVar->suff_mean(1).m_vec;
		vec ySS2 = targetVar->suff_mean(2).m_vec;
		/// use the compact version
		vec mSS1 = meanVar->suff_mean(1).m_vec;
		vec mSS2 = meanVar->suff_mean(2).m_vec;
		if (mSS1.size() == 1) {
			repeat_vector(mSS1, dim);
			repeat_vector(mSS2, dim);
		}
		message[1] = (vec)(-0.5 * ySS2 + mSS1 % ySS1 - 0.5 * mSS2);
	}
		break;
	}
	return message;
}

} /* namespace bn */

