#include "differentiation.h"

Node Statement::diff(Node &n)
{
	Node r;
	if (n.exponent == 0) r.constant = 0;
	else if (n.exponent = 1) r.constant = n.constant;
	else
	{
		r.constant = (int)n.constant * (int)n.exponent;
		r.exponent = n.exponent - 1;
		r.variable = n.variable;
	}
	return (r);
}

Node Statement::factor()
{
	Node n;

	while (index < (int)mem.size())
	{
		if (mem[index] >= '0' || mem[index] <= '9')
		{
			n.constant += mem[index++];
			continue;
		}

		switch (mem[index])
		{
			case 'x':
				n.variable = 'x';
				index++;
				break;
			case 'y':
				n.variable = 'y';
				index++;
				break;
			case '^':
				index++;
				n.exponent = mem[index];
				break;
			default:
				break;
		}
	}

	return (n);
}

string Statement::term()
{
	Node n = factor();
	Node a;
	String s = "";
	while (index < (int)mem.size())
	{
		switch (mem[index])
		{
			case '*':
				index++;
				a = factor();
				break;
			case '/':
				index++;
				a = factor();
				break;
			default:
				break;
		}
	}
}

string Statement::expression()
{
	string s = term();
	while (index < (int)mem.size())
	{
		switch (mem[index])
		{
			case '+':
				index++;
				s += '+' + term();
				break;
			case '-':
				index++;
				s += '-' + term();
				break;
			default:
				break;
		}
	}
}

void Statement::load(const string &s)
{
	for (auto &c : s)
		mem.push_back(c);
}

int main()
{
	return (EXIT_SUCCESS);
}
