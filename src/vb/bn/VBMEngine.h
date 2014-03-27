/*
 * VBMEngine.h
 *
 *  Created on: Feb 23, 2014
 *      Author: qzhao2
 */

#ifndef VBMENGINE_H_
#define VBMENGINE_H_
#include "Model.h"

namespace bn{

typedef shared_ptr<ProbModel> model_ptr_type;
typedef map<string, model_ptr_type> var_model_map;

/**
 * Variational Bayesian Message Inference Engine
 */
class VBMEngine {
	friend class ProbModel;
protected:
	/// defines relations between variables
	var_rel_map m_varRelMap;
	/// defines variable and model map
	var_model_map m_varModelMap;
	static VBMEngine G_ENGINE_INSTANCE;

	VBMEngine() {}
	VBMEngine(VBMEngine const&);

	model_ptr_type& _add_model(model_ptr_type const& modelPtr){
		string targetVarId = modelPtr->m_targetVarPtr->m_id;
		m_varModelMap[targetVarId] = modelPtr;
		return m_varModelMap[targetVarId];
	}

public:
	static VBMEngine& get_engine() {
		return G_ENGINE_INSTANCE;
	}


	template <typename T>
	model_ptr_type& add_model(T const& model){
		return _add_model(model_ptr_type(new T(model)));
	}

	var_ptr_type& get_variable(string const& varId) {
		assert(m_varModelMap.find(varId) != m_varModelMap.end());
		return m_varModelMap[varId]->m_targetVarPtr;
	}

	model_ptr_type& get_model(string const& varId) {
		assert(m_varModelMap.find(varId) != m_varModelMap.end());
		return m_varModelMap[varId];
	}

	void infer();
};

void test_engine();

}


#endif /* VBMENGINE_H_ */
