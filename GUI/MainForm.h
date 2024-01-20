#pragma once

#include "../Core/lexer.h"
#include "../Core/parse_result.h"
#include "../Core/parse_item.h"
#include "../Core/command_splitter.h"
#include "../Core/token.h"

#include "../Core/current_config.h"

#include "../SYNTAX/syntax.h"

#include "SyntaxTreeViewBuilder.h"


#include <msclr/marshal_cppstd.h>

#include <string>
#include <sstream>
#include <list>
#include "../Core/ref_tree.h"
#include "../Core/ref_value.h"
#include "../Core/syntax_tree_by_char_builder.h"
#include "../Core/operators_tree_builder.h"
#include "OperatorsTreeViewBuilder.h"
#include "../Core/triads_builder.h"
#include "../Core/triadopt2.h"



namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form {
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^ Tabs;
	protected:
	private: System::Windows::Forms::TabPage^ PageSource;
	private: System::Windows::Forms::TextBox^ SourceCodeTxt;

	private: System::Windows::Forms::TextBox^ SourceFileTxt;
	private: System::Windows::Forms::TabPage^ TokensPage;



	private: System::Windows::Forms::Button^ ExecuteBtn;

	private: System::Windows::Forms::Button^ ClearSourceBtn;


	private: System::Windows::Forms::Button^ FileBtn;
	private: System::Windows::Forms::DataGridView^ TokensTable;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Index;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Token;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ TokenType;
	private: System::Windows::Forms::TabPage^ SyntaxPage;


	private: System::Windows::Forms::TreeView^ SyntaxTreeView;































	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->Tabs = (gcnew System::Windows::Forms::TabControl());
			this->PageSource = (gcnew System::Windows::Forms::TabPage());
			this->ExecuteBtn = (gcnew System::Windows::Forms::Button());
			this->ClearSourceBtn = (gcnew System::Windows::Forms::Button());
			this->FileBtn = (gcnew System::Windows::Forms::Button());
			this->SourceCodeTxt = (gcnew System::Windows::Forms::TextBox());
			this->SourceFileTxt = (gcnew System::Windows::Forms::TextBox());
			this->TokensPage = (gcnew System::Windows::Forms::TabPage());
			this->TokensTable = (gcnew System::Windows::Forms::DataGridView());
			this->Index = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Token = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TokenType = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SyntaxPage = (gcnew System::Windows::Forms::TabPage());
			this->SyntaxTreeView = (gcnew System::Windows::Forms::TreeView());
			this->Tabs->SuspendLayout();
			this->PageSource->SuspendLayout();
			this->TokensPage->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TokensTable))->BeginInit();
			this->SyntaxPage->SuspendLayout();
			this->SuspendLayout();
			// 
			// Tabs
			// 
			this->Tabs->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Tabs->Controls->Add(this->PageSource);
			this->Tabs->Controls->Add(this->TokensPage);
			this->Tabs->Controls->Add(this->SyntaxPage);
			this->Tabs->Location = System::Drawing::Point(22, 22);
			this->Tabs->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->Tabs->Name = L"Tabs";
			this->Tabs->SelectedIndex = 0;
			this->Tabs->Size = System::Drawing::Size(834, 514);
			this->Tabs->TabIndex = 0;
			// 
			// PageSource
			// 
			this->PageSource->BackColor = System::Drawing::Color::SeaGreen;
			this->PageSource->Controls->Add(this->ExecuteBtn);
			this->PageSource->Controls->Add(this->ClearSourceBtn);
			this->PageSource->Controls->Add(this->FileBtn);
			this->PageSource->Controls->Add(this->SourceCodeTxt);
			this->PageSource->Controls->Add(this->SourceFileTxt);
			this->PageSource->Location = System::Drawing::Point(4, 41);
			this->PageSource->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->PageSource->Name = L"PageSource";
			this->PageSource->Padding = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->PageSource->Size = System::Drawing::Size(826, 469);
			this->PageSource->TabIndex = 0;
			this->PageSource->Text = L"Исходный код";
			// 
			// ExecuteBtn
			// 
			this->ExecuteBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ExecuteBtn->BackColor = System::Drawing::Color::DarkSeaGreen;
			this->ExecuteBtn->Location = System::Drawing::Point(679, 13);
			this->ExecuteBtn->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->ExecuteBtn->Name = L"ExecuteBtn";
			this->ExecuteBtn->Size = System::Drawing::Size(124, 42);
			this->ExecuteBtn->TabIndex = 4;
			this->ExecuteBtn->Text = L"Запустить";
			this->ExecuteBtn->UseVisualStyleBackColor = false;
			this->ExecuteBtn->Click += gcnew System::EventHandler(this, &MainForm::ExecuteBtn_Click);
			// 
			// ClearSourceBtn
			// 
			this->ClearSourceBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ClearSourceBtn->BackColor = System::Drawing::Color::DarkSeaGreen;
			this->ClearSourceBtn->Location = System::Drawing::Point(543, 13);
			this->ClearSourceBtn->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->ClearSourceBtn->Name = L"ClearSourceBtn";
			this->ClearSourceBtn->Size = System::Drawing::Size(124, 42);
			this->ClearSourceBtn->TabIndex = 3;
			this->ClearSourceBtn->Text = L"Очистить";
			this->ClearSourceBtn->UseVisualStyleBackColor = false;
			this->ClearSourceBtn->Click += gcnew System::EventHandler(this, &MainForm::ClearSourceBtn_Click);
			// 
			// FileBtn
			// 
			this->FileBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->FileBtn->BackColor = System::Drawing::Color::DarkSeaGreen;
			this->FileBtn->Location = System::Drawing::Point(407, 13);
			this->FileBtn->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->FileBtn->Name = L"FileBtn";
			this->FileBtn->Size = System::Drawing::Size(124, 42);
			this->FileBtn->TabIndex = 2;
			this->FileBtn->Text = L"Файл";
			this->FileBtn->UseVisualStyleBackColor = false;
			this->FileBtn->Click += gcnew System::EventHandler(this, &MainForm::FileBtn_Click);
			// 
			// SourceCodeTxt
			// 
			this->SourceCodeTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->SourceCodeTxt->BackColor = System::Drawing::SystemColors::Info;
			this->SourceCodeTxt->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SourceCodeTxt->Location = System::Drawing::Point(12, 58);
			this->SourceCodeTxt->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->SourceCodeTxt->Multiline = true;
			this->SourceCodeTxt->Name = L"SourceCodeTxt";
			this->SourceCodeTxt->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->SourceCodeTxt->Size = System::Drawing::Size(893, 487);
			this->SourceCodeTxt->TabIndex = 1;
			this->SourceCodeTxt->WordWrap = false;
			// 
			// SourceFileTxt
			// 
			this->SourceFileTxt->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->SourceFileTxt->BackColor = System::Drawing::SystemColors::Info;
			this->SourceFileTxt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SourceFileTxt->Location = System::Drawing::Point(12, 13);
			this->SourceFileTxt->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->SourceFileTxt->Name = L"SourceFileTxt";
			this->SourceFileTxt->ReadOnly = true;
			this->SourceFileTxt->Size = System::Drawing::Size(384, 42);
			this->SourceFileTxt->TabIndex = 0;
			// 
			// TokensPage
			// 
			this->TokensPage->Controls->Add(this->TokensTable);
			this->TokensPage->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TokensPage->Location = System::Drawing::Point(4, 41);
			this->TokensPage->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->TokensPage->Name = L"TokensPage";
			this->TokensPage->Padding = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->TokensPage->Size = System::Drawing::Size(826, 469);
			this->TokensPage->TabIndex = 1;
			this->TokensPage->Text = L"Таблица лексем";
			this->TokensPage->UseVisualStyleBackColor = true;
			// 
			// TokensTable
			// 
			this->TokensTable->AllowUserToAddRows = false;
			this->TokensTable->AllowUserToDeleteRows = false;
			this->TokensTable->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->TokensTable->BackgroundColor = System::Drawing::SystemColors::Info;
			this->TokensTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->TokensTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Index, this->Token,
					this->TokenType
			});
			this->TokensTable->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TokensTable->Location = System::Drawing::Point(6, 7);
			this->TokensTable->Name = L"TokensTable";
			this->TokensTable->RowHeadersWidth = 51;
			this->TokensTable->Size = System::Drawing::Size(814, 455);
			this->TokensTable->TabIndex = 0;
			// 
			// Index
			// 
			this->Index->FillWeight = 10;
			this->Index->HeaderText = L"№";
			this->Index->MinimumWidth = 6;
			this->Index->Name = L"Index";
			this->Index->ReadOnly = true;
			// 
			// Token
			// 
			this->Token->HeaderText = L"Лексема";
			this->Token->MinimumWidth = 6;
			this->Token->Name = L"Token";
			this->Token->ReadOnly = true;
			// 
			// TokenType
			// 
			this->TokenType->HeaderText = L"Тип лексемы";
			this->TokenType->MinimumWidth = 6;
			this->TokenType->Name = L"TokenType";
			this->TokenType->ReadOnly = true;
			this->TokenType->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// SyntaxPage
			// 
			this->SyntaxPage->Controls->Add(this->SyntaxTreeView);
			this->SyntaxPage->Location = System::Drawing::Point(4, 41);
			this->SyntaxPage->Name = L"SyntaxPage";
			this->SyntaxPage->Padding = System::Windows::Forms::Padding(3);
			this->SyntaxPage->Size = System::Drawing::Size(826, 469);
			this->SyntaxPage->TabIndex = 2;
			this->SyntaxPage->Text = L"Синтаксическое дерево";
			this->SyntaxPage->UseVisualStyleBackColor = true;
			// 
			// SyntaxTreeView
			// 
			this->SyntaxTreeView->BackColor = System::Drawing::SystemColors::Info;
			this->SyntaxTreeView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SyntaxTreeView->Location = System::Drawing::Point(3, 3);
			this->SyntaxTreeView->Name = L"SyntaxTreeView";
			this->SyntaxTreeView->Size = System::Drawing::Size(820, 463);
			this->SyntaxTreeView->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(13, 32);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::MediumSeaGreen;
			this->ClientSize = System::Drawing::Size(878, 560);
			this->Controls->Add(this->Tabs);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(6, 7, 6, 7);
			this->Name = L"MainForm";
			this->Text = L"МережниковКА Вариант№4";
			this->Tabs->ResumeLayout(false);
			this->PageSource->ResumeLayout(false);
			this->PageSource->PerformLayout();
			this->TokensPage->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TokensTable))->EndInit();
			this->SyntaxPage->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void FileBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog openFileDialog;
		openFileDialog.DefaultExt = "sсv5";
		openFileDialog.Filter = "Файлы кода (*.scv5)|*.scv5";
		openFileDialog.ShowDialog();

		System::String^ fileName = openFileDialog.FileName;

		if (!System::String::IsNullOrWhiteSpace(fileName)) {
			SourceFileTxt->Text = fileName;
			System::String^ sourceCode = System::IO::File::ReadAllText(fileName);
			SourceCodeTxt->Text = sourceCode;
		}
		else {
			MessageBox::Show(this, "Выбор файла был отменен!", "Сообщение");
		}
	}

	private: System::Void ClearSourceBtn_Click(System::Object^ sender, System::EventArgs^ e) {	
		SourceFileTxt->Clear();
		SourceCodeTxt->Clear();
		TokensTable->Rows->Clear();
		SyntaxTreeView->Nodes->Clear();
		//OpersTreeView->Nodes->Clear();
		//Triads1->Rows->Clear();
		//Triads2->Rows->Clear();
		//Triads3->Rows->Clear();
	}

	private: System::Void ExecuteBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		
		setlocale(LC_ALL, "");
		

		if (String::IsNullOrWhiteSpace(SourceCodeTxt->Text)) {
			MessageBox::Show(this, "Нет данных для распознавания!", "Сообщение");
			return;
		}

		std::string sourceCode = msclr::interop::marshal_as<std::string>(SourceCodeTxt->Text);

		ParseResult result = Parser()
			.parse(sourceCode);

		if (!result.isSuccess()) {
			parseResultError(sourceCode, result);	
			return;
		}
		
		fillDataGridViewWithTokens(result);

		auto commands = MathCommandSplitter().split(result);

		//int tcount = 0;

		//std::vector<Triad*> triads_;
		//std::map<std::string, Triad*> vars;

		//std::list<Triad*> all_triads;

		for (auto& command : commands) {
			if (command.isValid) {
				Syntax syntax = Syntax(CurrentSyntaxConfig);
				
				auto syntaxResult = syntax.proccess(command);
				
				if (!syntaxResult.isSuccess()) {
					std::cout << syntaxResult.message << "\n";
					syntaxResultError(syntaxResult);
					return;
				}
				
				std::list<SyntaxNode> ruleNodes = syntaxResult.nodes;

				for (auto& it = ruleNodes.rbegin(); it != ruleNodes.rend(); it++) {
					std::cout << it->syntaxRule.buildRule << "\t" 
						<< it->syntaxRule.buildRule.ruleString  << "\n";
				}

				SyntaxTreeViewBuilder(SyntaxTreeView)
					.build(ruleNodes, command.getValueTokens());	

				// Построение дерева операций
				std::list<SyntaxNode> ruleNodes2 = syntaxResult.nodes;
				RefTree<RefValue> myTreeRefView;
				
				SyntaxTreeByCharBuilder(myTreeRefView)
					.build(ruleNodes2, command.getValueTokens());
				
				OperatorsTreeBuilder(myTreeRefView)
					.build();
				
				////OperatorsTreeViewBuilder(OpersTreeView)
				////	.build(myTreeRefView);
				//
				//std::list<Triad*> triads = TriadBuilderV2(myTreeRefView)
				//	.build(tcount);

				//tcount += triads.size();
				//
				//for (Triad* triad : triads) {
				//	all_triads.push_back(triad);
				//}
			}
		}

		//fillTriadsTable(Triads1, all_triads);

		//
		//TriadOpt1 triadOpt1(all_triads);
		//triadOpt1.reduce();
		//if (triadOpt1.error) {
		//	MessageBox::Show(this, gcnew String(triadOpt1.message.c_str()), "Ошибка");
		//	return;
		//}
		//

		//fillTriadsTable(Triads2, all_triads);

		//TriadOpt2 triadOpt2(all_triads);

		//triadOpt2.setDepValues();
		//triadOpt2.clearSameTriads();

		//fillTriadsTable(Triads3, all_triads);

		MessageBox::Show(this, "Анализ текста выполнен успешно!", "Сообщение");
	}

	private: void fillTriadsTable(DataGridView^ table, std::list<Triad*>& triads) {
		for (Triad* triad : triads) {
			table->Rows->Add(
				System::Int32(triad->id),
				gcnew String(triad->toString().c_str())
			);
		}
	}

	private: void parseResultError(std::string& source, ParseResult& result) {
		std::stringstream ss;

		int index = source.size() > result.current.index
			? result.current.index
			: source.size() - 1;

		char inputChar = source.at(index);

		ss << "Встречена ошибка на этапе \"Лексический анализ\":\n\n"
			<< "В символе: " << index << ";\n"
			<< "Входной симол \'" << inputChar << " \'(ASCII:" << (int)inputChar << ")\n\n"
			<< "Сообщение: " << result.items.at(result.items.size() - 1).statusCode.toString() << ".";

		String^ message = gcnew String(ss.str().c_str());

		MessageBox::Show(message);
	}

	private: void syntaxResultError(SyntaxResult& result) {
		std::stringstream ss;

			ss << "Встречена ошибка на этапе \"Синтаксический анализ\":\n\n"
			   << "Сообщение: " << result.message << ".";

			   String^ message = gcnew String(ss.str().c_str());

			   MessageBox::Show(message);
		   }

    private: void fillDataGridViewWithTokens(ParseResult& result) {
			TokensTable->Rows->Clear();

			for (int i = 0; i < result.items.size(); ++i) {
				String^ tokenString = gcnew String(result.items[i].token.value.c_str());
				String^ typeNameString = gcnew String(result.items[i].token.type.toString().c_str());
				TokensTable->Rows->Add(System::Int32(i + 1), tokenString, typeNameString);
			}
	    }
	};
}

