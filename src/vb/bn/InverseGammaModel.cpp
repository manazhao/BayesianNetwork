/*
 * InverseGammaModel.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: qzhao2
 */

#include "InverseGammaModel.h"
#include "VBMEngine.h"

namespace bn {

DistParamBundle InverseGammaModel::_update_from_parent() {
	var_ptr_type& alphaVar = VBMEngine::get_engine().get_variable(
			get_var_by_role(InverseGammaModel::COND_ALPHA));
	var_ptr_type& betaVar = VBMEngine::get_engine().get_variable(
			get_var_by_role(InverseGammaModel::COND_BETA));
	float alphaMean = alphaVar->moment(1);
	float betaMean = betaVar->moment(1);
	/// the natural statistics in original model parameters are
	/// [-\alpna - 1, -\beta]
	DistParamBundle parentStat(2, true);
	parentStat[0] = -alphaMean - 1;
	parentStat[1] = -betaMean;
	return parentStat;
}

void InverseGammaModel::_process_child_message(DistParamBundle& message) {
	if (message[0].m_vec.size() > 1) {
		message[0] = (float)arma::accu(message[0].m_vec);
		message[1] = (float)arma::accu(message[1].m_vec);
	}
}

} /* namespace bn */
