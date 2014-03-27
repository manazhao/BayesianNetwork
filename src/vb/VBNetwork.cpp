/*
 * VBNetwork.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#include "VBNetwork.h"

namespace vb {

VBNetwork::VBNetwork(unsigned int numIter, string const& appName):m_numIter(numIter),m_appName(appName) {
	// TODO Auto-generated constructor stub

}

VBNetwork::~VBNetwork() {
	// TODO Auto-generated destructor stub
}

void VBNetwork::_nodeInfer(){
	for(set<NodeTypePriority>::const_iterator iter = m_nodePriority.begin(); iter != m_nodePriority.end(); ++iter){
		cout << "-------------" << "infer for node of type:" << iter->m_nodeType << "-------------" << endl;
		unsigned int nodeType = iter->m_nodeType;
		Node::node_set& nodes = m_nodeTypeMap[nodeType];
		cout << "# of nodes to update:" << nodes.size() << endl;
		for(Node::node_set_iterator nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter){
			Node::node_ptr node = *nodeIter;
			cout << "update node:" << node->m_id << endl;
			node->infer();
		}
	}
}

void VBNetwork::infer(){
	cout << "-------------" << "Variational Bayesian Inference" << endl;
	for(unsigned int i = 0; i < m_numIter; i++){
		_nodeInfer();
	}
}

} /* namespace vb */
