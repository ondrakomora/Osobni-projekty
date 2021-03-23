#pragma once
#include <armadillo>
#include <fstream>

using namespace arma;

namespace Data_handler {

	field<vec> convert_vector_to_vec(std::vector<vec> in) {
		field<vec> out(in.size());
		for (int i = 0;i < in.size();i++) { out(i) = vec(in.at(i)); }
		return out;
	}

	field<vec> load_data(std::string path, int n_features) {
		std::fstream file(path, std::ios::in);
		std::vector<vec> v;
		while (!file.eof()) {
			vec a(n_features);
			for (int i = 0;i < n_features;i++) {
				if (!file.eof())
					file >> a(i);
				else {
					file.close();
					return convert_vector_to_vec(v);
				}
			}
			v.push_back(a);
		}
		file.close();
		return convert_vector_to_vec(v);
	}

	field<vec> encode_one_hot(field<vec> target, int classes) {
		field<vec> out(target.n_elem);
		for (int i = 0;i < target.n_elem;i++) {
			out(i) = vec(classes, fill::zeros);
			out(i)(target(i)(0)) = 1;
		}
		return out;
	}
};