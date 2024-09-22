#ifndef CROSS_REFERENCE_H
#define CROSS_REFERENCE_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

using std::string;

struct LineNode
{
	int lineNumber;
	LineNode *next;

	LineNode(int ln, LineNode *ptr = nullptr):
		lineNumber(ln), next(ptr) {}
};

struct TreeNode
{
	string word;
	LineNode *lines;
	TreeNode *left;
	TreeNode *right;

	TreeNode(const string &w, int ln)
	{
		word = w;
		lines = new LineNode(ln);

		left = right = nullptr;
	}
	~TreeNode()
	{
		while (lines != nullptr)
		{
			auto temp = lines;
			lines = lines->next;
			delete temp;
		}
	}

	bool checkLineNumber(int) const;
	void printLines() const;
};

class BinarySearchTree
{
	TreeNode *root;

	public:
		BinarySearchTree():
			root(nullptr) {}
		~BinarySearchTree()
		{
			if (root != nullptr)
				deleteTree(root);
		}

		void insert(const string &w, int ln)
		{
			insert(root, w, ln);
		}
		void inOrderPrint() const
		{
			if (root != nullptr)
				inOrderPrint(root);
		}

	private:
		void insert(TreeNode *&, const string &, int);
		void inOrderPrint(TreeNode *) const;
		void deleteTree(TreeNode *);
		friend void processFile(const string &, BinarySearchTree *);
};

bool TreeNode::checkLineNumber(int ln) const
{
	auto temp = lines;
	while (temp != nullptr)
	{
		if (temp->lineNumber == ln)
			return (true);
		temp = temp->next;
	}
	return (false);
}
void TreeNode::printLines() const
{
	auto temp = lines;
	while (temp != nullptr)
	{
		std::cout << temp->lineNumber << ", ";
		temp = temp->next;
	}
}

void BinarySearchTree::insert(TreeNode *&node, const string &w, int ln)
{
	if (node == nullptr)
		node = new TreeNode(w, ln);
	else
	{
		if (w < node->word)
		{
			insert(node->left, w, ln);
		}
		else if (w > node->word)
		{
			insert(node->right, w, ln);
		}
		else
		{
			if (!node->checkLineNumber(ln))
			{
				auto temp = node->lines;
				while (temp->next != nullptr)
					temp = temp->next;
				temp->next = new LineNode(ln);
			}
		}
	}
}

void BinarySearchTree::inOrderPrint(TreeNode *node) const
{
	if (node != nullptr)
	{
		inOrderPrint(node->left);
		std::cout << node->word << ": ";
		node->printLines();
		std::cout << "\n";
		inOrderPrint(node->right);
	}
}

void processFile(const string &filename, BinarySearchTree *bst)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	string line;
	int lineNumber = 0;

	while (getline(file, line))
	{
		lineNumber++;
		std::stringstream ss(line);
		string word;

		while (ss >> word)
		{
			// Remove punctuation from words
			word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

			// Convert word to lowercase
			for (char &c : word)
				c = tolower(c);

			// Insert the word into the BST
			bst->insert(word, lineNumber);
		}
	}

	file.close();
}

void BinarySearchTree::deleteTree(TreeNode *n)
{
	if (n != nullptr)
	{
		deleteTree(n->left);
		deleteTree(n->right);
		delete n;
	}
}

#endif
