#pragma once

#include <vector>
#include <Loss_functions.h>
#include <Activation_functions.h>
#include <Regularizers.h>
#include <Data_handler.h>
#include <armadillo>


using namespace arma;

// Function which computes derivative_matrix*matrix, 
// since given derivative_matrix could be of two different formats, viz Activation_functions.h
mat mul_derivative_matrix(mat derivatives, mat matrix) {
	if (derivatives.n_rows == matrix.n_rows) {
		return derivatives % matrix;
	}
	else {
		mat out(matrix.n_rows, matrix.n_cols);
		for (int i = 0;i < out.n_cols;i++) {
			mat m = reshape(derivatives.col(i), out.n_rows, out.n_rows);
			out.col(i) = m * matrix.col(i);
		}
		return out;
	}
}

class NeuralNetwork {
private:
	int layers;
	std::vector<int> architecture;
	std::vector<Activation*> acts;
	Loss* loss;
	Regularizer* reg;
	field<mat> weights;
	field<mat> biases;
	bool clf;
	bool regularize;

public:

	// Simplest NN constructor
	NeuralNetwork(std::vector<int> architecture, std::vector<Activation*> acts) {
		this->architecture = architecture;
		this->layers = architecture.size();
		this->acts = acts;
		this->regularize = false;

		initialize_parameters();
	}

	// Constructor for NN without regularization
	NeuralNetwork(std::vector<int> architecture, std::vector<Activation*> acts, Loss* loss, bool clf) {

		this->architecture = architecture;
		this->layers = architecture.size();
		this->clf = clf;
		this->acts = acts;
		this->loss = loss;
		this->regularize = false;

		initialize_parameters();
	}

	// Constructor for NN with regularization
	NeuralNetwork(std::vector<int> architecture, std::vector<Activation*> acts, Loss* loss, Regularizer* reg, bool clf) {

		this->architecture = architecture;
		this->layers = architecture.size();
		this->clf = clf;
		this->acts = acts;
		this->loss = loss;
		this->reg = reg;
		this->regularize = true;

		initialize_parameters();
	}

	// Destructor
	~NeuralNetwork() {
		architecture.clear();
		weights.clear();
		biases.clear();
		delete& acts;
		delete& loss;
		delete& reg;
	};

	// Initializing NN's parameters
private:
	void initialize_parameters() {
		this->weights.reset();
		this->biases.reset();

		field<mat> w(layers - 1);
		field<mat> b(layers - 1);

		for (int i = 0;i < layers - 1;i++) {
			w(i) = mat(architecture.at(i + 1), architecture.at(i), fill::randn);
			b(i) = mat(architecture.at(i + 1), 1, fill::randn);
		}

		this->weights = w;
		this->biases = b;
	}

private:
	// Method for updating model's parameters
	void update_parameters(field<mat> grad_weights, field<mat> grad_biases, double learn_rate) {
		if (regularize) {
			field<mat> weights_penalty = reg->penalty(weights);
			field<mat> biases_penalty = reg->penalty(biases);
			for (int i = 0;i < layers - 1;i++) {
				weights(i) -= learn_rate * (grad_weights(i) + weights_penalty(i));
				biases(i) -= learn_rate * (grad_biases(i) + biases_penalty(i));
			}
		}
		else {
			for (int i = 0;i < layers - 1;i++) {
				weights(i) -= learn_rate * grad_weights(i);
				biases(i) -= learn_rate * grad_biases(i);
			}
		}
	}

public:
	// Propagate multiple vectors through NN
	mat feed_forward(mat in) {
		for (int i = 0;i < layers - 1;i++) {
			in = weights(i) * in;
			in = acts.at(i)->activation(in.each_col() + biases(i));
		}
		return in;
	}

private:
	// Record activations at each layer for every sample. First element in field respresents activations on first layer,etc.
	// Individual values for each sample are stored in columns and before activation is aplied.
	field<mat> feed_forward_recorded(mat in) {
		field<mat> record(layers);

		record(0) = in;
		in = weights(0) * in;
		record(1) = in.each_col() + biases(0);

		for (int i = 1;i < layers - 1;i++) {
			in = weights(i) * acts.at(i - 1)->activation(record(i));
			record(i + 1) = in.each_col() + biases(i);
		}
		return record;
	}

private:
	// Propagates errors back through NN, computes gradients and stores them into given pointers.
	void back_propagate(field<mat> record, mat targets, field<mat>* w_grad, field<mat>* b_grad) {
		field<mat> gradient_weights(layers - 1);
		field<mat> gradient_biases(layers - 1);
		int batch_size = targets.n_cols;

		//mat deltas = loss->gradient(acts.at(layers-2)->activation(record(layers - 1)),targets) 
		//	% acts.at(layers-2)->derivative(record(layers - 1));

		/*mat matrix = loss->gradient(acts.at(layers - 2)->activation(record(layers - 1)),targets);
		mat derivative = acts.at(layers - 2)->derivative(record(layers - 1));

		mat deltas = mul_derivative_matrix(derivative,matrix);*/

		mat deltas = acts.at(layers - 2)->activation(record(layers - 1)) - targets;

		for (int i = layers - 1;i > 1;i--) {
			gradient_biases(i - 1) = sum(deltas, 1) / batch_size;
			gradient_weights(i - 1) = deltas * acts.at(i - 2)->activation(record(i - 1)).t() / batch_size;

			mat matrix = weights(i - 1).t() * deltas;
			mat derivative = acts.at(i - 2)->derivative(record(i - 1));
			deltas = mul_derivative_matrix(derivative, matrix);
		}
		gradient_biases(0) = sum(deltas, 1) / batch_size;
		gradient_weights(0) = deltas * record(0).t() / batch_size;

		w_grad->clear();
		b_grad->clear();
		*w_grad = gradient_weights;
		*b_grad = gradient_biases;
	}
private:
	/* Implements one training epoch which consists of:
		1. Spliting data into batches of size batch_size
		For every batch:
		2. Forward propagation of batch with records
		3. Back propagation of error and calculation of gradients
		4. Updating parameters
	*/
	void train_epoch(mat train_data, mat train_target, int batch_size, double learn_rate) {
		int n_batches = (train_data.n_cols % batch_size == 0) ? train_data.n_cols / batch_size : train_data.n_cols / batch_size + 1;
		field<mat>* data_batches = new field<mat>(n_batches);
		field<mat>* train_batches = new field<mat>(n_batches);
		Data_handler::batch_split(train_data, train_target, data_batches, train_batches, batch_size);

		field<mat>* gradient_weights = new field<mat>(layers - 1);
		field<mat>* gradient_biases = new field<mat>(layers - 1);
		for (int i = 0;i < data_batches->n_elem;i++) {
			field<mat> records = feed_forward_recorded(data_batches->at(i));
			back_propagate(records, train_batches->at(i), gradient_weights, gradient_biases);
			update_parameters(*gradient_weights, *gradient_biases, learn_rate);
			/*float* eval = evaluate(data_batches->at(i), train_batches->at(i));
			printf("Batch %d.: Loss{%.3f} Accuracy{%.3f}\n", i+1,eval[0], eval[1]);*/
		}

		data_batches->clear();
		train_batches->clear();
	}
public:
	// Performs given number of training epochs and writes out information about training.
	void fit(mat train_data, mat train_target, int batch_size, int epochs, double learn_rate) {
		for (int i = 0;i < epochs;i++) {
			printf("\nEpoch: %d. ", i + 1);
			train_epoch(train_data, train_target, batch_size, learn_rate);
			printf("done.\n");
			float* scores = evaluate(train_data, train_target);
			printf("Loss: %.3f	Accuracy: %.3f\n", scores[0], scores[1]);
		}
	}
public:
	// Evaluates given data with its targets. First number is loss and if NN is classifier, second number given is accuracy
	float* evaluate(mat data, mat target) {
		data = feed_forward(data);
		double l = this->loss->compute_loss(data, target);
		if (clf) {
			double correct = 0;
			for (int i = 0;i < data.n_cols;i++) {
				int argmax = index_max(data.col(i));
				if (target.col(i)(argmax) == 1)
					correct += 1;
			}
			double acc = correct / data.n_cols;
			float* scores = new float[2];
			scores[0] = l; scores[1] = acc;
			return scores;
		}
		else {
			float* scores = new float[1];
			scores[0] = l;
			return scores;
		}

	}

	vec predict(vec in) {
		vec prediction = this->feed_forward(in);
		if (clf) {
			vec out{ (float)prediction.index_max() };
			return out;
		}
		else
			return prediction;
	}

	void score(std::vector<float*> pred, std::vector<float*> actual) {}

	void accuracy(std::vector<float*> pred, std::vector<float*> actual) {}

	void write() {
		printf("Weights:\n");
		weights.print();
		printf("Biases:\n");
		biases.print();
	}
};