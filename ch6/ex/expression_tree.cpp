#include "expression_tree.h"
#include <iostream>

using namespace std;

int main(void)
{
	ExpressionTree *t = new ExpressionTree("- * x x 5");
	auto result = t->differentiate();
	cout << result << endl;

	if (t != nullptr)
		delete t;

	return (EXIT_SUCCESS);
}
