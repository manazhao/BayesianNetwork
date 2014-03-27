/*
 * FeatureNode.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#include "FeatureNode.h"

namespace mf {

FeatureNode::FeatureNode(unsigned int id, size_t latDim)
:Node(id,FEATURE_NODE)
,m_latDim(latDim)
,m_dist(latDim){
	// TODO Auto-generated constructor stub

}

FeatureNode::~FeatureNode() {
	// TODO Auto-generated destructor stub
}

void FeatureNode::infer(){

}

} /* namespace mf */
