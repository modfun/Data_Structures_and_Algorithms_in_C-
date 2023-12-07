#include <iostream>
#include <string>
#include <iterator>
#include <cctype>
#include <vector>
#include <cstdlib>

using std::cout; using std::cin; using std::endl; using std::getline;
using std::string;
using std::vector;
using std::begin; using std::end;

int f(int);
int g(int);
int sum(int (*g)(int), int i, int n);

/**
 * main - Initial Procedure
 *
 * Description: The Entry point of the program.
 * Return: (0) success.
 */
int main()
{
	cout << sum(f, 1, 10) << endl;
	cout << sum(g, 1, 10) << endl;
	return (EXIT_SUCCESS);
}

int f(int n)
{
	return (n * (n + 1) / 2);
}

int g(int x)
{
	return (2 * x);
}

int sum(int (*g)(int), int i, int n)
{
	int tot;

	if (i > n) return (0);
	tot = 0;
	for (; i <= n; i++)
		tot += g(i);
	return (tot);
}
