#pragma once

using namespace arma;

//Abstract class representing regularization
class Regularizer
{
public:
	virtual field<mat> penalty(field<mat> weights) = 0;
	virtual field<vec> penalty(field<vec> biases) = 0;
};

// L2 regularization penalizing loss with sum of squares of all weights and biases
class L2 : public Regularizer {
private:
	//Regularization term
	double lambda;

public:
	L2(double lambda){
		this->lambda = lambda;
	}

public:
	// Returns penalty for weights
	virtual field<mat> penalty(field<mat> weights){
		field<mat> out = weights;
		out.for_each([&](mat& m) {m *= lambda;});
		return out;
	}

	// Overload for biases
	virtual field<vec> penalty(field<vec> biases) {
		field<vec> out = biases;
		out.for_each([&](mat& m) {m *= lambda;});
		return out;
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
	// Returns penalty for weights
	virtual field<mat> penalty(field<mat> weights) {
		field<mat> out = weights;
		out.for_each([&](mat& m) {
			m.for_each([](mat::elem_type& x) {x = (x > 0 ? 1 : (x < 0 ? -1 : 0)); });
			m *= lambda;
		});
		return out;
	}

	// Overload for biases
	virtual field<vec> penalty(field<vec> biases) {
		field<vec> out = biases;
		out.for_each([&](vec& v) {
			v.for_each([](vec::elem_type& x) {x = (x > 0 ? 1 : (x < 0 ? -1 : 0));});
			v *= lambda;
		});
		return out;
	}
};

// Mix of L1 and L2 regularization. Ratio of L1 and L2 is determined by L1_ratio attribute
class Elastic_net : public Regularizer {
private:
	// Regularization term
	double lambda;
	// How much of L1 regularization is present
	double l1_ratio;

public:
	Elastic_net(double lambda, double l1_ratio) {
		this->lambda = lambda;
		this->l1_ratio = l1_ratio;
	}

public:
	// Returns penalty for weights
	virtual field<mat> penalty(field<mat> weights) {
		field<mat> out = weights;
		out.for_each([&](mat& m) {
			m.for_each([&](mat::elem_type& x) {
				double s = (1-l1_ratio) * x;
				s += l1_ratio * (x > 0 ? 1 : (x < 0 ? -1 : 0));
				x = s*lambda;
			});
		});
		return out;
	}

	// Overload for biases
	virtual field<vec> penalty(field<vec> biases) {
		field<vec> out = biases;
		out.for_each([&](vec& v) {
			v.for_each([&](vec::elem_type& x) {
				double s = (1 - l1_ratio) * x;
				s += l1_ratio * (x > 0 ? 1 : (x < 0 ? -1 : 0));
				x = s * lambda;
				});
			});
		return out;
	}
};

class None : public Regularizer {
public:
	None() {}

public:
	virtual field<mat> penalty(field<mat> weights) {
		field<mat> out(weights.n_elem);
		for (int i = 0;i < weights.n_elem;i++) { out(i) = mat(weights(i).n_rows, weights(i).n_cols, fill::zeros); }
		return out;
	}

	virtual field<vec> penalty(field<vec> biases) {
		field<vec> out(biases.n_elem);
		for (int i = 0;i < biases.n_elem;i++) { out(i) = vec(biases(i).n_elem,fill::zeros); }
		return out;
	}
};

