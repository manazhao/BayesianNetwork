/*
 * ArmadilloSerrialization.hpp
 *
 *  Created on: Apr 25, 2014
 *      Author: qzhao2
 */

#ifndef ARMADILLOSERRIALIZATION_HPP_
#define ARMADILLOSERRIALIZATION_HPP_

#include <armadillo>
#include <boost/serialization/access.hpp>

using namespace arma;

namespace boost {
namespace serialization{

template<class Archive>
void save(Archive& ar, arma::vec const& v, unsigned int version){
	/// get the size
	size_t sz = v.size();
	ar & sz;
	for(size_t i = 0; i < sz; i++){
		ar & v(i);
	}
}

template<class Archive>
void load(Archive& ar, arma::vec const& v, unsigned int version){
	/// get the size
	size_t sz;
	v = vec(sz,fill::zeros);
	for(size_t i = 0; i < sz; i++){
		ar & v(i);
	}
}

template<class Archive>
void save(Archive& ar, arma::mat const& v, unsigned int version){
	/// get the size
	size_t nRow = v.n_rows;
	size_t nCol = v.n_cols;
	ar & nRow & nCol;
	/// save the data block
	for(size_t i = 0; i < v.size(); i++){
		ar & v(i);
	}
}

template<class Archive>
void load(Archive& ar, arma::mat const& v, unsigned int version){
	/// get the size
	size_t nRow;
	size_t nCol;
	ar & nRow & nCol;
	v = mat(nRow,nCol);
	for(size_t i = 0; i < nRow * nCol; i++){
		ar & v(i);
	}
}
}


};

#endif /* ARMADILLOSERRIALIZATION_HPP_ */
