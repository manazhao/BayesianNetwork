/*
 * FeatureNode.h
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#ifndef FEATURENODE_H_
#define FEATURENODE_H_
#include "UserNode.h"
#include "../vb/Probability.h"

using namespace vb;
namespace mf {

class FeatureNode: public vb::Node {
protected:
	size_t m_latDim;
	GaussianDist<DIAG> m_dist;
public:
	FeatureNode(unsigned int id, size_t latDim);
	virtual void infer();
	virtual ~FeatureNode();
};


} /* namespace mf */

#endif /* FEATURENODE_H_ */
