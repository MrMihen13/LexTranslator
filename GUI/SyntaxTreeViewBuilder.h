#pragma once

#include "../Core/token.h"
#include "../Core/syntax_node.h"

#include <list>

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	public ref class SyntaxTreeViewBuilder
	{
	public: TreeView^ treeView;

	public:	SyntaxTreeViewBuilder(TreeView^ treeView)
		: treeView(treeView)
	{ }

	public: void build(std::list<SyntaxNode>& ruleNodes, std::list<::Token>& tokens) {
			  TreeNode^ root = gcnew TreeNode(L"S");

			  buildCascade(root, ruleNodes, tokens, 0);

			  treeView->Nodes->Add(root);
		  }

		  void buildCascade(TreeNode^ parent, std::list<SyntaxNode>& rnodes,
			  std::list<::Token>& tokens, int depth) {
			  if (rnodes.empty())
				  return;

			  auto& rnode = rnodes.back();
			  auto items = rnode.syntaxRule.buildRule.items;

			  System::Collections::Generic::List<TreeNode^> treenodes;

			  for (int i = items.size() - 1; i >= 0; --i) {
				  // TODO: not only for IDENTIFIER 
				  if (items[i] == SyntaxChars::IDENTIFIER && !rnodes.empty()) {
					  String^ text = gcnew String(tokens.back().value.c_str());
					  tokens.pop_back();
					  TreeNode^ node = gcnew TreeNode(text);
					  treenodes.Add(node);
				  }
				  else {
					  String^ text = gcnew String(items[i].tokenString.c_str());
					  TreeNode^ node = gcnew TreeNode(text);
					  treenodes.Add(node);
					  if (items[i] == SyntaxChars::NONTERMINAL && !rnodes.empty()) {
						  rnodes.pop_back();
						  buildCascade(node, rnodes, tokens, depth + 1);
					  }
				  }
			  }

			  for (int i = treenodes.Count - 1; i >= 0; --i) {
				  parent->Nodes->Add(treenodes[i]);
			  }
		  }
	};
}