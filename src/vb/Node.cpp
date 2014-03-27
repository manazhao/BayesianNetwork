/*
 * Node.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#include "Node.h"

namespace vb {

Node::Node(size_t const& id , unsigned int type)
:m_id(id)
,m_type(type){
	// TODO Auto-generated constructor stub
	stringstream oss;
	oss << m_type << "_" << m_id;
	m_key = oss.str();
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

} /* namespace vb */
