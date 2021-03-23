#pragma once
#include <armadillo>
#include <cmath>

using namespace arma;

// Abstract class representing activations
class Activation {
	public:
		virtual vec activation(vec in) = 0;
		virtual vec derivative(vec in) = 0;
};

class Sigmoid : public Activation {
public: 
	virtual vec activation(vec in) {
		vec out= in;
		out.for_each([](vec::elem_type& x) { x = 1 / (1+exp(-x));});
		return out;
	}

	virtual vec derivative(vec in) {
		vec out = activation(in) % (1 - activation(in));
		return out;
	}
};

class Tanh : public Activation {
public: 
	virtual vec activation(vec in) {
		vec out = in;
		out.for_each([](vec::elem_type& x) {x = tanh(x);});
		return out;
	}

	virtual vec derivative(vec in) {
		vec out = 1 - activation(in) % activation(in);
		return out;
	}
};

class ReLU : public Activation {
public: 
	virtual vec activation(vec in) {
		vec out = in;
		out.for_each([](vec::elem_type& x) {x = fmax(0, x);});
		return in;
	}

	virtual vec derivative(vec in) {
		vec out = in;
		out.for_each([](vec::elem_type& x) {x = (x > 0 ? 1 : 0);});;
		return out;
	}
};

class SoftMax : public Activation {
public:
	virtual vec activation(vec in) {
		vec out = in;
		double s = 0;
		out.for_each([&](vec::elem_type& x) {s += exp(-x);});
		out /= s;
		return out;
	}

	virtual vec derivative(vec in) {
		vec out = activation(in) % (1 - activation(in));
		return out;
	}
};

class Linear : public Activation {
public:
	virtual vec activaiton(vec in) {
		return in;
	}

	virtual vec derivative(vec in) {
		vec out = vec(size(in), fill::ones);
		return out;
	}
};