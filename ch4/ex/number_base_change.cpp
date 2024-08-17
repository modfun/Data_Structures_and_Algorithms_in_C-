#include <stack>
#include <iostream>

using std::cout; using std::cin; using std::endl;
using std::stack;

int main(void)
{
	stack<int> s;
	int num = 400;
	int base = 3;
	int size = 0;

	while (num > 0)
	{
		s.push(num % base);
		num = num / base;
	}

	size = s.size();
	for (int i = 0; i < size; i++)
	{
		cout << s.top();
		s.pop();
	}
	cout << endl;

	return (EXIT_SUCCESS);
}
