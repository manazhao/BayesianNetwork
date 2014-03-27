/*
 * ItemNode.h
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#ifndef ITEMNODE_H_
#define ITEMNODE_H_
#include "UserNode.h"
#include "../vb/Probability.h"

using namespace vb;

namespace mf {

class ItemNode: public vb::Node {
protected:
	size_t m_latDim;
	GaussianDist<DIAG> m_posDist;
public:
	ItemNode(unsigned int id, size_t latDim);
	virtual void infer();
	virtual ~ItemNode();
};

} /* namespace mf */

#endif /* ITEMNODE_H_ */
