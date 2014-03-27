/*
 * VBMEngine.cpp
 *
 *  Created on: Feb 23, 2014
 *      Author: qzhao2
 */
#include "VBMEngine.h"
#include "GaussianModel.h"
#include "InverseGammaModel.h"
#include "HyperParamModel.h"

namespace bn {

/// definition of global engine instance
VBMEngine VBMEngine::G_ENGINE_INSTANCE;

void VBMEngine::infer() {
	cout << "========= start VBM on the given network with: "
			<< m_varModelMap.size() << " nodes =========" << endl;
	for (size_t iter = 0; iter < 50; iter++) {
		cout << "---- iter: " << iter << " ----" << endl;
		for (var_model_map::iterator modelIter = m_varModelMap.begin();
				modelIter != m_varModelMap.end(); ++modelIter) {
			string varId = modelIter->first;
			model_ptr_type varModel = modelIter->second;
			varModel->update();
		}
	}

	for (var_model_map::iterator modelIter = m_varModelMap.begin();
			modelIter != m_varModelMap.end(); ++modelIter) {
		string varId = modelIter->first;
		model_ptr_type& varModel = modelIter->second;
		if (!varModel->m_isObserved) {
			cout << *(varModel->m_targetVarPtr);
		}
	}
}


void test_engine() {
//#define KNOWN_VARIANCE
//#define KNOWN_MEAN
	/// generate samples from standard Gaussian distribution and infer the mean and variance using Variational Bayesian Message passing
	size_t numSamples = 1000;
	vec samples = randn<vec>(numSamples);
	samples *= 2;
	samples += 1.5;
	cout << "mean:" << arma::mean(samples) << endl;
	cout << "sample variance:" << arma::var(samples) << endl;
	/// first construct all nodes
	VBMEngine& ENGINE = VBMEngine::get_engine();
#ifndef KNOWN_MEAN
	ENGINE.add_model(HyperParameter<Gaussian>("mu_0", "hyper mean", (float) 0));
	ENGINE.add_model(
			HyperParameter<InverseGamma>("var_0", "hyper variance", (float) 1e6));
	ENGINE.add_model(GaussianModel("mu", "mean of Gaussian"));
#else
	ENGINE.add_model(HyperParameter<Gaussian>("mu","mean of Gaussian",1.5));
#endif
#ifndef KNOWN_VARIANCE
	ENGINE.add_model(HyperParameter<Gaussian>("alpha_0", "hyper alpha", (float) 1));
	ENGINE.add_model(HyperParameter<Gaussian>("beta_0", "hyper beta", (float) 1));
	ENGINE.add_model(InverseGammaModel("var", "variance of Gaussian"));
#else
	ENGINE.add_model(HyperParameter<InverseGamma>("var","variance",(float)4));
#endif

	/// add observations
	for (size_t i = 0; i < numSamples; i++) {
		stringstream ss;
		ss << "o_" << i;
		ENGINE.add_model(GaussianModel(ss.str(), ss.str(), samples(i)));
	}

#ifndef KNOWN_MEAN
	/// add models
	model_ptr_type& meanModel = ENGINE.get_model("mu");
	meanModel->add_parent_var("mu_0", GaussianModel::COND_MEAN);
	meanModel->add_parent_var("var_0", GaussianModel::COND_VAR);
#endif
#ifndef KNOWN_VARIANCE
	model_ptr_type& varModel = ENGINE.get_model("var");
	varModel->add_parent_var("alpha_0", InverseGammaModel::COND_ALPHA);
	varModel->add_parent_var("beta_0", InverseGammaModel::COND_BETA);
#endif
	/// add the observation models
	for (size_t i = 0; i < numSamples; i++) {
		stringstream ss;
		ss << "o_" << i;
		model_ptr_type& obsModel = ENGINE.get_model(ss.str());
		obsModel->add_parent_var("mu", GaussianModel::COND_MEAN);
		obsModel->add_parent_var("var", GaussianModel::COND_VAR);
	}
	ENGINE.infer();
}

}
