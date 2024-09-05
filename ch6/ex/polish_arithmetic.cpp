#include "polish_arithmetic.h"

using std::cout; using std::cin;

int main()
{
	cout << "Enter a prefix expression: ";
	string expression;
	getline(cin, expression);

	ExpressionTree *extree = new ExpressionTree(expression);
	int result = extree->evaluate();
	delete extree;

	cout << "result = " << result << '\n';

	return (EXIT_SUCCESS);
}
