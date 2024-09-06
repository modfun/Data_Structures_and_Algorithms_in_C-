#include "BinaryTreeSorting.h"

using std::cout; using std::endl;

int main()
{
	/* vector<int> nums = {8, 3, 4, 2, 4, 0};
	vector<int> nums = {4, 9, 4, 6, 8, 3, 2, 8, 5, 6, 4, 8, 22}; */
	vector<int> nums = {44, 49, 43, 65, 8, 93, 27, 87, 5, 6, 4, 8, 22, 
		44, 49, 43, 65, 8, 95, 27, 87, 5, 6, 74, 58, 22, 13, 34, 65, 23};
	vector<int> *numsptr = &nums;

	/* BTree<int> t(numsptr, 23); */
	BTree<int> t(numsptr, 100);
	vector<int> *result = t.result;

	for (size_t i = 0; i < t.result->size(); i++)
		cout << i << ':' << (*result)[i] << '\n';

	return (EXIT_SUCCESS);
}
