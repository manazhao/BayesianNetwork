/*
 * InverseGammaModel.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: qzhao2
 */

#include "InverseGammaModel.h"
#include "VBMEngine.h"

namespace bn {

NatParamVec InverseGammaModel::_update_from_parent() {
	var_ptr_type& alphaVar = VBMEngine::get_engine().get_variable(
			get_var_by_role(InverseGammaModel::COND_ALPHA));
	var_ptr_type& betaVar = VBMEngine::get_engine().get_variable(
			get_var_by_role(InverseGammaModel::COND_BETA));
	float alphaMean = alphaVar->moment(1);
	float betaMean = betaVar->moment(1);
	/// the natural statistics in original model parameters are
	/// [-\alpna - 1, -\beta]
	NatParamVec parentStat((size_t) 2, true);
	parentStat[0] = -alphaMean - 1;
	parentStat[1] = -betaMean;
	return parentStat;
}

void InverseGammaModel::_process_child_message(NatParamVec& message) {
	if (message.size() > 1) {
		/// from mv child nodes
		NatParamVec messageBk = message;
		size_t dim = messageBk.size() / 2;
		message.m_vec = vec(2);
		message.m_vec(0) = arma::accu(messageBk.m_vec.cols(0, dim - 1));
		message.m_vec(1) = arma::accu(messageBk.m_vec.cols(dim, 2 * dim - 1));
	}
}

} /* namespace bn */
