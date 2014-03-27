/*
 * Node.h
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <sstream>
#include <set>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace boost;

namespace vb {

class Node {
	friend class VBNetwork;
public:
	enum {DEFAULT_NODE};
protected:
	struct NodePtrCompare{
		bool operator()(shared_ptr<Node> const& node1, shared_ptr<Node> const& node2)const{
			return node1->m_key < node2->m_key;
		}
	};

	typedef shared_ptr<Node> node_ptr;
	typedef set<node_ptr, NodePtrCompare > node_set;
	typedef node_set::iterator node_set_iterator;
	typedef node_set::const_iterator node_set_const_iterator;
protected:
	string m_key;
	size_t m_id;
	unsigned int m_type;
	node_set m_parentNodes;
	node_set m_childNodes;
public:
	Node(size_t const& id = size_t(), unsigned int type = DEFAULT_NODE);

	void addParentNode(node_ptr const& node){
		m_parentNodes.insert(node);
	}

	void addChildNode(node_ptr const& node){
		m_childNodes.insert(node);
	}

	size_t getId() const{
		return m_id;
	}

	unsigned int getType() const{
		return m_type;
	}

	string getKey() const{
		return m_key;
	}

	virtual void infer() = 0;
	virtual ~Node();
};

template <typename T>
class SimpleNode: public Node{
public:
	typedef T node_value_type;
protected:
	T m_val;
public:
	SimpleNode(size_t const& id = string(), unsigned int type=Node::DEFAULT_NODE, T const& val = T()):Node(id,type),m_val(val){}
	virtual void infer(){}
};

} /* namespace vb */

#endif /* NODE_H_ */
