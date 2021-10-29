#pragma once
#include "Node.h"
#include <iostream>

#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <wtypes.h>

namespace KosianenkoHuffman {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Globalization;
	vector <bool> _code;
	map<char, vector<bool>> table;
	struct NodesCompare
	{
		bool operator()(const Node* l, const Node* r) const { return l->_integer < r->_integer; }
	};
	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		
	protected:

		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private: String^ file_input = "";
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button4;

	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(509, 33);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(113, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = L"open file";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(509, 98);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(184, 32);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Start Huffman compressor";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(27, 36);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(463, 22);
			this->textBox1->TabIndex = 2;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button3->Location = System::Drawing::Point(509, 149);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(184, 34);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Check compressed file";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(27, 98);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(463, 210);
			this->textBox2->TabIndex = 4;
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button4->Location = System::Drawing::Point(509, 207);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(184, 37);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Check decompressed file";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(793, 332);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


		
		void BuildTable(Node* root)
		{
			if (root->left != NULL)
			{
				_code.push_back(0);
				BuildTable(root->left);
			}

			if (root->right != NULL)
			{
				_code.push_back(1);
				BuildTable(root->right);
			}

			if (root->left == NULL && root->right == NULL) table[root->_char] = _code;
		
			if(!_code.empty()) _code.pop_back();
		}


		String^ HuffmanAlgorithm(String^ input)
		{

			////// считаем частоты символов
		  //  ifstream f("1.txt", ios::out | ios::binary);

			map<char, int> m;

			// while (!f.eof())
			// {
			//     char c = f.get();
			//     m[c]++;
			// }
			for (int i = 0; i < input->Length; i++)
			{
				char c = input[i];
				m[c]++;
			}

			////// записываем начальные узлы в список list

			list<Node*> t;
			for (map<char, int>::iterator itr = m.begin(); itr != m.end(); ++itr)
			{
				Node* p = new Node;
				p->_char = itr->first;
				p->_integer = itr->second;
				t.push_back(p);
			}


			//////  создаем дерево

			while (t.size() != 1)
			{
				t.sort(NodesCompare());

				Node* SonL = t.front();
				t.pop_front();
				Node* SonR = t.front();
				t.pop_front();

				Node* parent = new Node(SonL, SonR);
				t.push_back(parent);

			}

			Node* root = t.front();   //root - указатель на вершину дерева

		////// создаем пары 'символ-код':

			BuildTable(root);

			////// ¬ыводим коды в файл output.txt

		   // f.clear(); f.seekg(0); // перемещаем указатель снова в начало файла

			ofstream g("Compressed_output.txt", ios::out | ios::binary);

			int count = 0; char buf = 0;
			for (int i = 0; i < input->Length; i++)//  while (!f.eof())
			{
				char c = input[i];// f.get();
				vector<bool> x = table[c];
				for (int n = 0; n < x.size(); n++)
				{
					buf = buf | x[n] << (7 - count);
					count++;
					if (count == 8) { count = 0;   g << buf; buf = 0; }
				}
			}

			// f.close();
			g.close();

			///// считывание из файла output.txt и преобразование обратно

			ifstream F("Compressed_output.txt", ios::in | ios::binary);
			ofstream q("Readable_output.txt", ios::out | ios::binary);

			setlocale(LC_ALL, "Russian"); // чтоб русские символы отображались в командной строке
			String^ out = "";
			Node* p = root;
			count = 0; char byte;
			byte = F.get();
			while (!F.eof())
			{
				bool b = byte & (1 << (7 - count));
				if (b) p = p->right; else p = p->left;
				if (p->left == NULL && p->right == NULL)
				{
					q << p->_char;
					p = root;
				}
				count++;
				if (count == 8) { count = 0; byte = F.get(); }
			}

			F.close();
			q.close();
			return out;
		}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		String^ file_name = "";
		if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			file_name = openFileDialog1->FileName;
		}

		try 
		{
			StreamReader^ reader = File::OpenText(file_name);
			textBox1->Text = file_name;
			file_input = reader->ReadToEnd();
			reader->Close();
		}
		catch (Exception^ e) { MessageBox::Show(this, "Failed to open file", "Error" , MessageBoxButtons::OK, MessageBoxIcon::Error); }
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		HuffmanAlgorithm(file_input->ToString());
		button3->Enabled = true;
		button4->Enabled = true;
	}
	
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	textBox2->Text = "";
	StreamReader^ reader = File::OpenText("Compressed_output.txt");
	textBox2->Text = reader->ReadToEnd();
	reader->Close();
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) 
{
	textBox2->Text = "";
	StreamReader^ reader = File::OpenText("Readable_output.txt");
	textBox2->Text = reader->ReadToEnd();
	reader->Close();
}


};
}
