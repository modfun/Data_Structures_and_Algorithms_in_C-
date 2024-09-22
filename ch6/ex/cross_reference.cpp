#include "cross_reference.h"

int main(void)
{
	BinarySearchTree *t = new BinarySearchTree();
	string filename1 = "test.txt";
	BinarySearchTree *r = new BinarySearchTree();
	string filename2 = "trial.txt";

	processFile(filename1, t);
	processFile(filename2, r);

	std::cout << "Words and their respective line numbers:\n";
	t->inOrderPrint();
	std::cout << "\n";
	std::cout << "Words and their respective line numbers:\n";
	r->inOrderPrint();
	std::cout << "\n";

	delete t;
	delete r;

	return (EXIT_SUCCESS);
}
