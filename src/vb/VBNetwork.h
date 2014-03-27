/*
 * VBNetwork.h
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#ifndef VBNETWORK_H_
#define VBNETWORK_H_
#include "Node.h"
#include <map>

namespace vb {

struct NodeTypePriority {
	unsigned int m_nodeType;
	unsigned int m_priority;
	NodeTypePriority(unsigned int nodeType = Node::DEFAULT_NODE,
			unsigned int priority = 0) :
			m_nodeType(nodeType), m_priority(priority) {
	}
	bool operator<(NodeTypePriority const& rhs) const {
		return m_priority < rhs.m_priority;
	}
};

class VBNetwork {
public:
	typedef map<string, shared_ptr<Node> > node_map;
	typedef map<unsigned int, Node::node_set> node_type_map;
protected:
	node_map m_nodeMap;
	node_type_map m_nodeTypeMap;
	set<NodeTypePriority> m_nodePriority;
	unsigned int m_numIter;
	string m_appName;
protected:
	void _nodeInfer();
public:
	VBNetwork(unsigned int numIter = 10,
			string const& appName = string(
					"variational Bayesian network inference"));
	void setPriority(NodeTypePriority const& nodePrior) {
		m_nodePriority.insert(nodePrior);
	}

	shared_ptr<Node>& addNode(shared_ptr<Node> const& nodePtr) {
		/// get the composit key of the node
		string nodeKey = nodePtr->getKey();
		if (m_nodeMap.find(nodeKey) == m_nodeMap.end()) {
			m_nodeMap[nodeKey] = nodePtr;
			unsigned int nodeType = nodePtr->getType();
			m_nodeTypeMap[nodeType].insert(nodePtr);
		}
		return m_nodeMap[nodeKey];
	}

	shared_ptr<Node> operator[](string const& nodeKey) {
		return m_nodeMap[nodeKey];
	}

	void addEdge(shared_ptr<Node> const& fromNode,
			shared_ptr<Node> const& toNode) {
		shared_ptr<Node>& addedFrom = addNode(fromNode);
		shared_ptr<Node>& addedTo = addNode(toNode);
		/// add an edge between them
		addedFrom->addChildNode(toNode);
		addedTo->addChildNode(fromNode);
	}
	void infer();
	virtual ~VBNetwork();
};

} /* namespace vb */

#endif /* VBNETWORK_H_ */
