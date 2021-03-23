#pragma once
#include <vector>
#include <armadillo>

using namespace arma;

//Abstract class representing loss functions
class Loss{
	public:
		virtual double loss(field<vec> predictions, field<vec> actual)=0;
		virtual vec gradient(vec prediction, vec actual) = 0;

};

class MSE : public Loss {
public:
	MSE() {}
public:
	virtual double loss(field<vec> predictions, field<vec> actual) {
		double loss = 0;
		for (int i = 0;i < predictions.n_elem;i++) {
			loss += sum((predictions(i) - actual(i)) % (predictions(i) - actual(i)));
		}
		return loss / (2*predictions.n_elem);
	}

	virtual vec gradient(vec prediction, vec actual) {
		return (prediction - actual);
	}
};

class Cross_entropy : public Loss {
public:
	virtual double loss(field<vec> predictions, field<vec> actual) {
		double loss = 0;
		for (int i = 0;i < predictions.n_elem;i++) {
			loss += -sum(actual(i) * log(predictions(i)));
		}
		return loss / predictions.n_elem;
	}

	virtual vec gradient(vec prediction, vec actual) {
		return -actual / prediction;
	}
};