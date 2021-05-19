#pragma once

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <msclr\marshal_cppstd.h>

#define ARMA_DONT_USE_STD_MUTEX
#include <armadillo>
#include <Data_handler.h>
#include <Exceptions.h>
#include <NeuralNetwork.h>


namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// </summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		arma::mat* train_data;
		arma::mat* train_target;
		arma::mat* dev_data;
		arma::mat* dev_target;
		arma::mat* test_data;
		arma::mat* test_target;

		double dev_size;
		double test_size;
		double train_size;

		int n_td_features;
		int n_tt_features;

		double learn_rate;
		int batch_size;
		int epochs;

		double reg_term;
		double l1_ratio;

		std::vector<int>* architecture;
		NeuralNetwork* nn;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//

			train_size = 1;
			dev_size = 0;
			test_size = 0;
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::TextBox^ data_path_tb;
	private: System::Windows::Forms::TextBox^ target_path_tb;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ evaluation_data_tb;
	private: System::Windows::Forms::TextBox^ train_data_tb;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::CheckBox^ dev_size_chb;
	private: System::Windows::Forms::TextBox^ dev_size_tb;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ train_files_load_but;
	private: System::Windows::Forms::Label^ target_path_lb;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ nn_architecture_lb;
	private: System::Windows::Forms::ComboBox^ reg_cb;
	private: System::Windows::Forms::ComboBox^ loss_cb;
	private: System::Windows::Forms::ComboBox^ act_cb;




	private: System::Windows::Forms::Label^ loss_lb;
	private: System::Windows::Forms::RadioButton^ regressor_rb;
	private: System::Windows::Forms::RadioButton^ classifier_rb;





	private: System::Windows::Forms::TextBox^ n_epochs_tb;

	private: System::Windows::Forms::TextBox^ batch_size_tb;

	private: System::Windows::Forms::TextBox^ learn_rate_tb;

	private: System::Windows::Forms::TextBox^ nn_architecture_tb;
	private: System::Windows::Forms::Label^ reg_lb;


	private: System::Windows::Forms::Label^ act_lb;

	private: System::Windows::Forms::Label^ n_epochs_lb;

	private: System::Windows::Forms::Label^ batch_size_lb;

	private: System::Windows::Forms::Label^ learn_rate_lb;
	private: System::Windows::Forms::TextBox^ l1_ratio_tb;
	private: System::Windows::Forms::Label^ l1_ratio_lb;



	private: System::Windows::Forms::TextBox^ reg_term_tb;

	private: System::Windows::Forms::Label^ reg_term_lb;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ x_features_lb;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ y_features_lb;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label22;

	private: System::Windows::Forms::TextBox^ x_features_tb;
	private: System::Windows::Forms::TextBox^ y_features_tb;


	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ data_path_lb;
	private: System::Windows::Forms::Button^ set_parameters_but;


	private: System::Windows::Forms::TextBox^ test_size_tb;
	private: System::Windows::Forms::CheckBox^ test_size_chb;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->target_path_tb = (gcnew System::Windows::Forms::TextBox());
			this->data_path_lb = (gcnew System::Windows::Forms::Label());
			this->target_path_lb = (gcnew System::Windows::Forms::Label());
			this->evaluation_data_tb = (gcnew System::Windows::Forms::TextBox());
			this->data_path_tb = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->dev_size_chb = (gcnew System::Windows::Forms::CheckBox());
			this->dev_size_tb = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->test_size_tb = (gcnew System::Windows::Forms::TextBox());
			this->test_size_chb = (gcnew System::Windows::Forms::CheckBox());
			this->y_features_tb = (gcnew System::Windows::Forms::TextBox());
			this->y_features_lb = (gcnew System::Windows::Forms::Label());
			this->x_features_lb = (gcnew System::Windows::Forms::Label());
			this->x_features_tb = (gcnew System::Windows::Forms::TextBox());
			this->train_files_load_but = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->set_parameters_but = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->reg_term_tb = (gcnew System::Windows::Forms::TextBox());
			this->reg_term_lb = (gcnew System::Windows::Forms::Label());
			this->l1_ratio_tb = (gcnew System::Windows::Forms::TextBox());
			this->l1_ratio_lb = (gcnew System::Windows::Forms::Label());
			this->reg_cb = (gcnew System::Windows::Forms::ComboBox());
			this->loss_cb = (gcnew System::Windows::Forms::ComboBox());
			this->act_cb = (gcnew System::Windows::Forms::ComboBox());
			this->loss_lb = (gcnew System::Windows::Forms::Label());
			this->regressor_rb = (gcnew System::Windows::Forms::RadioButton());
			this->classifier_rb = (gcnew System::Windows::Forms::RadioButton());
			this->n_epochs_tb = (gcnew System::Windows::Forms::TextBox());
			this->batch_size_tb = (gcnew System::Windows::Forms::TextBox());
			this->learn_rate_tb = (gcnew System::Windows::Forms::TextBox());
			this->nn_architecture_tb = (gcnew System::Windows::Forms::TextBox());
			this->reg_lb = (gcnew System::Windows::Forms::Label());
			this->act_lb = (gcnew System::Windows::Forms::Label());
			this->n_epochs_lb = (gcnew System::Windows::Forms::Label());
			this->batch_size_lb = (gcnew System::Windows::Forms::Label());
			this->learn_rate_lb = (gcnew System::Windows::Forms::Label());
			this->nn_architecture_lb = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// target_path_tb
			// 
			this->target_path_tb->Location = System::Drawing::Point(6, 71);
			this->target_path_tb->Name = L"target_path_tb";
			this->target_path_tb->Size = System::Drawing::Size(268, 20);
			this->target_path_tb->TabIndex = 1;
			this->target_path_tb->Text = L"C:\\\\Users\\\\ondra\\\\Desktop\\\\MFF UK\\\\Prog 3 ZP\\\\train_target.txt";
			this->target_path_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::target_path_tb_KeyPress);
			// 
			// data_path_lb
			// 
			this->data_path_lb->AutoSize = true;
			this->data_path_lb->Location = System::Drawing::Point(3, 16);
			this->data_path_lb->Name = L"data_path_lb";
			this->data_path_lb->Size = System::Drawing::Size(91, 13);
			this->data_path_lb->TabIndex = 2;
			this->data_path_lb->Text = L"Path to train data:";
			// 
			// target_path_lb
			// 
			this->target_path_lb->AutoSize = true;
			this->target_path_lb->Location = System::Drawing::Point(3, 55);
			this->target_path_lb->Name = L"target_path_lb";
			this->target_path_lb->Size = System::Drawing::Size(102, 13);
			this->target_path_lb->TabIndex = 3;
			this->target_path_lb->Text = L"Path to train targets:";
			// 
			// evaluation_data_tb
			// 
			this->evaluation_data_tb->Location = System::Drawing::Point(289, 22);
			this->evaluation_data_tb->Name = L"evaluation_data_tb";
			this->evaluation_data_tb->Size = System::Drawing::Size(268, 20);
			this->evaluation_data_tb->TabIndex = 4;
			// 
			// data_path_tb
			// 
			this->data_path_tb->Location = System::Drawing::Point(6, 32);
			this->data_path_tb->Name = L"data_path_tb";
			this->data_path_tb->Size = System::Drawing::Size(268, 20);
			this->data_path_tb->TabIndex = 5;
			this->data_path_tb->Text = L"C:\\\\Users\\\\ondra\\\\Desktop\\\\MFF UK\\\\Prog 3 ZP\\\\train_data.txt";
			this->data_path_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::data_path_tb_KeyPress);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(280, 6);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(135, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Path to data for evaluation:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(295, 37);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(120, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Where to output results:\r\n";
			// 
			// dev_size_chb
			// 
			this->dev_size_chb->AutoSize = true;
			this->dev_size_chb->Location = System::Drawing::Point(6, 100);
			this->dev_size_chb->Name = L"dev_size_chb";
			this->dev_size_chb->Size = System::Drawing::Size(170, 17);
			this->dev_size_chb->TabIndex = 8;
			this->dev_size_chb->Text = L"Separate dev set from train set\r\n";
			this->dev_size_chb->UseVisualStyleBackColor = true;
			this->dev_size_chb->CheckedChanged += gcnew System::EventHandler(this, &Form1::dev_size_chb_CheckedChanged);
			// 
			// dev_size_tb
			// 
			this->dev_size_tb->Location = System::Drawing::Point(196, 97);
			this->dev_size_tb->Name = L"dev_size_tb";
			this->dev_size_tb->Size = System::Drawing::Size(78, 20);
			this->dev_size_tb->TabIndex = 9;
			this->dev_size_tb->Text = L"0.2";
			this->dev_size_tb->Visible = false;
			this->dev_size_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::dev_size_tb_KeyPress);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->test_size_tb);
			this->groupBox1->Controls->Add(this->test_size_chb);
			this->groupBox1->Controls->Add(this->y_features_tb);
			this->groupBox1->Controls->Add(this->y_features_lb);
			this->groupBox1->Controls->Add(this->x_features_lb);
			this->groupBox1->Controls->Add(this->x_features_tb);
			this->groupBox1->Controls->Add(this->train_files_load_but);
			this->groupBox1->Controls->Add(this->data_path_lb);
			this->groupBox1->Controls->Add(this->data_path_tb);
			this->groupBox1->Controls->Add(this->dev_size_tb);
			this->groupBox1->Controls->Add(this->target_path_lb);
			this->groupBox1->Controls->Add(this->dev_size_chb);
			this->groupBox1->Controls->Add(this->target_path_tb);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(557, 177);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Input files loading";
			// 
			// test_size_tb
			// 
			this->test_size_tb->Location = System::Drawing::Point(196, 124);
			this->test_size_tb->Name = L"test_size_tb";
			this->test_size_tb->Size = System::Drawing::Size(78, 20);
			this->test_size_tb->TabIndex = 17;
			this->test_size_tb->Text = L"0.1";
			this->test_size_tb->Visible = false;
			this->test_size_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::test_size_tb_KeyPress);
			// 
			// test_size_chb
			// 
			this->test_size_chb->AutoSize = true;
			this->test_size_chb->Location = System::Drawing::Point(6, 123);
			this->test_size_chb->Name = L"test_size_chb";
			this->test_size_chb->Size = System::Drawing::Size(169, 17);
			this->test_size_chb->TabIndex = 16;
			this->test_size_chb->Text = L"Separate test set from train set";
			this->test_size_chb->UseVisualStyleBackColor = true;
			this->test_size_chb->CheckedChanged += gcnew System::EventHandler(this, &Form1::test_size_chb_CheckedChanged_1);
			// 
			// y_features_tb
			// 
			this->y_features_tb->Location = System::Drawing::Point(473, 67);
			this->y_features_tb->Name = L"y_features_tb";
			this->y_features_tb->Size = System::Drawing::Size(78, 20);
			this->y_features_tb->TabIndex = 15;
			this->y_features_tb->Text = L"1";
			this->y_features_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::y_features_tb_KeyPress);
			// 
			// y_features_lb
			// 
			this->y_features_lb->AutoSize = true;
			this->y_features_lb->Location = System::Drawing::Point(280, 74);
			this->y_features_lb->Name = L"y_features_lb";
			this->y_features_lb->Size = System::Drawing::Size(130, 13);
			this->y_features_lb->TabIndex = 14;
			this->y_features_lb->Text = L"Number of target features:";
			// 
			// x_features_lb
			// 
			this->x_features_lb->AutoSize = true;
			this->x_features_lb->Location = System::Drawing::Point(280, 35);
			this->x_features_lb->Name = L"x_features_lb";
			this->x_features_lb->Size = System::Drawing::Size(123, 13);
			this->x_features_lb->TabIndex = 13;
			this->x_features_lb->Text = L"Number of train features:\r\n";
			// 
			// x_features_tb
			// 
			this->x_features_tb->Location = System::Drawing::Point(473, 32);
			this->x_features_tb->Name = L"x_features_tb";
			this->x_features_tb->Size = System::Drawing::Size(78, 20);
			this->x_features_tb->TabIndex = 12;
			this->x_features_tb->Text = L"784";
			this->x_features_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::x_features_tb_KeyPress);
			// 
			// train_files_load_but
			// 
			this->train_files_load_but->Location = System::Drawing::Point(196, 148);
			this->train_files_load_but->Name = L"train_files_load_but";
			this->train_files_load_but->Size = System::Drawing::Size(161, 23);
			this->train_files_load_but->TabIndex = 10;
			this->train_files_load_but->Text = L"Load train files";
			this->train_files_load_but->UseVisualStyleBackColor = true;
			this->train_files_load_but->Click += gcnew System::EventHandler(this, &Form1::train_files_load_but_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(344, 85);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(161, 23);
			this->button3->TabIndex = 11;
			this->button3->Text = L"Load evaluation files";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->set_parameters_but);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->reg_term_tb);
			this->groupBox2->Controls->Add(this->reg_term_lb);
			this->groupBox2->Controls->Add(this->l1_ratio_tb);
			this->groupBox2->Controls->Add(this->l1_ratio_lb);
			this->groupBox2->Controls->Add(this->reg_cb);
			this->groupBox2->Controls->Add(this->loss_cb);
			this->groupBox2->Controls->Add(this->act_cb);
			this->groupBox2->Controls->Add(this->loss_lb);
			this->groupBox2->Controls->Add(this->regressor_rb);
			this->groupBox2->Controls->Add(this->classifier_rb);
			this->groupBox2->Controls->Add(this->n_epochs_tb);
			this->groupBox2->Controls->Add(this->batch_size_tb);
			this->groupBox2->Controls->Add(this->learn_rate_tb);
			this->groupBox2->Controls->Add(this->nn_architecture_tb);
			this->groupBox2->Controls->Add(this->reg_lb);
			this->groupBox2->Controls->Add(this->act_lb);
			this->groupBox2->Controls->Add(this->n_epochs_lb);
			this->groupBox2->Controls->Add(this->batch_size_lb);
			this->groupBox2->Controls->Add(this->learn_rate_lb);
			this->groupBox2->Controls->Add(this->nn_architecture_lb);
			this->groupBox2->Location = System::Drawing::Point(12, 224);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(557, 151);
			this->groupBox2->TabIndex = 11;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Hyperparameters of neural network model";
			// 
			// set_parameters_but
			// 
			this->set_parameters_but->Location = System::Drawing::Point(112, 122);
			this->set_parameters_but->Name = L"set_parameters_but";
			this->set_parameters_but->Size = System::Drawing::Size(161, 23);
			this->set_parameters_but->TabIndex = 21;
			this->set_parameters_but->Text = L"Set parameters";
			this->set_parameters_but->UseVisualStyleBackColor = true;
			this->set_parameters_but->Click += gcnew System::EventHandler(this, &Form1::set_parameters_but_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(283, 122);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(161, 23);
			this->button2->TabIndex = 20;
			this->button2->Text = L"Fit";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// reg_term_tb
			// 
			this->reg_term_tb->Location = System::Drawing::Point(361, 79);
			this->reg_term_tb->Name = L"reg_term_tb";
			this->reg_term_tb->Size = System::Drawing::Size(60, 20);
			this->reg_term_tb->TabIndex = 19;
			this->reg_term_tb->Visible = false;
			this->reg_term_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::reg_term_tb_KeyPress);
			// 
			// reg_term_lb
			// 
			this->reg_term_lb->AutoSize = true;
			this->reg_term_lb->Location = System::Drawing::Point(280, 82);
			this->reg_term_lb->Name = L"reg_term_lb";
			this->reg_term_lb->Size = System::Drawing::Size(48, 13);
			this->reg_term_lb->TabIndex = 18;
			this->reg_term_lb->Text = L"Lambda:";
			this->reg_term_lb->Visible = false;
			// 
			// l1_ratio_tb
			// 
			this->l1_ratio_tb->Location = System::Drawing::Point(491, 79);
			this->l1_ratio_tb->Name = L"l1_ratio_tb";
			this->l1_ratio_tb->Size = System::Drawing::Size(60, 20);
			this->l1_ratio_tb->TabIndex = 17;
			this->l1_ratio_tb->Visible = false;
			this->l1_ratio_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::l1_ratio_tb_KeyPress);
			// 
			// l1_ratio_lb
			// 
			this->l1_ratio_lb->AutoSize = true;
			this->l1_ratio_lb->Location = System::Drawing::Point(427, 82);
			this->l1_ratio_lb->Name = L"l1_ratio_lb";
			this->l1_ratio_lb->Size = System::Drawing::Size(45, 13);
			this->l1_ratio_lb->TabIndex = 16;
			this->l1_ratio_lb->Text = L"L1 ratio:";
			this->l1_ratio_lb->Visible = false;
			// 
			// reg_cb
			// 
			this->reg_cb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->reg_cb->FormattingEnabled = true;
			this->reg_cb->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"None", L"L1", L"L2", L"Elastic net" });
			this->reg_cb->Location = System::Drawing::Point(430, 57);
			this->reg_cb->Name = L"reg_cb";
			this->reg_cb->Size = System::Drawing::Size(121, 21);
			this->reg_cb->TabIndex = 15;
			this->reg_cb->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::reg_cb_SelectedIndexChanged);
			// 
			// loss_cb
			// 
			this->loss_cb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->loss_cb->FormattingEnabled = true;
			this->loss_cb->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"MSE", L"Cross-entropy" });
			this->loss_cb->Location = System::Drawing::Point(430, 35);
			this->loss_cb->Name = L"loss_cb";
			this->loss_cb->Size = System::Drawing::Size(121, 21);
			this->loss_cb->TabIndex = 14;
			// 
			// act_cb
			// 
			this->act_cb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->act_cb->FormattingEnabled = true;
			this->act_cb->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"Sigmoid", L"ReLU", L"Tanh", L"Softmax", L"Linear" });
			this->act_cb->Location = System::Drawing::Point(430, 13);
			this->act_cb->Name = L"act_cb";
			this->act_cb->Size = System::Drawing::Size(121, 21);
			this->act_cb->TabIndex = 13;
			// 
			// loss_lb
			// 
			this->loss_lb->AutoSize = true;
			this->loss_lb->Location = System::Drawing::Point(280, 38);
			this->loss_lb->Name = L"loss_lb";
			this->loss_lb->Size = System::Drawing::Size(73, 13);
			this->loss_lb->TabIndex = 12;
			this->loss_lb->Text = L"Loss function:";
			// 
			// regressor_rb
			// 
			this->regressor_rb->AutoSize = true;
			this->regressor_rb->Location = System::Drawing::Point(97, 105);
			this->regressor_rb->Name = L"regressor_rb";
			this->regressor_rb->Size = System::Drawing::Size(78, 17);
			this->regressor_rb->TabIndex = 11;
			this->regressor_rb->TabStop = true;
			this->regressor_rb->Text = L"Regression";
			this->regressor_rb->UseVisualStyleBackColor = true;
			this->regressor_rb->CheckedChanged += gcnew System::EventHandler(this, &Form1::regressor_rb_CheckedChanged);
			// 
			// classifier_rb
			// 
			this->classifier_rb->AutoSize = true;
			this->classifier_rb->Location = System::Drawing::Point(6, 105);
			this->classifier_rb->Name = L"classifier_rb";
			this->classifier_rb->Size = System::Drawing::Size(86, 17);
			this->classifier_rb->TabIndex = 10;
			this->classifier_rb->TabStop = true;
			this->classifier_rb->Text = L"Classification";
			this->classifier_rb->UseVisualStyleBackColor = true;
			this->classifier_rb->CheckedChanged += gcnew System::EventHandler(this, &Form1::classifier_rb_CheckedChanged);
			// 
			// n_epochs_tb
			// 
			this->n_epochs_tb->Location = System::Drawing::Point(174, 79);
			this->n_epochs_tb->Name = L"n_epochs_tb";
			this->n_epochs_tb->Size = System::Drawing::Size(100, 20);
			this->n_epochs_tb->TabIndex = 9;
			this->n_epochs_tb->Text = L"10";
			this->n_epochs_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::n_epochs_tb_KeyPress);
			// 
			// batch_size_tb
			// 
			this->batch_size_tb->Location = System::Drawing::Point(174, 57);
			this->batch_size_tb->Name = L"batch_size_tb";
			this->batch_size_tb->Size = System::Drawing::Size(100, 20);
			this->batch_size_tb->TabIndex = 8;
			this->batch_size_tb->Text = L"64";
			this->batch_size_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::batch_size_tb_KeyPress);
			// 
			// learn_rate_tb
			// 
			this->learn_rate_tb->Location = System::Drawing::Point(174, 35);
			this->learn_rate_tb->Name = L"learn_rate_tb";
			this->learn_rate_tb->Size = System::Drawing::Size(100, 20);
			this->learn_rate_tb->TabIndex = 7;
			this->learn_rate_tb->Text = L"0,01";
			this->learn_rate_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::learn_rate_tb_KeyPress);
			// 
			// nn_architecture_tb
			// 
			this->nn_architecture_tb->Location = System::Drawing::Point(174, 13);
			this->nn_architecture_tb->Name = L"nn_architecture_tb";
			this->nn_architecture_tb->Size = System::Drawing::Size(100, 20);
			this->nn_architecture_tb->TabIndex = 6;
			this->nn_architecture_tb->Text = L"784-10-10";
			this->nn_architecture_tb->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::nn_architecture_tb_KeyPress);
			// 
			// reg_lb
			// 
			this->reg_lb->AutoSize = true;
			this->reg_lb->Location = System::Drawing::Point(280, 60);
			this->reg_lb->Name = L"reg_lb";
			this->reg_lb->Size = System::Drawing::Size(80, 13);
			this->reg_lb->TabIndex = 5;
			this->reg_lb->Text = L"Regularization: ";
			// 
			// act_lb
			// 
			this->act_lb->AutoSize = true;
			this->act_lb->Location = System::Drawing::Point(280, 16);
			this->act_lb->Name = L"act_lb";
			this->act_lb->Size = System::Drawing::Size(98, 13);
			this->act_lb->TabIndex = 4;
			this->act_lb->Text = L"Activation function:";
			// 
			// n_epochs_lb
			// 
			this->n_epochs_lb->AutoSize = true;
			this->n_epochs_lb->Location = System::Drawing::Point(6, 82);
			this->n_epochs_lb->Name = L"n_epochs_lb";
			this->n_epochs_lb->Size = System::Drawing::Size(97, 13);
			this->n_epochs_lb->TabIndex = 3;
			this->n_epochs_lb->Text = L"Number of epochs:";
			// 
			// batch_size_lb
			// 
			this->batch_size_lb->AutoSize = true;
			this->batch_size_lb->Location = System::Drawing::Point(6, 60);
			this->batch_size_lb->Name = L"batch_size_lb";
			this->batch_size_lb->Size = System::Drawing::Size(53, 13);
			this->batch_size_lb->TabIndex = 2;
			this->batch_size_lb->Text = L"Bath size:";
			// 
			// learn_rate_lb
			// 
			this->learn_rate_lb->AutoSize = true;
			this->learn_rate_lb->Location = System::Drawing::Point(6, 38);
			this->learn_rate_lb->Name = L"learn_rate_lb";
			this->learn_rate_lb->Size = System::Drawing::Size(72, 13);
			this->learn_rate_lb->TabIndex = 1;
			this->learn_rate_lb->Text = L"Learning rate:";
			// 
			// nn_architecture_lb
			// 
			this->nn_architecture_lb->AutoSize = true;
			this->nn_architecture_lb->Location = System::Drawing::Point(6, 16);
			this->nn_architecture_lb->Name = L"nn_architecture_lb";
			this->nn_architecture_lb->Size = System::Drawing::Size(141, 13);
			this->nn_architecture_lb->TabIndex = 0;
			this->nn_architecture_lb->Text = L"Neural network architecture:";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(18, 511);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(557, 23);
			this->progressBar1->TabIndex = 12;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label23);
			this->groupBox3->Controls->Add(this->label22);
			this->groupBox3->Controls->Add(this->button3);
			this->groupBox3->Controls->Add(this->label21);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->evaluation_data_tb);
			this->groupBox3->Controls->Add(this->label20);
			this->groupBox3->Controls->Add(this->label19);
			this->groupBox3->Controls->Add(this->label18);
			this->groupBox3->Controls->Add(this->label17);
			this->groupBox3->Controls->Add(this->label16);
			this->groupBox3->Controls->Add(this->label15);
			this->groupBox3->Controls->Add(this->label14);
			this->groupBox3->Location = System::Drawing::Point(12, 381);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(557, 124);
			this->groupBox3->TabIndex = 13;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Results";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(134, 69);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(41, 13);
			this->label23->TabIndex = 9;
			this->label23->Text = L"label23";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(6, 43);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(110, 13);
			this->label22->TabIndex = 8;
			this->label22->Text = L"Accuracy on train set:";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(134, 56);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(41, 13);
			this->label21->TabIndex = 7;
			this->label21->Text = L"label21";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(6, 56);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(87, 13);
			this->label20->TabIndex = 6;
			this->label20->Text = L"Loss on train set:";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(134, 42);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(41, 13);
			this->label19->TabIndex = 5;
			this->label19->Text = L"label19";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(6, 69);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(107, 13);
			this->label18->TabIndex = 4;
			this->label18->Text = L"Accuracy on test set:";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(134, 29);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(41, 13);
			this->label17->TabIndex = 3;
			this->label17->Text = L"label17";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(6, 29);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(87, 13);
			this->label16->TabIndex = 2;
			this->label16->Text = L"Loss on train set:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(134, 16);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(41, 13);
			this->label15->TabIndex = 1;
			this->label15->Text = L"label15";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(6, 16);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(43, 13);
			this->label14->TabIndex = 0;
			this->label14->Text = L"Fit time:";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(581, 546);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"Form1";
			this->Text = L"Neurotron-3000";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: bool check_split_sizes() {
		return (dev_size + test_size < 1) ? true : false;
	}

	private: System::Void data_path_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			String^ sys_td_path = this->data_path_tb->Text;
			std::string td_path = msclr::interop::marshal_as<std::string>(sys_td_path);

			x_features_tb_KeyPress(sender, e);

			try {
				std::fstream data_file(td_path, ios::in);
				if (!data_file.good()) { throw gcnew File_error(sys_td_path, "not found"); }
				data_file.close();

				if (n_td_features <= 0) { throw gcnew Input_error(n_td_features, "int>0"); }

				train_data = &Data_handler::load_data(td_path, n_td_features);
			}
			catch (Error^ e) { MessageBox::Show(e->mess); }
			catch (...) {}
		}
	}

	private: System::Void target_path_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			String^ sys_tt_path = this->target_path_tb->Text;
			std::string tt_path = msclr::interop::marshal_as<std::string>(sys_tt_path);

			y_features_tb_KeyPress(sender, e);

			try {
				std::fstream target_file(tt_path, ios::in);
				if (!target_file.good()) { throw gcnew File_error(sys_tt_path, "not found"); }
				target_file.close();

				if (n_tt_features <= 0) { throw gcnew Input_error(n_tt_features, "int>0"); }

				train_target = &Data_handler::load_data(tt_path, n_tt_features);
			}
			catch (Error^ e) { MessageBox::Show(e->mess); }
			catch (...) {}
		}
	}

	private: System::Void dev_size_chb_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		this->dev_size_tb->Visible = !this->dev_size_tb->Visible;
	}

	private: System::Void test_size_chb_CheckedChanged_1(System::Object^ sender, System::EventArgs^ e) {
		this->test_size_tb->Visible = !this->test_size_tb->Visible;
	}

	private: System::Void dev_size_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			if (dev_size_chb->Checked) {
				try {
					dev_size = double::Parse(this->dev_size_tb->Text);
					if (dev_size <= 0 || dev_size >= 1) {
						throw gcnew Input_error(dev_size, "0<double<1");
					}
					if (check_split_sizes()) { train_size = 1 - dev_size - test_size; }
					else { throw gcnew Input_error(dev_size, "0<double<train_size"); }
				}
				catch (Error^ e) { MessageBox::Show(e->mess); }
				catch (...) { MessageBox::Show("Loading dev size failed!"); }
			}
		}
	}

	private: System::Void test_size_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			if (test_size_chb->Checked) {
				try {
					test_size = double::Parse(this->test_size_tb->Text);
					if (test_size <= 0 || test_size >= 1) {
						throw gcnew Input_error(test_size, "0<double<1");
					}
					if (check_split_sizes()) { train_size = 1 - dev_size - test_size; }
					else { throw gcnew Input_error(test_size, "0<double<train_size"); }
				}
				catch (Error^ e) { MessageBox::Show(e->mess); }
				catch (...) { MessageBox::Show("Loading dev size failed!"); }
			}
		}
	}

	private: System::Void x_features_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			try { n_td_features = int::Parse(this->x_features_tb->Text); }
			catch (...) { MessageBox::Show("Loading number of training features failed!"); }
		}
	}

	private: System::Void y_features_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			try { n_tt_features = int::Parse(this->y_features_tb->Text); }
			catch (...) { MessageBox::Show("Loading number of target features failed!"); }
		}
	}

	// FIX - problém s pointery
	private: System::Void train_files_load_but_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::KeyPressEventArgs^ f = gcnew System::Windows::Forms::KeyPressEventArgs((char)Keys::Enter);
		data_path_tb_KeyPress(sender, f);
		target_path_tb_KeyPress(sender, f);

		if (dev_size_chb->Checked) {
			dev_size_tb_KeyPress(sender, f);


			if (check_split_sizes()) {
				Data_handler::data_split(*train_data, *train_target, train_data, train_target, dev_data, dev_target, dev_size);
			}
		}

		if (test_size_chb->Checked) {
			test_size_tb_KeyPress(sender, f);

			if (check_split_sizes()) {
				Data_handler::data_split(*train_data, *train_target, train_data, train_target, test_data, test_target, test_size);
			}
		}

	}

	private: System::Void set_parameters_but_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::KeyPressEventArgs^ f = gcnew System::Windows::Forms::KeyPressEventArgs((char)Keys::Enter);
		nn_architecture_tb_KeyPress(sender, f);
		learn_rate_tb_KeyPress(sender, f);
		batch_size_tb_KeyPress(sender, f);
		n_epochs_tb_KeyPress(sender, f);

		// TODO - přidat aktivace, loss, regularizace
	}

	private: System::Void nn_architecture_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			String^ sys_nn_architecture = this->nn_architecture_tb->Text;
			std::string nn_architecture = msclr::interop::marshal_as<std::string>(sys_nn_architecture);

			std::vector<int> architecture;
			int n = 0;
			for (int i = 0;i < nn_architecture.length();i++) {
				char c = nn_architecture.at(i);
				if (48 <= c && c < 58) {
					n = 10 * n + c - 48;
				}
				else {
					if (n!=0) architecture.push_back(n);
					n = 0;
				}
			}

			bool ok = true;
			int e = 0;
			for (int i = 0;i < architecture.size();i++) {
				if (architecture.at(i) <= 0) {
					ok = false; e = architecture.at(i);
					break;
				}
			}

			if (ok) { 
				this->architecture = &architecture;
			}
			else {
				Input_error^ ie = gcnew Input_error(e, "int>0");
				MessageBox::Show(ie->mess);
			}
		}
	}

	private: System::Void learn_rate_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			try {
				this->learn_rate = double::Parse(this->learn_rate_tb->Text);
				if (learn_rate <= 0) {
					throw gcnew Input_error(learn_rate, "double>0");
				}
			}
			catch (Error^ e) { MessageBox::Show(e->mess); }
			catch (...) { MessageBox::Show("Loading learning rate failed!"); }
		}
	}

	private: System::Void batch_size_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			try {
				this->batch_size = int::Parse(this->batch_size_tb->Text);
				if (batch_size <= 0) { throw gcnew Input_error(batch_size, "int>0"); }
			}
			catch (Error^ e) { MessageBox::Show(e->mess); }
			catch (...) {
				MessageBox::Show("Loading batch_size failed!");
			}
		}
	}

	private: System::Void n_epochs_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			try {
				this->epochs = int::Parse(this->n_epochs_tb->Text);
				if (epochs <= 0) { throw gcnew Input_error(epochs, "int>0"); }
			}
			catch (Error^ e) { MessageBox::Show(e->mess); }
			catch (...) {
				MessageBox::Show("Loading n_epochs failed!");
			}
		}
	}

	// TODO - upravit nabídku loss
	private: System::Void classifier_rb_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (classifier_rb->Checked) {
			this->loss_cb->ResetText();
			this->loss_cb->Items->Clear();
			this->loss_cb->Items->AddRange(gcnew cli::array< System::Object^>(1) { L"Cross-entropy"});
		}
	}

	private: System::Void regressor_rb_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (regressor_rb->Checked) {
			this->loss_cb->ResetText();
			this->loss_cb->Items->Clear();
			this->loss_cb->Items->AddRange(gcnew cli::array<System::Object^>(1) { L"MSE" });
		}
	}

	private: System::Void reg_cb_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		this->reg_term_tb->ResetText();
		this->reg_term_tb->Visible = false;
		this->reg_term_lb->Visible = false;
		this->l1_ratio_tb->ResetText();
		this->l1_ratio_tb->Visible = false;
		this->l1_ratio_lb->Visible = false;
		String^ reg = this->reg_cb->Text;

		if (reg == "L1") {
			this->reg_term_lb->Visible = true;
			this->reg_term_tb->Visible = true;
		}
		if (reg == "L2") {
			this->reg_term_lb->Visible = true;
			this->reg_term_tb->Visible = true;
		}
		if (reg == "Elastic net") {
			this->reg_term_lb->Visible = true;
			this->reg_term_tb->Visible = true;
			this->l1_ratio_lb->Visible = true;
			this->l1_ratio_tb->Visible = true;
		}
	}

	private: System::Void reg_term_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			try {
				this->reg_term = double::Parse(this->reg_term_tb->Text);
				if (reg_term < 0) { throw gcnew Input_error(reg_term, "double>=0"); }
			}
			catch (Error^ e) { MessageBox::Show(e->mess); }
			catch (...) { MessageBox::Show("Loading reg_term failed!"); }
		}
	}

	private: System::Void l1_ratio_tb_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Enter) {
			try {
				this->l1_ratio = double::Parse(this->l1_ratio_tb->Text);
				if (l1_ratio < 0 || l1_ratio>1) { throw gcnew Input_error(l1_ratio, "0<=double<=1"); }
			}
			catch (Error^ e) { MessageBox::Show(e->mess); }
			catch (...) { MessageBox::Show("Loading l1_ratio failed!"); }
		}
	}
};
}

	
