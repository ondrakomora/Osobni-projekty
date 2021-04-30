#pragma once
#include <armadillo>
#include <fstream>

using namespace arma;

namespace Data_handler {

	// Converts given std::vector of arma::vec of inputs into arma::mat. 
	// Vectors are added into columns of matrix
	mat convert_field_to_mat(std::vector<vec> in, int n_features) {
		mat out(n_features, in.size());
		for (int i = 0;i < in.size();i++) { out.col(i) = vec(in.at(i)); }
		return out;
	}

	// Loads numbers from txt file with given path, adds them into a vector of length n_features
	// and then places that vector into column of output matrix.
	mat load_data(std::string path, int n_features) {
		std::fstream file(path, std::ios::in);
		std::vector<vec> v;
		int p = 1;
		for(int i =0;i<300;i++) {
			printf("Loading %d. vector\n", p++);
			vec a(n_features);
			for (int i = 0;i < n_features;i++) {
				if (!file.eof())
					file >> a(i);
				else {
					file.close();
					return convert_field_to_mat(v, n_features);
				}
			}
			v.push_back(a);
		}
		printf("Done loading\n");
		file.close();
		return convert_field_to_mat(v, n_features);
	}

	// Encodes one-number targets into one-hot vectors.
	mat encode_one_hot(mat target, int classes) {
		mat out(classes, target.n_cols);
		for (int i = 0;i < target.n_cols;i++) {
			out.col(i) = vec(classes, fill::zeros);
			out(target(0, i), i) = 1;
		}
		return out;
	}

	// Shuffles given dataset 
	void shuffle(mat& data, mat& target) {
		uvec rand_perm = randperm(data.n_cols);
		mat out_data = mat(data); mat out_target = mat(target);
		for (int i = 0; i < data.n_cols;i++) {
			out_data.col(i) = data.col(rand_perm(i));
			out_target.col(i) = target.col(rand_perm(i));
		}

		data = out_data; target = out_target;
	}

	// Splits data and its target into batches of size batch_size and stores them into given pointers. 
	// If size of data is not divisble by batch_size, the remainder is added to output nevertheless.
	// Data and targets are shuffled at the begining.
	void batch_split(mat data, mat target, field<mat>* data_batch_pointer, field<mat>* target_batch_pointer, int batch_size) {
		int size = data.n_cols;
		int r = size % batch_size;
		int m = size / batch_size;
		int n_batches = (r == 0) ? m : m + 1;
		field<mat> data_batches(n_batches);
		field<mat> target_batches(n_batches);

		shuffle(data, target);
		for (int i = 0;i < m;i++) {
			data_batches(i) = data.submat(0, i * batch_size, data.n_rows - 1, (i + 1) * batch_size - 1);
			target_batches(i) = target.submat(0, i * batch_size, data.n_rows - 1, (i + 1) * batch_size - 1);
		}

		if (r != 0) {
			data_batches(n_batches - 1) = data.submat(0, size - r, data.n_rows - 1, size - 1);
			target_batches(n_batches - 1) = target.submat(0, size - r, data.n_rows - 1, size - 1);
		}

		data_batch_pointer->clear();
		target_batch_pointer->clear();

		*data_batch_pointer = data_batches;
		*target_batch_pointer = target_batches;
	}

	// Splits dataset into two datasets with given split_ratio
	void data_split(mat data, mat target, mat* data_main, mat* target_main, mat* data_side, mat* target_side, double split_ratio) {
		int split = round((1 - split_ratio) * data.n_cols);
		shuffle(data, target);

		data_main->clear(); target_main->clear();
		data_side->clear(); target_side->clear();

		*data_main = data.submat(0, 0, data.n_rows - 1, split - 1);
		*target_main = target.submat(0, 0, target.n_rows - 1, split - 1);
		*data_side = data.submat(0, split, data.n_rows - 1, data.n_cols - 1);
		*target_side = data.submat(0, split, target.n_rows - 1, target.n_cols - 1);
	}

	/*void store_results(std::string path, std::string file_name, field<vec> predictions) {
		std::fstream file(path)
		predictions.for_each([](vec& v) {
			v.for_each([](vec::elem_type& x) {

			});
		});
	}*/
};
