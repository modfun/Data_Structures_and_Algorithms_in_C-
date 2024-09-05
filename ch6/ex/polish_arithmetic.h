#ifndef POLISH_ARITHMETIC
#define POLISH_ARITHMETIC

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdlib.h>

using std::string; using std::vector; using std::istringstream;

struct TreeNode
{
	string value;
	TreeNode *left;
	TreeNode *right;

	TreeNode(string v, TreeNode *l = nullptr, TreeNode *r = nullptr):
		value(v), left(l), right(r) {}
};

class ExpressionTree
{
	TreeNode *root;
	vector<string> tokens;
	size_t index;

	public:
		ExpressionTree(const string &expr)
		{
			index = 0;

			tokenise(expr);
			if (tokens.size() != 0)
				root = buildTree();
			else
				root = nullptr;
		}
		~ExpressionTree()
		{
			deleteTree(root);
		}

		int evaluate()
		{
			if (root != nullptr)
				return (evaluateTree(root));
			else
				return (0);
		}

	private:
		void tokenise(const string &);
		TreeNode *buildTree();
		bool isOperator(const string &);
		int evaluateTree(TreeNode *);
		void deleteTree(TreeNode *);
};

void ExpressionTree::tokenise(const string &expr)
{
	string token;
	istringstream iss(expr);

	while (iss >> token)
		tokens.push_back(token);
}

TreeNode *ExpressionTree::buildTree()
{
	if (index >= tokens.size())
		return (nullptr);

	string token = tokens[index++];
	TreeNode *n = new TreeNode(token);

	if (isOperator(token))
	{
		n->left = buildTree();
		n->right = buildTree();
	}

	return (n);
}

bool ExpressionTree::isOperator(const string &s)
{
	return (s == "*" || s == "/" || s == "+" || s == "-" || s == "^");
}


int ExpressionTree::evaluateTree(TreeNode *n)
{
	bool loff = true, roff = true;
	int lval = 0, rval = 0;

	if (!n->left && !n->right)
		return (stoi(n->value));

	if (n->left != nullptr)
		lval = evaluateTree(n->left);
	else
		loff = false;

	if (n->right != nullptr)
		rval = evaluateTree(n->right);
	else
		roff = false;

	if (loff || roff)
	{
		if (n->value == "-")
			return -lval - rval;
		else if (n->value == "+")
			return lval + rval;
	}

	char c = n->value[0];
	switch(c)
	{
		case '*':
			return lval * rval;
			break;
		case '/':
			return lval / rval;
			break;
		case '+':
			return lval + rval;
			break;
		case '-':
			return lval - rval;
			break;
		default:
			break;
	}

	return (0);
}

void ExpressionTree::deleteTree(TreeNode *n)
{
	if (n != nullptr)
	{
		deleteTree(n->left);
		deleteTree(n->right);
		delete n;
	}
}

#endif
