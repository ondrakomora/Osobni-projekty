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


namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
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

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//

			train_data = new mat(1, 1); train_data = new mat(1, 1);
			dev_data = new mat(1, 1); dev_target = new mat(1, 1);
			test_data = new mat(1, 1); test_target = new mat(1, 1);
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
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::ComboBox^ comboBox3;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::Label^ label13;
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
	private: System::Windows::Forms::Button^ button4;
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
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
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
			this->y_features_lb->Size = System::Drawing::Size(127, 13);
			this->y_features_lb->TabIndex = 14;
			this->y_features_lb->Text = L"Number of taget features:";
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
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->textBox11);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Controls->Add(this->textBox10);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->comboBox3);
			this->groupBox2->Controls->Add(this->comboBox2);
			this->groupBox2->Controls->Add(this->comboBox1);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->radioButton2);
			this->groupBox2->Controls->Add(this->radioButton1);
			this->groupBox2->Controls->Add(this->textBox9);
			this->groupBox2->Controls->Add(this->textBox8);
			this->groupBox2->Controls->Add(this->textBox7);
			this->groupBox2->Controls->Add(this->textBox6);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Location = System::Drawing::Point(12, 224);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(557, 151);
			this->groupBox2->TabIndex = 11;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Hyperparameters of neural network model";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(113, 122);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(161, 23);
			this->button4->TabIndex = 21;
			this->button4->Text = L"Set parameters";
			this->button4->UseVisualStyleBackColor = true;
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
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(361, 79);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(60, 20);
			this->textBox11->TabIndex = 19;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(280, 82);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(48, 13);
			this->label13->TabIndex = 18;
			this->label13->Text = L"Lambda:";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(491, 79);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(60, 20);
			this->textBox10->TabIndex = 17;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(427, 82);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(45, 13);
			this->label12->TabIndex = 16;
			this->label12->Text = L"L1 ratio:";
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"None", L"L1", L"L2", L"Elastic net" });
			this->comboBox3->Location = System::Drawing::Point(430, 57);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(121, 21);
			this->comboBox3->TabIndex = 15;
			this->comboBox3->SelectedValueChanged += gcnew System::EventHandler(this, &Form1::comboBox3_SelectedValueChanged);
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"MSE", L"Cross-entropy" });
			this->comboBox2->Location = System::Drawing::Point(430, 35);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 14;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Sigmoid", L"ReLU", L"Tanh" });
			this->comboBox1->Location = System::Drawing::Point(430, 13);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 13;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(280, 38);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(73, 13);
			this->label11->TabIndex = 12;
			this->label11->Text = L"Loss function:";
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(97, 105);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(78, 17);
			this->radioButton2->TabIndex = 11;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Regression";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(6, 105);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(86, 17);
			this->radioButton1->TabIndex = 10;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Classification";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(174, 79);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(100, 20);
			this->textBox9->TabIndex = 9;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(174, 57);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(100, 20);
			this->textBox8->TabIndex = 8;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(174, 35);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(100, 20);
			this->textBox7->TabIndex = 7;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(174, 13);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 6;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(280, 60);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(80, 13);
			this->label10->TabIndex = 5;
			this->label10->Text = L"Regularization: ";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(280, 16);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(98, 13);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Activation function:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 82);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(97, 13);
			this->label8->TabIndex = 3;
			this->label8->Text = L"Number of epochs:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 60);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(53, 13);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Bath size:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 38);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(72, 13);
			this->label6->TabIndex = 1;
			this->label6->Text = L"Learning rate:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 16);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(141, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Neural network architecture:";
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

	private: System::Void comboBox3_SelectedValueChanged(System::Object^ sender, System::EventArgs^ e) {
		if (this->comboBox3->SelectedItem == "Elastic net") {
			this->textBox10->Visible = !this->textBox10->Visible;
		}
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
			catch(...){}
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

};

	
}