/*
 * UserNode.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#include "UserNode.h"

namespace mf {

UserNode::UserNode(unsigned int id, size_t latDim) :
		Node(id, USER_NODE), m_latDim(latDim), m_dist(latDim) {
	// TODO Auto-generated constructor stub

}

UserNode::~UserNode() {
	// TODO Auto-generated destructor stub
}

void UserNode::infer() {
	/// reset the mean and covariance matrix to zero
	GaussianDist<MULTI> updatedDist(m_latDim);
	updatedDist.zero();
//	for(node_set_iterator iter = m_parentNodes.begin(); iter != m_parentNodes.end(); ++iter){
//		node_ptr pNode = *iter;
//		switch(pNode->getType()){
//		case USER_PRIOR_NODE:
//			shared_ptr<UserPriorNode>& priorNode = dynamic_cast<shared_ptr<UserPriorNode>& >(pNode);
//			updatedDist *= priorNode->m_dist;
//			break;
//		case FEATURE_NODE:
//			shared_ptr<FeatureNode>& featNode = dynamic_cast<shared_ptr<FeatureNode>& >(pNode);
//			updatedDist *= featNode->m_dist;
//		}
//	}
}

void UserPriorNode::infer() {

}

} /* namespace mf */
