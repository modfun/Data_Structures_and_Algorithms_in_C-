#include "genADTStack.h"
#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;
using std::cout;

int main(void)
{
	Stack<int, vector<int>> s;

	s.push(4);
	s.push(5);
	cout << s.pop() << '\n';

	return (EXIT_SUCCESS);
}
