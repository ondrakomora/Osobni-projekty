#pragma once
#include <vector>
#include <armadillo>

using namespace arma;

//Abstract class representing loss functions
class Loss {
public:

	virtual double compute_loss(mat output, mat target) = 0;
	// Returns gradient of loss function with respect to output layer activations.
	// Gradients are computed column-wise
	virtual mat gradient(mat output, mat target) = 0;

};

// Mean squared error
class MSE : public Loss {
public:
	MSE() {}
public:
	virtual double compute_loss(mat output, mat target) {
		double l = accu((output - target) % (output - target));
		return l / target.n_cols;
	}

	virtual mat gradient(mat output, mat target) {
		return (output - target);
	}
};

// Cross entropy
class Cross_entropy : public Loss {
public:
	virtual double compute_loss(mat output, mat target) {
		// Term for numerical stability
		double eps = 0.00000000001;
		double loss = accu(-target % log(output + eps));
		return loss / target.n_cols;
	}

	virtual mat gradient(mat output, mat target) {
		// Term for numerical stability
		double eps = 0.00000000001;
		return target / (output + eps);
	}


};
