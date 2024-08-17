#include <iostream>
#include <string>
#include <stack>
#include <fstream>

using std::stack; using std::fstream; using std::string;
using std::cout; using std::endl; using std::getline;

bool delimiterMatching(fstream &f)
{
	string l = "";
	stack<char> s;

	while (getline(f, l))
	{
		cout << l << '\n';
		for (auto c : l)
		{
			if (c == '(' || c == '[' || c == '{')
			{
				s.push(c);
			}
			else if (c == ')')
			{
				if (s.empty() || s.top() != '(')
					return (false);
				if (!s.empty()) s.pop();
			}
			else if (c == '}')
			{
				if (s.empty() || s.top() != '{')
					return (false);
				if (!s.empty()) s.pop();
			}
			else if (c == ']')
			{
				if (s.empty() || s.top() != '[')
					return (false);
				if (!s.empty()) s.pop();
			}
		}
	}
	if (s.empty())
		return (true);
	else
		return (false);
}

int main()
{
	fstream file;
	file.open("test.txt", std::ios::in | std::ios::out);
	cout << delimiterMatching(file) << std::endl;
	file.close();

	return (0);
}
