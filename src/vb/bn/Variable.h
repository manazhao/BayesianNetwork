/*
 * bn.h
 *
 *  Created on: Feb 22, 2014
 *      Author: qzhao2
 */

#ifndef BN_H_
#define BN_H_
#include <vector>
#include <ostream>
#include "../prob/Distribution.h"
#include "../prob/Gaussian.h"
#include "../prob/InverseGamma.h"
#include "../prob/MVInverseGamma.h"

namespace bn {
using namespace prob;
using namespace std;

class BaseVariable;
ostream& operator<<(ostream&, BaseVariable&);

template<class T> class Variable;

template<typename T>
ostream& operator<<(ostream &, Variable<T>&);

class BaseVariable {
	friend class VBMEngine;
	friend class ProbModel;
	friend class ostream;
	friend ostream& operator<<(ostream&, BaseVariable&);
protected:
	string m_id;
	string m_name;
public:
	BaseVariable(string const& id, string const& name) :
			m_id(id), m_name(name) {
	}
	virtual void updateOnMessage(NatParamVec const& rhs) = 0;
	virtual void reset() = 0;
	virtual size_t size() const = 0;
	virtual NatParamVec moment(size_t const& order) = 0;
	virtual NatParamVec suff_mean(size_t const& idx) = 0;
	virtual ostream& print(ostream& oss) = 0;
	virtual ~BaseVariable() {
	}

};

template<typename T>
class Variable: public BaseVariable {
	friend ostream& operator<<(ostream & oss, Variable<T>& var) {
		oss << endl;
		oss << "---- dump of variable: " << var.m_name << " ----";
		oss << endl;
		oss << var.m_var;
		oss << endl;
		return oss;
	}
public:
	typedef T distribution_type;
protected:
	distribution_type m_var;
public:
	Variable(string const& id = string(), string const& name = string(),
			T const& var = T()) :
			BaseVariable(id, name), m_var(var) {

	}


	virtual void reset() {
		m_var.reset();
	}

	 size_t size() const{
		return m_var.size();
	}

	T& getDistribution(){
		return m_var;
	}
	virtual NatParamVec moment(size_t const& order){
		return m_var.moment(order);
	}
	virtual NatParamVec suff_mean(size_t const& idx){
		return m_var.suff_mean(idx);
	}

	virtual void updateOnMessage(NatParamVec const& rhs){
		m_var = rhs;
	}

	ostream& print(ostream& oss) {
		oss << *this;
		return oss;
	}
};


void test_variable();

}

#endif /* BN_H_ */
