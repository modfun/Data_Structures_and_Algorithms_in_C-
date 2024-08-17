#include "basic_lint.h"
/* not complete */

void loader(string fname, vector<vector<string >> &text)
{
	fstream file;
	string tmp;

	file.open(fname, std::ios::in);
	while (getline(file, tmp))
	{
		iss buf(tmp);
		vector<string> v;

		while (buf >> tmp) v.push_back(tmp);
		text.push_back(v);
	}
	file.close();
}

void print(vector<vector<string >> &text)
{
	for (auto &e : text)
	{
		for (auto &w : e)
			cout << w << "\n";
		cout << endl;
	}
}

bool isType(string t)
{
	string types[] = {"char", "short", "int", "long", "float", "double", "bool"};
	for (auto &e : types)
	{
		if (t == e) return (true);
	}
	return (false);
}

bool isValid(string i)
{
	if (i.size() > 0)
	{
		if (i[0] == '$' || i[0] == '_' || isalpha(i[0])) return (true);
	}
	return (false);
}

bool isVariable(const vector<string> &line)
{
	bool semi = false;
	for (auto &e : line)
	{
		if (e == ";") semi = true;
	}

	if (semi == true && line.size() > 2)
	{
		if (isType(line[0]))
		{
			if (isValid(line[1]))
				return (true);
		}
	}
	return (false);
}

bool isFunction(const vector<string> &line)
{
	bool semi = false;
	for (auto &e : line)
	{
		if (e == ";") semi = true;
	}

	if (semi == false && line.size() > 2)
	{
		if (isType(line[0]))
		{
			if (isValid(line[1]))
			{
				if (line[2][0] == '(') return (true);
			}
		}
	}

	return (false);
}

bool isInit(vector<string> line)
{
	return line[0] == "l";
}

void parser(string fname, vector<vector<string >> &text)
{
	loader(fname, text);

	list<Variable> globals;
	list<Variable> functions;
	bool inFunction = false;

	for (auto &l : text)
	{
		if (l.size() > 2)
		{
			if (isVariable(l))
			{
				Variable var(l[1], l[0], isInit(l));
				if (inFunction == true)
					functions.push_back(var);
				else
					globals.push_back(var);
			}
			else
			{
				if (isFunction(l))
				{
					inFunction = false;
					functions.clear();
				}
			}
		}
	}
}

void run(string fname)
{
	vector<vector<string >> text;

	parser(fname, text);
	print(text);
}


int main(void)
{
	run("basic_lint.h");
	vector<string> s ={"int", "node", "("};
	cout << isVariable(s) << endl;
	cout << isFunction(s) << endl;

	return (EXIT_SUCCESS);
}
