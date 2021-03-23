#pragma once
#include <vector>
#include <Loss_functions.h>
#include <Activation_functions.h>
#include <Regularizer.h>
#include <armadillo>

using namespace arma;

class NeuralNetwork {
private:
	int layers;
	Col<int> architecture;
	Activation* act;
	Loss* loss;
	Regularizer* reg;
	field<mat> weights;
	field<vec> biases;
	bool clf;

public:

	// Simplest NN constructor
	NeuralNetwork(Col<int> architecture, Activation* act) {
		this->architecture = architecture;
		this->layers = architecture.n_elem;
		this->act = act;

		initialize_parameters();
	}


	// Constructor for NN with regularization
	NeuralNetwork(Col<int> architecture, Activation* act, Loss* loss, Regularizer* reg, bool clf) {

		this->architecture = architecture;
		this->layers = architecture.n_elem;
		this->clf = clf;
		this->act = act;
		this->loss = loss;
		this->reg = reg;

		initialize_parameters();
	}

	~NeuralNetwork() {
		architecture.clear();
		weights.clear();
		biases.clear();
		delete act;
		delete &loss;
		delete reg;
	};

	// Initializing NN's parameters
	void initialize_parameters() {
		this->weights.reset();
		this->biases.reset();

		field<mat> w(layers-1);
		field<vec> b(layers- 1);

		for (int i = 0;i < layers - 1;i++) {
			w(i) = mat(architecture(i + 1), architecture(i), fill::randn);
			b(i) = vec(architecture(i + 1), fill::randn);
		}
		
		this->weights = w;
		this->biases = b;
	}

	// Propagate vector through NN
	vec feed_forward(vec in) {
		vec out=in;
		for (int i = 0;i < layers-1;i++) {
			out = act->activation(weights(i) * out + biases(i));
		}
		return out;
	}

	// Propagate multiple vectors through NN
	field<vec> feed_forward(field<vec> in) {
		field<vec> out(in.n_elem);
		for (int i = 0;i < in.n_elem;i++) {
			out(i) = feed_forward(in(i));
		}
		return out;
	}

	field<vec> feed_forward_recorded(vec in) {
		field<vec> record(layers);
		record(0) = in;
		for (int i = 0;i < layers-1;i++) { record(i + 1) = weights(i) * act->activation(record(i)) + biases(i); }
		return record;
	}

	field<vec> back_propagate(field<vec> record,vec target) {
		field<vec> deltas(layers);
		deltas(layers - 1) = loss->gradient(act->activation(record(layers - 1)),target) % act->derivative(record(layers - 1));
		for (int i = layers - 2;i >= 0;i--) {
			deltas(i) = (weights(i).t() * deltas(i + 1)) % act->derivative(record(i));
		}
		return deltas;
	}

	void train_epoch(field<vec> train, field<vec> target, int batch_size, double alpha) {
		field<mat> weights_gradient = reg->penalty(weights);
		field<vec> biases_gradient = reg->penalty(biases);
		for (int i = 0;i < train.n_elem;i++) {
			field<vec> record = feed_forward_recorded(train(i));
			field<vec> deltas = back_propagate(record,target(i));
			for (int j = 0;j < layers-1;j++) {
				biases_gradient(j) += deltas(j+1)/batch_size;
				weights_gradient(j) += deltas(j+1) * act->activation(record(j)).t()/batch_size;
			}
			if ((i + 1) % batch_size == 0 || i==train.n_elem) {
				for (int i = 0;i < layers - 1;i++) {
					weights(i) -= alpha * weights_gradient(i);
					biases(i) -= alpha * biases_gradient(i);
				}
				field<mat> weights_gradient = reg->penalty(weights);
				field<vec> biases_gradient = reg->penalty(biases);
			}
		}
	}

	void train_epoch(field<vec> train, field<vec> target, double alpha) {
		field<mat> weights_gradient = reg->penalty(weights);
		field<vec> biases_gradient = reg->penalty(biases);
		for (int i = 0;i < train.n_elem;i++) {
			field<vec> record = feed_forward_recorded(train(i));
			field<vec> deltas = back_propagate(record,target(i));
			for (int j = 0;j < layers;j++) {
				biases_gradient(j) += deltas(j) / train.n_elem;
				weights_gradient(j) += deltas(j) * act->activation(record(j)) / train.n_elem;
			}
		}
		for (int i = 0;i < layers - 1;i++) {
			weights(i) += alpha * weights_gradient(i);
			biases(i) += alpha * biases_gradient(i);
		}
	}

	void fit(field<vec> train, field<vec> target, int batch_size, int epochs, double alpha) {	
		for (int i = 0;i < epochs;i++) {
			train_epoch(train, target, batch_size, alpha);
			printf("Epoch: %d\n", i + 1);
			weights.print();
			biases.print();
		}
	}
	
	void score(std::vector<float*> pred, std::vector<float*> actual){}

	void accuracy(std::vector<float*> pred, std::vector<float*> actual) {}

	void write() {
		printf("Weights:\n");
		weights.print();
		printf("Biases:\n");
		biases.print();
	}
};