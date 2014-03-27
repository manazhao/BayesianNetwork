/*
 * ItemNode.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: qzhao2
 */

#include "ItemNode.h"

namespace mf {

ItemNode::ItemNode(unsigned int id, size_t latDim)
:Node(id,ITEM_NODE)
,m_latDim(latDim)
,m_posDist(latDim){
	// TODO Auto-generated constructor stub

}

ItemNode::~ItemNode() {
	// TODO Auto-generated destructor stub
}

void ItemNode::infer(){

}

} /* namespace mf */
