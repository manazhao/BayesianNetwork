#ifndef __PROBABILITY_H__
#define __PROBABILITY_H__
#include <armadillo>
#include <assert.h>

using namespace arma;
using namespace std;

namespace vb{

enum gaussian_dist_type {SINGLE,MULTI,SPHERE,DIAG};

template<gaussian_dist_type dist_type = MULTI>
class GaussianDist{
	friend class GaussianDist<DIAG>;
	friend class GaussianDist<SPHERE>;
protected:
	size_t m_dim;
	colvec m_mean;
	colvec m_meanInv;
	mat m_cov;
	mat m_covInv;
public:
	GaussianDist(size_t dim = 1):m_dim(dim),m_mean(dim,fill::zeros),m_cov(dim,dim,fill::zeros){
		m_meanInv = m_mean;
		m_covInv = m_cov;
	}

	void zero(){
		m_mean.fill(0.0);
		m_cov.fill(0.0);
		m_meanInv.fill(0.0);
		m_covInv.fill(0.0);
	}

	void randMean(){
		m_mean.randn();
	}

	void eyeCov(){
		m_cov.eye();
	}

	void setMean(colvec const& meanVec){
		assert(meanVec.size() == m_mean.size());
		m_mean = meanVec;
	}

	void setCov(mat const& cov){
		assert(m_cov.n_rows == cov.n_rows && m_cov.n_cols == cov.n_cols);
		m_cov = cov;
	}

	colvec const& mean()const{
		return m_mean;
	}

	mat const& cov()const{
		return m_cov;
	}

	void setInvMean(colvec const& meanVec){
		assert(meanVec.size() == m_mean.size());
		m_meanInv = meanVec;
	}

	void setInvCov(mat const& cov){
		assert(m_cov.n_rows == cov.n_rows && m_cov.n_cols == cov.n_cols);
		m_covInv = cov;
	}

	colvec const& invMean()const{
		return m_mean;
	}

	mat const& invCov()const{
		return m_cov;
	}

	GaussianDist operator*(GaussianDist const& rhs)const{
		GaussianDist resultDist(m_dim);
		resultDist.m_covInv = m_covInv + rhs.m_covInv;
		resultDist.m_meanInv = m_meanInv + rhs.m_meanInv;
		return resultDist;
	}

	GaussianDist& operator*=(GaussianDist const& rhs){
		if( this == &rhs){
			throw std::exception();
		}
		m_covInv += rhs.m_covInv;
		m_meanInv += rhs.m_meanInv;
		return *this;
	}

	void sync(bool toDist = true){
		if(toDist){
			m_cov = arma::inv(m_covInv);
			m_mean = m_cov * m_meanInv;
		}else{
			m_covInv = arma::inv(m_cov);
			m_meanInv = m_covInv * m_mean;
		}
	}
};

template<>
class GaussianDist<SPHERE>{
protected:
	size_t m_dim;
	colvec m_mean;
	colvec m_meanInv;
	float m_cov;
	float m_covInv;
public:
	GaussianDist(size_t dim=1):m_dim(dim),m_mean(dim,fill::zeros),m_cov(0){
		m_covInv = m_cov;
		m_meanInv = m_mean;
	}
	void randMean(){
		m_mean.randn();
	}

	void eyeCov(){
		m_cov = 1;
	}
	void zero(){
		m_mean.fill(0.0);
		m_cov = m_covInv = 0;
		m_meanInv.fill(0.0);
	}

	void setMean(colvec const& meanVec){
		assert(meanVec.size() == m_mean.size());
		m_mean = meanVec;
	}

	void setCov(float const& cov){
		m_cov = cov;
	}

	colvec const& mean()const{
		return m_mean;
	}

	float const& cov()const{
		return m_cov;
	}

	void setInvMean(colvec const& meanVec){
		assert(meanVec.size() == m_mean.size());
		m_meanInv = meanVec;
	}

	void setInvCov(float const& cov){
		m_covInv = cov;
	}

	colvec const& invMean()const{
		return m_mean;
	}

	float const& invCov()const{
		return m_cov;
	}


	operator GaussianDist<MULTI>(){
		GaussianDist<MULTI> resultDist(m_dim);
		resultDist.m_mean = m_mean;
		colvec tmpVec(m_dim);
		tmpVec.fill(m_cov);
		resultDist.m_cov.diag() = tmpVec;
		resultDist.m_meanInv = m_meanInv;
		tmpVec.fill(m_covInv);
		resultDist.m_covInv.diag() = tmpVec;
		return resultDist;
	}

	void sync(bool toDist = true){
		if(toDist){
			m_cov = 1/(m_covInv);
			m_mean = m_cov * m_meanInv;
		}else{
			m_covInv = 1/m_cov;
			m_meanInv = m_covInv * m_mean;
		}
	}

};

template<>
class GaussianDist<DIAG>{
protected:
	size_t m_dim;
	colvec m_mean;
	mat m_cov;
	colvec m_meanInv;
	mat m_covInv;
public:
	GaussianDist(size_t dim=1):m_dim(dim),m_mean(dim,fill::zeros),m_cov(dim,1,fill::zeros){
		m_meanInv = m_mean;
		m_covInv = m_cov;
	}

	GaussianDist(GaussianDist<MULTI> const& rhs){
		m_dim = rhs.m_dim;
		m_mean = rhs.m_mean;
		m_cov = rhs.m_cov.diag();
		m_meanInv = rhs.m_meanInv;
		m_covInv = 1/m_cov;
	}

	void zero(){
		m_mean.fill(0.0);
		m_cov.fill(0.0);
		m_meanInv.fill(0.0);
		m_covInv.fill(0.0);
	}

	void randMean(){
		m_mean.randn();
	}

	void eyeCov(){
		m_cov = 1;
	}

	operator GaussianDist<MULTI>(){
		GaussianDist<MULTI> resultDist(m_dim);
		resultDist.m_mean = m_mean;
		resultDist.m_cov.diag() = m_cov;
		resultDist.m_meanInv = m_meanInv;
		resultDist.m_covInv.diag() = m_covInv;
		return resultDist;
	}

	void setMean(colvec const& meanVec){
		assert(meanVec.size() == m_mean.size());
		m_mean = meanVec;
	}

	void setCov(mat const& cov){
		assert(m_cov.n_rows == cov.n_rows);
		if(cov.n_cols == m_dim){
			m_cov = cov.diag();
		}else{
			m_cov = cov;
		}
	}

	colvec const& mean()const{
		return m_mean;
	}

	mat const& cov()const{
		return m_cov;
	}

	void setInvMean(colvec const& meanVec){
		assert(meanVec.size() == m_mean.size());
		m_meanInv = meanVec;
	}

	void setInvCov(mat const& cov){
		assert(m_cov.n_rows == cov.n_rows);
		if(cov.n_cols > 1){
			m_covInv = cov.diag();
		}else{
			m_covInv = cov;
		}
	}

	colvec const& invMean()const{
		return m_mean;
	}

	mat const& invCov()const{
		return m_cov;
	}

	GaussianDist& operator=(GaussianDist<MULTI> const& rhs){
		m_mean = rhs.m_mean;
		m_cov = rhs.m_cov.diag();
		m_meanInv = rhs.m_meanInv;
		m_covInv = 1/m_cov;
		return *this;
	}

	void sync(bool toDist = true){
		if(toDist){
			m_cov = 1/(m_covInv);
			m_mean = m_cov % m_meanInv;
		}else{
			m_covInv = 1/m_cov;
			m_meanInv = m_covInv % m_mean;
		}
	}

};


template<>
class GaussianDist<SINGLE>{
protected:
	float m_mean;
	float m_cov;
	float m_meanInv;
	float m_covInv;
public:
	GaussianDist():m_mean(0),m_cov(0){
		m_meanInv = m_mean;
		m_covInv = m_cov;
	}

	void randMean(){
		m_mean = arma::randn();
	}

	void eyeCov(){
		m_cov = 1;
	}

	void setMean(float const& mean){
		m_mean = mean;
	}

	float const& mean()const{
		return m_mean;
	}

	void setCov(float const& cov){
		m_cov = cov;
	}

	float const& cov()const{
		return m_cov;
	}

	void setInvMean(float const& mean){
		m_meanInv = mean;
	}

	float const& invMean()const{
		return m_meanInv;
	}

	void setInvCov(float const& cov){
		m_covInv = cov;
	}

	float const& invCov()const{
		return m_covInv;
	}

	GaussianDist operator*(GaussianDist const& rhs) const{
		GaussianDist resultDist;
		resultDist.m_covInv = m_covInv + rhs.m_covInv;
		resultDist.m_meanInv = m_meanInv + rhs.m_meanInv;
		return resultDist;
	}

	GaussianDist& operator*=(GaussianDist const& rhs){
		if( this == &rhs){
			throw std::exception();
		}
		m_covInv += rhs.m_covInv;
		m_meanInv += rhs.m_meanInv;
		return *this;
	}

	void sync(bool toDist = true){
		if(toDist){
			m_cov = 1/(m_covInv);
			m_mean = m_cov * m_meanInv;
		}else{
			m_covInv = 1/m_cov;
			m_meanInv = m_covInv * m_mean;
		}
	}
};


}

#endif
