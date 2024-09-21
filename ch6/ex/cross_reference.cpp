#include "cross_reference.h"

int main(void)
{
	BinarySearchTree *t = new BinarySearchTree();
	string filename = "test.txt";

	processFile(filename, t);

	std::cout << "Words and their respective line numbers:\n";
	t->inOrderPrint();
	delete t;

	return (EXIT_SUCCESS);
}
