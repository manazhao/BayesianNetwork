/*
 * MVInverseGammaModel.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: qzhao2
 */

#include "MVInverseGammaModel.h"
#include "VBMEngine.h"

namespace bn {

MVInverseGammaModel::MVInverseGammaModel(string const& id, string const& name)
:ProbModel(var_ptr_type(new var_type(id, name, dist_type())),false){
	// TODO Auto-generated constructor stub

}

NatParamVec MVInverseGammaModel::_update_from_parent(){
	var_ptr_type& alphaVar = VBMEngine::get_engine().get_variable(get_var_by_role(MVInverseGammaModel::COND_ALPHA));
	var_ptr_type& betaVar = VBMEngine::get_engine().get_variable(get_var_by_role(MVInverseGammaModel::COND_BETA));
	size_t dim = m_targetVarPtr->size();
	vec alphaMean = alphaVar->moment(1);
	vec betaMean = betaVar->moment(1);
	if(alphaMean.size() == 1){
		repeat_vector(alphaMean,dim);
	}
	if(betaMean.size() == 1){
		repeat_vector(betaMean,dim);
	}
	/// the natural statistics in original model parameters are
	/// [-\alpna - 1, -\beta]
	NatParamVec parentStat((size_t)dim * 2,true);
	parentStat.m_vec.cols(0,dim-1) = -alphaMean - 1;
	parentStat.m_vec.cols(dim,2 * dim - 1) = -betaMean;
	return parentStat;
}

MVInverseGammaModel::~MVInverseGammaModel() {
	// TODO Auto-generated destructor stub
}

} /* namespace bn */
