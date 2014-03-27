/*
 * LinearGaussianModel.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: qzhao2
 */

#include "LinearGaussianModel.h"
#include "VBMEngine.h"

namespace bn {

template<class T>
NatParamVec LinearGaussianModel<T>::to_parent_message(string const& varId) {
	VBMEngine& ENGINE = VBMEngine::get_engine();
	var_ptr_type& varianceVar = ENGINE.get_variable(
			get_var_by_role(LinearGaussianModel<>::COND_VAR));
	size_t varRole = m_varRoleMap[varId];
	assert(varRole);
	NatParamVec message((size_t) 2, true);
	message[0] = m_targetVarPtr->moment(1);
	switch (varRole) {
	case LinearGaussianModel<>::COND_A: {
//		NatParamVec vSuffMean = varianceVar->suff_mean();
//		float vsf2 = vSuffMean[1]; /// the expectation of 1/\sigma^2
//		float bVarIMean = 0;
//		for (size_t i = 0; i < m_aVec.size(); i++) {
//			string& aVarId = m_aVec[i];
//			string& bVarId = m_bVec[i];
//			if (aVarId != varId) {
//				var_ptr_type& aVarPtr = ENGINE.get_variable(aVarId);
//				var_ptr_type& bVarPtr = ENGINE.get_variable(bVarId);
//				message[0] -= (aVarPtr->moment(1) * bVarPtr->moment(1));
//			} else {
//				var_ptr_type& bVarPtr = ENGINE.get_variable(bVarId);
//				bVarIMean = bVarPtr->moment(1);
//			}
//		}
//		message[0] *= (vsf2 * bVarIMean);
	}
		break;
	case LinearGaussianModel<>::COND_B: {
//		NatParamVec vSuffMean = varianceVar->suff_mean();
//		float vsf2 = vSuffMean[1]; /// the expectation of 1/\sigma^2
//		float aVarIMean = 0;
//		for (size_t i = 0; i < m_bVec.size(); i++) {
//			string& aVarId = m_aVec[i];
//			string& bVarId = m_bVec[i];
//			if (bVarId != varId) {
//				var_ptr_type& aVarPtr = ENGINE.get_variable(aVarId);
//				var_ptr_type& bVarPtr = ENGINE.get_variable(bVarId);
//				message[0] -= (aVarPtr->moment(1) * bVarPtr->moment(1));
//			} else {
//				var_ptr_type& aVarPtr = ENGINE.get_variable(aVarId);
//				aVarIMean = aVarPtr->moment(1);
//			}
//		}
//		message[0] *= (vsf2 * aVarIMean);
//	}
		break;
	case LinearGaussianModel<>::COND_VAR: {
		message[0] = -0.5;
//		NatParamVec ySuffMean = m_targetVarPtr->suff_mean();
//		message[1] -= (0.5 * ySuffMean[1]);
//		for(size_t i = 0; i < m_aVec.size(); i++){
//			string& aVarId = m_aVec[i];
//			string& bVarId = m_bVec[i];
//			var_ptr_type& aVarPtr = ENGINE.get_variable(aVarId);
//			var_ptr_type& bVarPtr = ENGINE.get_variable(bVarId);
//			NatParamVec aSuffMean = aVarPtr->suff_mean();
//			NatParamVec bSuffMean = bVarPtr->suff_mean();
//			message[1] += (ySuffMean[0] * aSuffMean[0] * bSuffMean[0]);
//			message[1] -= (0.5 * )
		}
	}
		break;
	}
}

template<class T>
NatParamVec LinearGaussianModel<T>::_update_from_parent() {
	VBMEngine& ENGINE = VBMEngine::get_engine();
//	var_ptr_type& varianceVar = ENGINE.get_variable(
//			get_var_by_role(LinearGaussianModel<>::COND_VAR));
//	NatParamVec vSuffMean = varianceVar->suff_mean();
//	float vsf2 = vSuffMean[1]; /// the expectation of 1/\sigma^2
	NatParamVec resultStat((size_t) 2, true);
//	for (size_t i = 0; i < m_aVec.size(); i++) {
//		string& aVarId = m_aVec[i];
//		string& bVarId = m_bVec[i];
//		var_ptr_type& aVarPtr = ENGINE.get_variable(aVarId);
//		var_ptr_type& bVarPtr = ENGINE.get_variable(bVarId);
//		resultStat[0] += (vsf2 * aVarPtr->moment(1) * bVarPtr->moment(1));
//	}
//	resultStat[1] = -0.5;
	return resultStat;
}

} /* namespace bn */
