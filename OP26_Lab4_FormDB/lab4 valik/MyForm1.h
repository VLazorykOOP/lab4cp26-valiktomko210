#pragma once

#using <System.dll>
#using <System.Data.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Project1 {

	public ref class MyForm1 : public Form
	{
	public:
		MyForm1(void)
		{
			InitializeComponent();
			LoadData();
		}

	protected:
		~MyForm1()
		{
			if (components)
				delete components;
		}

	private:
		Label^ label1;
		Label^ label2;
		Label^ label3;
		Label^ label4;
		Label^ label5;
		Label^ label6;
		Label^ label7;
		Label^ label8;

		TextBox^ textBox1;
		TextBox^ textBox2;
		TextBox^ textBox3;
		TextBox^ textBox4;
		TextBox^ textBox5;
		TextBox^ textBox6;
		TextBox^ textBox7;
		TextBox^ textBox8;

		Button^ button1;
		DataGridView^ dataGridView1;

		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();

			label1 = gcnew Label();
			label1->Text = "Authors";
			label1->Location = Point(10, 15);

			label2 = gcnew Label();
			label2->Text = "NameBook";
			label2->Location = Point(10, 55);

			label3 = gcnew Label();
			label3->Text = "Publishing";
			label3->Location = Point(10, 95);

			label4 = gcnew Label();
			label4->Text = "Pages";
			label4->Location = Point(10, 135);

			label5 = gcnew Label();
			label5->Text = "Genre";
			label5->Location = Point(250, 15);

			label6 = gcnew Label();
			label6->Text = "Price";
			label6->Location = Point(250, 55);

			label7 = gcnew Label();
			label7->Text = "Storage";
			label7->Location = Point(250, 95);

			label8 = gcnew Label();
			label8->Text = "InventoryNumber";
			label8->Location = Point(250, 135);

			textBox1 = gcnew TextBox();
			textBox1->Location = Point(100, 12);

			textBox2 = gcnew TextBox();
			textBox2->Location = Point(100, 52);

			textBox3 = gcnew TextBox();
			textBox3->Location = Point(100, 92);

			textBox4 = gcnew TextBox();
			textBox4->Location = Point(100, 132);

			textBox5 = gcnew TextBox();
			textBox5->Location = Point(370, 12);

			textBox6 = gcnew TextBox();
			textBox6->Location = Point(370, 52);

			textBox7 = gcnew TextBox();
			textBox7->Location = Point(370, 92);

			textBox8 = gcnew TextBox();
			textBox8->Location = Point(370, 132);

			button1 = gcnew Button();
			button1->Text = "Додати";
			button1->Location = Point(370, 180);
			button1->Click += gcnew EventHandler(this, &MyForm1::button1_Click);

			dataGridView1 = gcnew DataGridView();
			dataGridView1->Location = Point(10, 230);
			dataGridView1->Size = Drawing::Size(560, 200);

			this->Controls->Add(label1);
			this->Controls->Add(label2);
			this->Controls->Add(label3);
			this->Controls->Add(label4);
			this->Controls->Add(label5);
			this->Controls->Add(label6);
			this->Controls->Add(label7);
			this->Controls->Add(label8);

			this->Controls->Add(textBox1);
			this->Controls->Add(textBox2);
			this->Controls->Add(textBox3);
			this->Controls->Add(textBox4);
			this->Controls->Add(textBox5);
			this->Controls->Add(textBox6);
			this->Controls->Add(textBox7);
			this->Controls->Add(textBox8);

			this->Controls->Add(button1);
			this->Controls->Add(dataGridView1);

			this->ClientSize = Drawing::Size(600, 460);
			this->Text = "LibraryDB";
			this->ResumeLayout(false);
		}
#pragma endregion

	private: void LoadData()
	{
		String^ connectStr =
			"Data Source=(localdb)\\MSSQLLocalDB;Initial Catalog=LibraryDB;Integrated Security=True";

		SqlConnection^ con = gcnew SqlConnection(connectStr);
		SqlDataAdapter^ da = gcnew SqlDataAdapter("SELECT * FROM Books", con);
		DataTable^ dt = gcnew DataTable();
		da->Fill(dt);
		dataGridView1->DataSource = dt;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			String^ connectStr =
				"Data Source=(localdb)\\MSSQLLocalDB;Initial Catalog=LibraryDB;Integrated Security=True";

			SqlConnection^ con = gcnew SqlConnection(connectStr);
			con->Open();

			String^ sql =
				"INSERT INTO Books (Authors, NameBook, Publishing, Pages, Genre, Price, Storage, InventoryNumber) "
				"VALUES (@Authors, @NameBook, @Publishing, @Pages, @Genre, @Price, @Storage, @InventoryNumber)";

			SqlCommand^ cmd = gcnew SqlCommand(sql, con);

			cmd->Parameters->AddWithValue("@Authors", textBox1->Text);
			cmd->Parameters->AddWithValue("@NameBook", textBox2->Text);
			cmd->Parameters->AddWithValue("@Publishing", textBox3->Text);
			cmd->Parameters->AddWithValue("@Pages", Convert::ToInt32(textBox4->Text));
			cmd->Parameters->AddWithValue("@Genre", textBox5->Text);
			cmd->Parameters->AddWithValue("@Price", Convert::ToDouble(textBox6->Text));
			cmd->Parameters->AddWithValue("@Storage", textBox7->Text);
			cmd->Parameters->AddWithValue("@InventoryNumber", textBox8->Text);

			cmd->ExecuteNonQuery();
			con->Close();

			MessageBox::Show("Запис додано!");

			LoadData();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
	};
}
