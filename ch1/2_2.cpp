#include <iostream>

/**
 * swap - generic function
 */
template<class genType>
void swap(genType &el1, genType&el2)
{
	genType tmp(el1);
	el1 = el2;
	el2 = tmp;
}

/**
 * main
 */
int main()
{
	int i = 5;
	int j = 4;
	char x = 'x';
	char y = 'y';

	swap(i, j);
	std::cout << i << " " << j << std::endl;
	swap(x, y);
	std::cout << x << " " << y << std::endl;

	return (0);
}
