#include <stdio.h>
#include <stdlib.h>


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <NeuralNetwork.h>
#include <Data_handler.h>

using namespace arma;

int main() {
	std::string st1 = "C:\\Users\\ondra\\Desktop\\MFF UK\\Prog 3 ZP\\train_data.txt";
	std::string st2 = "C:\\Users\\ondra\\Desktop\\MFF UK\\Prog 3 ZP\\train_target.txt";
	field<vec> data = Data_handler::load_data(st1, 784);
	field<vec> target = Data_handler::load_data(st2, 1);
	target = Data_handler::encode_one_hot(target, 10);

	Col<int> arch{ 784,5,5,10 };
	Activation* act = new SoftMax();
	Loss* cr_en = new Cross_entropy();
	Regularizer* reg = new Elastic_net(0.1,0.5);
	NeuralNetwork* nn = new NeuralNetwork(arch,act,cr_en,reg,false);

	field<vec> f(3);
	vec f1{ 0,0,0,0,0,0 };
	vec f2{ 1,1,1,1,1,1 };
	vec f3{ 0.5,1.5,2,2,-1,-2 };
	f(0) = f1; f(1) = f2; f(2) = f3;


	field<vec> t(3);
	vec t1{ -0.5,1,3,-7,8.52,0 };
	vec t2{ 1,2,-1,1,-1,5 };
	vec t3{ 0.5,1.5,2,2,-1,-2 };
	t(0) = t1; t(1) = t2; t(2) = t3;

	field<mat> g(2);
	mat g1(3, 3, fill::eye);
	mat g2(4, 7, fill::ones);
	g(0) = g1; g(1) = -2*g2;


	nn->fit(data, target, 1, 2, 0.1);
	
	/*Regularizer* reg = new Elastic_net(0.1,0.8);
	f = reg->penalty(f);
	f.print();
	g = reg->penalty(g);
	g.print();*/
	
	/*t = nn->back_propagate(nn->feed_forward_recorded(t1), t2);
	nn->train_epoch(f, t, 1, 0.1);
	nn->write();*/
}