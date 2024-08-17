#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <iostream>
#include <vector>
#include <string>
#include <list>

using std::string; using std::vector; using std::ostream;
using std::cout; using std::cin; using std::endl;

class Node
{
	private:
		string name;
		string constant;
		char variable;
		char exponent;

		friend class Statement;

	public:
		Node(string c = "1", char var = '\0', char exp = '1'):
			constant(c), variable(var), exponent(exp) {}
};

class Statement
{
	private:
		int index;
		vector<char> mem;

		string expression();
		string term();
		Node factor();
		Node diff(Node &);

	public:
		Statement()
		{
			index = 0;
		}
		void load(const string &);
};

#endif
