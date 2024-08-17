#ifndef BASIC_LINT_H
#define BASIC_LINT_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <cctype>

using std::string; using std::vector; using std::list;
using std::fstream; using std::istringstream;
using std::cout; using std::cin; using std::endl; using std::getline;
using std::isalpha;
typedef istringstream iss;

struct Variable
{
	string identifier;
	string type;
	bool init;

	Variable(string s, string t, bool i=false):
		identifier(s), type(t), init(i) {}

	protected:
		friend bool operator==(const Variable &, const Variable &);
		friend bool operator!=(const Variable &, const Variable &);
};

bool operator==(const Variable &left, const Variable &right)
{
	if (left.identifier != right.identifier || left.type != right.type)
		return (false);
	return (true);
}

bool operator!=(const Variable &left, const Variable &right)
{
	return (!(left == right));
}

#endif
