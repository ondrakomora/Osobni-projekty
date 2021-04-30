#pragma once

#include <armadillo>

using namespace arma;

//Abstract class representing regularization
class Regularizer
{
public:
	// Return penalty for weights and biases
	virtual field<mat> penalty(field<mat> weights) = 0;
};

// L2 regularization penalizing loss with sum of squares of all weights and biases
class L2 : public Regularizer {
private:
	//Regularization term
	double lambda;

public:
	L2(double lambda) {
		this->lambda = lambda;
	}

public:
	virtual field<mat> penalty(field<mat> weights) {
		return weights.for_each([&](mat& m) {m *= lambda;});
	}

};

// L1 regularization penalizes loss with sum of absolute values of all weights and biases
class L1 : public Regularizer {
	//Regularization term
private:
	double lambda;

public:
	L1(double lambda) {
		this->lambda = lambda;
	}

public:
	virtual field<mat> penalty(field<mat> weights) {
		return weights.for_each([&](mat& m) {
			m = sign(m) * lambda;
			});
	}

};

// Mix of L1 and L2 regularization. Ratio of L1 and L2 is determined by L1_ratio attribute
class Elastic_net : public Regularizer {
private:
	// Regularization term
	double lambda;
	// Ratio of L1 regularization present
	double l1_ratio;

public:
	Elastic_net(double lambda, double l1_ratio) {
		this->lambda = lambda;
		this->l1_ratio = l1_ratio;
	}

public:
	virtual field<mat> penalty(field<mat> weights) {
		return weights.for_each([&](mat& m) {
			m = lambda * (m * (1 - l1_ratio) + sign(m) * l1_ratio);
			});
	}

};


