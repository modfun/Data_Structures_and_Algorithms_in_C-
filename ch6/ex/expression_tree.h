#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using std::string; using std::vector;

struct TNode
{
	string value;
	TNode *left;
	TNode *right;

	TNode(string val, TNode *l = nullptr, TNode *r = nullptr):
		value(val), left(l), right(r) {}
};

class ExpressionTree
{
	TNode *root;
	vector<string> token_list;
	size_t index;
	size_t size;

	public:
		ExpressionTree(const string &);
		~ExpressionTree(void);

		string differentiate(void);

	private:
		void tokenise(const string &);
		TNode *buildTree(void);
		bool isOperator(const string &);
		string differentiate(TNode *);
		bool isVariable(const string &);
		bool isConstant(const string &);
		void deleteTree(TNode *);
};

ExpressionTree::ExpressionTree(const string &expr)
{
	index = 0;
	size = 0;

	tokenise(expr);
	if (token_list.size() != 0)
		root = buildTree();
	else
		root = nullptr;
}

ExpressionTree::~ExpressionTree(void)
{
	if (root != nullptr)
		deleteTree(root);
}

string ExpressionTree::differentiate(void)
{
	if (root != nullptr)
		return (differentiate(root));
	return ("");
}

string ExpressionTree::differentiate(TNode *n)
{
	if (isOperator(n->value))
	{
		char c = n->value[0];
		switch(c)
		{
			case '+':
				return (differentiate(n->left) + " + " +
					differentiate(n->right));
				break;
			case '-':
				return (differentiate(n->left) + " - " +
					differentiate(n->right));
				break;
			case '*':
				return (differentiate(n->left) + " * " +
				n->right->value + " + " + n->left->value +
				" * " + differentiate(n->right));
				break;
			case '/':
				break;
			case '^':
				break;
			default:
				break;
		}
	}
	else if (isVariable(n->value))
	{
		return (" 1 ");
	}
	else if (isConstant(n->value))
	{
		return (" 0 ");
	}

	return ("");
}

bool ExpressionTree::isVariable(const string &s)
{
	for (char c : s)
		if (!isalpha(c)) return (false);
	return (true);
}

bool ExpressionTree::isConstant(const string &s)
{
	for (char c : s)
		if (!isdigit(c)) return (false);
	return (true);
}

void ExpressionTree::tokenise(const string &expr)
{
	string token;

	std::istringstream iss(expr);
	while (iss >> token)
		token_list.push_back(token);

	size = token_list.size();
}

TNode *ExpressionTree::buildTree(void)
{	// Expect expression in Poilsh notation.
	if (index >= size)
		return (nullptr);

	string token = token_list[index++];
	TNode *n = new TNode(token);

	if (isOperator(token))
	{
		n->left = buildTree();
		n->right = buildTree();
	}

	return (n);
}

bool ExpressionTree::isOperator(const string &s)
{
	return (s == "*" || s == "/" ||
		s == "+" || s == "-" ||
		s == "^");
}

void ExpressionTree::deleteTree(TNode *n)
{
	if (n != nullptr)
	{
		deleteTree(n->left);
		deleteTree(n->right);
		delete n;
	}
}

#endif
