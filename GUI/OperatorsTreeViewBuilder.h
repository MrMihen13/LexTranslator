#pragma once

#include "../Core/syntax_node.h"
#include "../Core/token.h"
#include "../Core/ref_tree.h"
#include "../Core/ref_value.h"
#include <list>

namespace GUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


public ref class OperatorsTreeViewBuilder
	{
	public: TreeView^ treeView;

	public:	OperatorsTreeViewBuilder(TreeView^ treeView)
		: treeView(treeView)
	{ }

	public: void build(RefTree<RefValue>& refTree) {
		if (refTree.root->items.size() != 0) {
			std::string data = getNodeDataString(refTree.root->items[0]);
			TreeNode^ root = gcnew TreeNode(gcnew String(data.c_str()));
			buildCascade(root, refTree.root->items[0]);
			treeView->Nodes->Add(root);
		}		
	}


	public: void buildCascade(TreeNode^ parent, RefTreeNode<RefValue>* node)  {
		System::Collections::Generic::List<TreeNode^> treenodes;

		for (int i = node->items.size() - 1; i >= 0; --i) {			
			std::string data = getNodeDataString(node->items[i]);
			String^ text = gcnew String(data.c_str());
			TreeNode^ treenode = gcnew TreeNode(text);
			buildCascade(treenode, node->items[i]);
			treenodes.Add(treenode);
		}

		for (int i = treenodes.Count - 1; i >= 0; --i) {
			parent->Nodes->Add(treenodes[i]);
		}
	}

	private: std::string getNodeDataString(RefTreeNode<RefValue>* node) {
		std::string data;
		if (*node->value->syntaxChar == SyntaxChars::IDENTIFIER) {
			data = node->value->value->value;
		}
		else {
			data = node->value->syntaxChar->tokenString;
		}
		return data;
	}
	};
}

