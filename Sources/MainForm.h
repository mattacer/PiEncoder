#pragma once
#include <msclr\marshal_cppstd.h>
#include "Encoder.h"

//The resource logical name of MainForm.resx has to be set to "$(RootNamespace).%(Filename).resources" otherwise a missing resource exception is thrown
namespace PiEncoder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		MainForm(std::string input, std::string output){
			InitializeComponent();
			inputTextBox->Text = msclr::interop::marshal_as<String^>(input);
			outputTextBox->Text = msclr::interop::marshal_as<String^>(output);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  piPictureBox;
	protected:

	private: System::Windows::Forms::RadioButton^  encodeRadioButton;
	private: System::Windows::Forms::RadioButton^  decodeRadioButton;
	private: System::Windows::Forms::Button^  inputBrowseButton;
	private: System::Windows::Forms::TextBox^  inputTextBox;
	private: System::Windows::Forms::TextBox^  outputTextBox;



	private: System::Windows::Forms::Button^  outputBrowseButton;



	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  startOperation;
	private: System::Windows::Forms::SaveFileDialog^  inputBrowseFileDialog;
	private: System::Windows::Forms::SaveFileDialog^  outputBrowseFileDialog;








	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->piPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->encodeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->decodeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->inputBrowseButton = (gcnew System::Windows::Forms::Button());
			this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->outputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->outputBrowseButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->startOperation = (gcnew System::Windows::Forms::Button());
			this->inputBrowseFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->outputBrowseFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->piPictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// piPictureBox
			// 
			this->piPictureBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"piPictureBox.Image")));
			this->piPictureBox->Location = System::Drawing::Point(214, 12);
			this->piPictureBox->Name = L"piPictureBox";
			this->piPictureBox->Size = System::Drawing::Size(210, 140);
			this->piPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->piPictureBox->TabIndex = 0;
			this->piPictureBox->TabStop = false;
			// 
			// encodeRadioButton
			// 
			this->encodeRadioButton->AutoSize = true;
			this->encodeRadioButton->Checked = true;
			this->encodeRadioButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->encodeRadioButton->Location = System::Drawing::Point(132, 160);
			this->encodeRadioButton->Name = L"encodeRadioButton";
			this->encodeRadioButton->Size = System::Drawing::Size(142, 40);
			this->encodeRadioButton->TabIndex = 1;
			this->encodeRadioButton->TabStop = true;
			this->encodeRadioButton->Text = L"Encode";
			this->encodeRadioButton->UseVisualStyleBackColor = true;
			this->encodeRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::encodeRadioButton_CheckedChanged);
			// 
			// decodeRadioButton
			// 
			this->decodeRadioButton->AutoSize = true;
			this->decodeRadioButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->decodeRadioButton->Location = System::Drawing::Point(132, 206);
			this->decodeRadioButton->Name = L"decodeRadioButton";
			this->decodeRadioButton->Size = System::Drawing::Size(142, 40);
			this->decodeRadioButton->TabIndex = 2;
			this->decodeRadioButton->Text = L"Decode";
			this->decodeRadioButton->UseVisualStyleBackColor = true;
			this->decodeRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::decodeRadioButton_CheckedChanged);
			// 
			// inputBrowseButton
			// 
			this->inputBrowseButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->inputBrowseButton->Location = System::Drawing::Point(466, 268);
			this->inputBrowseButton->Name = L"inputBrowseButton";
			this->inputBrowseButton->Size = System::Drawing::Size(124, 41);
			this->inputBrowseButton->TabIndex = 3;
			this->inputBrowseButton->Text = L"Browse";
			this->inputBrowseButton->UseVisualStyleBackColor = true;
			this->inputBrowseButton->Click += gcnew System::EventHandler(this, &MainForm::inputBrowseButton_Click);
			// 
			// inputTextBox
			// 
			this->inputTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->inputTextBox->Location = System::Drawing::Point(126, 268);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(330, 41);
			this->inputTextBox->TabIndex = 4;
			// 
			// outputTextBox
			// 
			this->outputTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outputTextBox->Location = System::Drawing::Point(126, 325);
			this->outputTextBox->Name = L"outputTextBox";
			this->outputTextBox->Size = System::Drawing::Size(330, 41);
			this->outputTextBox->TabIndex = 6;
			// 
			// outputBrowseButton
			// 
			this->outputBrowseButton->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->outputBrowseButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->outputBrowseButton->Location = System::Drawing::Point(466, 325);
			this->outputBrowseButton->Name = L"outputBrowseButton";
			this->outputBrowseButton->Size = System::Drawing::Size(124, 41);
			this->outputBrowseButton->TabIndex = 5;
			this->outputBrowseButton->Text = L"Browse";
			this->outputBrowseButton->UseVisualStyleBackColor = true;
			this->outputBrowseButton->Click += gcnew System::EventHandler(this, &MainForm::outputBrowseButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 271);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 36);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Input :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(0, 327);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(120, 36);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Output :";
			// 
			// startOperation
			// 
			this->startOperation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->startOperation->Location = System::Drawing::Point(210, 372);
			this->startOperation->Name = L"startOperation";
			this->startOperation->Size = System::Drawing::Size(200, 47);
			this->startOperation->TabIndex = 9;
			this->startOperation->Text = L"Encode";
			this->startOperation->UseVisualStyleBackColor = true;
			this->startOperation->Click += gcnew System::EventHandler(this, &MainForm::startOperation_Click);
			// 
			// inputBrowseFileDialog
			// 
			this->inputBrowseFileDialog->InitialDirectory = L"%cd%\\";
			this->inputBrowseFileDialog->OverwritePrompt = false;
			// 
			// outputBrowseFileDialog
			// 
			this->outputBrowseFileDialog->InitialDirectory = L"%cd%\\";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(618, 424);
			this->Controls->Add(this->startOperation);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->outputTextBox);
			this->Controls->Add(this->outputBrowseButton);
			this->Controls->Add(this->inputTextBox);
			this->Controls->Add(this->inputBrowseButton);
			this->Controls->Add(this->decodeRadioButton);
			this->Controls->Add(this->encodeRadioButton);
			this->Controls->Add(this->piPictureBox);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"PiEncoder";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->piPictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void encodeRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		this->startOperation->Text = L"Encode";
	}
	private: System::Void decodeRadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		this->startOperation->Text = L"Decode";
	}
	private: System::Void inputBrowseButton_Click(System::Object^  sender, System::EventArgs^  e) {
		inputBrowseFileDialog->ShowDialog();
		if (inputBrowseFileDialog->FileName != L""){
			inputTextBox->Text = inputBrowseFileDialog->FileName;
			if (encodeRadioButton->Checked){
				outputTextBox->Text = inputTextBox->Text->Substring(0, inputTextBox->Text->LastIndexOf('.')+1) + L"pi";
			} else {
				outputTextBox->Text = inputTextBox->Text->Substring(0, inputTextBox->Text->LastIndexOf('\\')+1) + L"output";			
			}
		}
	}
	private: System::Void outputBrowseButton_Click(System::Object^  sender, System::EventArgs^  e) {
		outputBrowseFileDialog->ShowDialog();
		if (outputBrowseFileDialog->FileName != L""){
			outputTextBox->Text = outputBrowseFileDialog->FileName;
		}
	}

	private: System::Void startOperation_Click(System::Object^  sender, System::EventArgs^  e) {
		Encoder encoder(FORM);
		std::string input = msclr::interop::marshal_as<std::string>(inputTextBox->Text);
		std::string output = msclr::interop::marshal_as<std::string>(outputTextBox->Text);
		if (encodeRadioButton->Checked){
			encoder.encode(input, output);
			//show dialog
		} else {
			encoder.decode(input, output);
		}
	}
};
}
