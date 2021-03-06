/*
 * GaussianModel.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: qzhao2
 */
#include "GaussianModel.h"
#include "VBMEngine.h"

namespace bn {


void GaussianModel::_process_child_message(DistParamBundle& message){
	if(message[0].size() > 1){
		/// from mv child nodes
		message[0] = (float)accu(message[0].m_vec);
		message[1] = (float)accu(message[1].m_vec);
	}
}

DistParamBundle GaussianModel::_update_from_parent() {
	/// receive messages from child nodes
	VBMEngine& ENGINE = VBMEngine::get_engine();
	var_ptr_type& meanVar = ENGINE.get_variable(get_var_by_role(GaussianModel::COND_MEAN));
	var_ptr_type& varianceVar = ENGINE.get_variable(get_var_by_role(GaussianModel::COND_VAR));
	float vSS2 = (float)varianceVar->suff_mean(2);
	/// mean of mean variable
	float mMean = (float)meanVar->moment(1);
	DistParamBundle parentMessage(2, true);
	parentMessage[0] = mMean * vSS2;
	parentMessage[1] = (float)(-0.5 * vSS2);
	return parentMessage;
}

DistParamBundle GaussianModel::to_parent_message(string const& varId) {
	VBMEngine& ENGINE = VBMEngine::get_engine();
	size_t varRole = m_varRoleMap[varId];
	assert(varRole);
	var_ptr_type& targetVar = m_targetVarPtr;
	var_ptr_type& meanVar = ENGINE.get_variable(get_var_by_role(GaussianModel::COND_MEAN));
	var_ptr_type& varianceVar = ENGINE.get_variable(get_var_by_role(GaussianModel::COND_VAR));
	DistParamBundle message(2, true);

	switch (varRole) {
	case GaussianModel::COND_MEAN: {
		/// get the natural statistics from variance variable and use the second component
		float vSS2 = (float)varianceVar->suff_mean(2);
		float yMean = (float) targetVar->moment(1);
		message[0] = yMean * vSS2;
		message[1] = (float)-0.5 * vSS2;
	}
		break;
	case GaussianModel::COND_VAR: {
		message[0] = (float)-0.5;
		float ySS1 = (float)targetVar->suff_mean(1);
		float ySS2 = (float)targetVar->suff_mean(2);
		float mSS1 = (float)meanVar->suff_mean(1);
		float mSS2 = (float)meanVar->suff_mean(2);
		message[1] = (float)(-0.5 * ySS2 + mSS1 * ySS1 - 0.5 * mSS2);

	}
		break;
	}
	return message;
}

}

