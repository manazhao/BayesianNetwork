/*
 * UserNode.h
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#ifndef USERNODE_H_
#define USERNODE_H_

#include "../vb/Node.h"
#include "../vb/Probability.h"

using namespace vb;
namespace mf {

enum {
	USER_NODE = 1,
	ITEM_NODE = 2,
	FEATURE_NODE = 3,
	USER_PRIOR_NODE = 4,
	ITEM_PRIOR_NODE = 5,
	FEATURE_PRIOR_NODE = 6,
	FEATURE_HYPER_VAR_NODE = 7
};

class UserNode: public vb::Node {
protected:
	size_t m_latDim;
	GaussianDist<DIAG> m_dist;
public:
	UserNode(unsigned int id, size_t latDim);
	virtual void infer();
	virtual ~UserNode();
};

class UserPriorNode: public vb::Node {
protected:
	size_t m_latDim;
	GaussianDist<SPHERE> m_dist;
public:
	UserPriorNode(unsigned int id, size_t latDim):Node(id,USER_PRIOR_NODE),m_latDim(latDim),m_dist(latDim){}
	virtual void infer();
};

} /* namespace mf */

#endif /* USERNODE_H_ */
