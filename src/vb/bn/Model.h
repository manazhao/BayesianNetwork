/*
 * Model.h
 *
 *  Created on: Feb 22, 2014
 *      Author: qzhao2
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Variable.h"
#include <map>
#include <set>
using namespace std;
using namespace prob;

namespace bn {
void repeat_vector(vec & origVec, size_t const& newLength);

typedef shared_ptr<BaseVariable> var_ptr_type;
typedef map<string, set<string> > var_rel_map;
typedef map<string, var_ptr_type> var_map;

/**
 * base class for all probability models
 */
class ProbModel {
	friend class VBMEngine;
public:
	/// map node to role
	typedef map<string, size_t> var_role_map;
	typedef map<size_t, var_ptr_type> role_var_map;
	typedef set<string> var_set;
	/// maps a set of variables to a role
	typedef map<size_t, var_set> role_var_set_map;
protected:
	NatParamVec m_prior;
	var_role_map m_varRoleMap;
	role_var_set_map m_roleVarSetMap;
	var_set m_childVarSet;
	var_ptr_type m_targetVarPtr;
	bool m_isObserved;
protected:
	virtual void _process_child_message(NatParamVec message){

	}
	virtual NatParamVec _update_from_child();
	virtual NatParamVec _update_from_parent() = 0;
	void _add_child_var(string const& varId) {
		m_childVarSet.insert(varId);
	}

public:
	ProbModel(var_ptr_type const& targetVar = var_ptr_type(), bool isObserved = false);
	virtual void add_parent_var(string const& varId, size_t role);
	string get_var_by_role(size_t role) {
		var_set& varSet = m_roleVarSetMap[role];
		if (varSet.empty()) {
			return string();
		}
		return *(varSet.begin());
	}

	virtual NatParamVec to_parent_message(string const& varId) = 0;
	void setPrior(NatParamVec const& natStat){
		m_prior = natStat;
	}
	void update();

	virtual ~ProbModel() {
	}
};

}

#endif /* MODEL_H_ */
