#include <iostream>
#include <string>
#include <stack>

using std::cout; using std::cin; using std::endl;
using std::stack; using std::string;

string addingLargeNumbers(string a, string b)
{
	stack<int> s1, s2;
	stack<int> res;
	int carry = 0;
	int size = 0;

	for (unsigned int i = 0; i < a.size(); i++)
		s1.push(a[i] - '0');
	for (unsigned int i = 0; i < b.size(); i++)
		s2.push(b[i] - '0');

	while(!(s1.empty() && s2.empty()))
	{
		if (!s1.empty())
		{
			carry += s1.top();
			s1.pop();
		}
		if (!s2.empty())
		{
			carry += s2.top();
			s2.pop();
		}

		res.push(carry % 10);
		carry /= 10;
	}
	if (carry != 0) res.push(carry);

	size = res.size();
	string s = "";
	for (int i = 0; i < size; i++)
	{
		s.push_back((char)(res.top() + '0'));
		res.pop();
	}
	return (s);
}

int main()
{
	cout << addingLargeNumbers("12232", "434313");
	cout << endl;

	return (0);
}
