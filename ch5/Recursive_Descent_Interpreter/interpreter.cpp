#include "interpreter.h"
#include <cstring>
#include <bits/stdc++.h>

using std::isspace; using std::isalnum; using std::isalpha;
using std::isdigit;

double Statement::factor()
{
	double var, minus = 1.0;
	string id;

	cin >> ch;
	while (ch == '-' || ch == '+')
	{
		if (ch == '-')
			minus *= -1.0;
		cin >> ch;
	}
	if (isdigit(ch) || ch == 'i')
	{
		cin.putback(ch);
		cin >> var >> ch;
	}
	else if (ch == '(')
	{
		var = expression();
		if (ch == ')')
			cin >> ch;
		else
			issueError("Right Paren left out");
	}
	else
	{
		readId(id);
		if (isspace(ch))
			cin >> ch;
		var = findValue(id);
	}

	return (minus*var);
}

double Statement::term()
{
	double f = factor();
	while (true)
	{
		switch (ch)
		{
			case '*':
				f *= factor();
				break;
			case '/':
				f /= factor();
				break;
			default:
				return (f);
		}
	}
}

double Statement::expression()
{
	double t = term();
	while (true)
	{
		switch (ch)
		{
			case '+':
				t += term();
				break;
			case '-':
				t -= term();
				break;
			default:
				return (t);
		}
	}
}

void Statement::readId(string s)
{
	int i = 0;
	if (isspace(ch))
		cin >> ch;
	if (isalpha(ch))
	{
		while (isalnum(ch))
		{
			s[i++] = ch;
			cin.get(ch);
		}
		s = s + '\0';
	}
	else 
		issueError("Identifier expected");
}

void Statement::processNode(string id, double e)
{
	IdNode tmp(id, e);

	list<IdNode>::iterator i = find(idList.begin(), idList.end(), tmp);
	if (i != idList.end())
		i->value = e;
	else
		idList.push_front(tmp);
}

double Statement::findValue(string id)
{
	IdNode tmp(id);

	list<IdNode>::iterator i = find(idList.begin(), idList.end(), tmp);
	if (i != idList.end())
		return (i->value);
	else
		issueError("Unknown variable");
	return (0);
}

void Statement::getStatement()
{
	string id, command;
	double e;

	cout << "Enter a Statement: ";
	cin >> ch;
	readId(id);

	command = id;
	for (auto & c : command) c = toupper(c);
	if (command == "STATUS")
		cout << *this;
	else if (command == "PRINT")
	{
		readId(id);
		cout << id << " = " << findValue(id) << endl;
	}
	else if (command == "END")
		exit(0);
	else
	{
		if (isspace(ch))
			cin >> ch;
		if (ch == '=')
		{
			e = expression();
			if (ch != ';')
				issueError("There are some extras in the statement");
			else
				processNode(id, e);
		}
		else
			issueError("'=' is missing");
	}
}

