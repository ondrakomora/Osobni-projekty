#pragma once

#include <armadillo>
#include <cmath>

using namespace arma;

// Implemented Kronecker's delta function
double kronecker(int i, int j) {
	return (i == j) ? 1 : 0;
}

// Abstract class representing activations
class Activation {
public:
	// Applies activation function on columns of inputed matrix
	virtual mat activation(mat in) = 0;

	// Computes derivatives of activation function with respect to inputs from inputed matrix. 
	// Output is either matrix with the same shape as input matrix, in this case derivatives are computed column-wise, 
	// or matrix of shape (in.n_row^2,in.n_cols) if activation value is dependend on all other activations in same layer.
	// Example of such activation function is softmax
	virtual mat derivative(mat in) = 0;
};

class Sigmoid : public Activation {
public:
	virtual mat activation(mat in) {
		return in.for_each([](mat::elem_type& x) {x = 1 / (1 + exp(-x));});
	}

	virtual mat derivative(mat in) {
		return activation(in) % (1 - activation(in));
	}
};

class Tanh : public Activation {
public:
	virtual mat activation(mat in) {
		return tanh(in);
	}

	virtual mat derivative(mat in) {
		return 1 - tanh(in) % tanh(in);
	}
};

class ReLU : public Activation {
public:
	virtual mat activation(mat in) {
		return in.for_each([](mat::elem_type& x) {x = fmax(0, x);});
	}

	virtual mat derivative(mat in) {
		return in.for_each([](mat::elem_type& x) {x = (x > 0 ? 1 : 0);});;
	}
};

class SoftMax : public Activation {
public:
	virtual mat activation(mat in) {
		in.each_col([&](vec& v) {
			double s = 0;
			double max = v.max();
			v.for_each([&](vec::elem_type& x) {
				s += exp(x - max);
				x = exp(x - max);
				});
			v /= s;
			});
		return in;
	}

	virtual mat derivative(mat in) {
		mat out(in.n_rows * in.n_rows, in.n_cols);
		in = activation(in);
		for (int i = 0;i < out.n_cols;i++) {
			mat m(in.n_rows, in.n_rows);
			for (int j = 0;j < m.n_rows;j++) {
				for (int k = 0;k <= j;k++) {
					m(j, k) = in.col(i)(j) * (kronecker(j, k) - in.col(i)(k));
					m(k, j) = m(j, k);
				}
			}
			out.col(i) = vectorise(m, 1).t();
		}
		return out;
	}
};

class Linear : public Activation {
public:
	virtual mat activation(mat in) {
		return in;
	}
	virtual mat derivative(mat in) {
		return mat(in.n_rows, in.n_cols, fill::ones);
	}
};
