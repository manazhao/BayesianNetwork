/*
 * Model.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: qzhao2
 */

#include "Model.h"
#include "VBMEngine.h"

namespace bn {
void repeat_vector(vec & origVec, size_t const& newLength) {
	assert(newLength > 0);
	float val = origVec(0);
	origVec = vec(newLength);
	origVec.fill(val);
}

ProbModel::ProbModel(var_ptr_type const& targetVarPtr, bool isObserved) :
m_targetVarPtr(targetVarPtr), m_isObserved(isObserved) {
}

void ProbModel::add_parent_var(string const& varId, size_t role) {
	m_varRoleMap[varId] = role;
	m_roleVarSetMap[role].insert(varId);
	/// add an edge from parent node to current node
	VBMEngine& ENGINE = VBMEngine::get_engine();
	model_ptr_type& parentModel = ENGINE.get_model(varId);
	parentModel->_add_child_var(m_targetVarPtr->m_id);
}


NatParamVec ProbModel::_update_from_child() {
	// reset the target value natural statistics
	VBMEngine& ENGINE = VBMEngine::get_engine();
	/// get statistics from child node and add them to the target variable
	NatParamVec resultMessage;
	for (var_set::iterator iter = m_childVarSet.begin();
			iter != m_childVarSet.end(); ++iter) {
		string childVarId = *iter;
		NatParamVec childMessage =
				ENGINE.get_model(childVarId)->to_parent_message(m_targetVarPtr->m_id);
		_process_child_message(childMessage);
		resultMessage += childMessage;
	}
	return resultMessage;
}

void ProbModel::update() {
	if (!m_isObserved) {
		/// reset the variable status
		m_targetVarPtr->reset();
		NatParamVec parentMessage = _update_from_parent();
		NatParamVec childMessage = _update_from_child();
		/// include the prior information
		NatParamVec resultMessage = parentMessage + childMessage + m_prior;
		resultMessage.m_is_canonical = true;
		m_targetVarPtr->updateOnMessage(resultMessage);
	}
}

}

