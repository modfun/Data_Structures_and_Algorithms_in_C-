#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::cout;

int processRow(vector<vector<char>> &g, int r, int a, int b)
{
	int count = 0;
	int noncount = 0;
	int newA = 0;
	int newB = 0;
	int n = g[r].size();

	for (int i = a; i <= b; i++)
	{
		if (g[r][i] == 'w')
		{
			count++;
			g[r][i] = 'c';
			if (newA == 0) newA = i;
		}
		else
		{
			noncount++;
		}
	}

	if (count == 0)
		return (0);
	else newB = newA + count - 1;

	if (a == newA)
	{
		for (int i = a-1; i >= 0; i--)
		{
			if (g[r][i] == 'w')
			{
				count++;
				g[r][i] = 'c';
				newA = i;
			}
			else
				break;
		}
	}
	if (b == newB)
	{
		for (int i = b+1; i < n; i++)
		{
			if (g[r][i] == 'w')
			{
				count++;
				g[r][i] = 'c';
				newB = i;
			}
			else
				break;
		}
	}

	return (count + processRow(g, r-1, newA, newB)
			+ processRow(g, r, newA, newB)
			+ processRow(g, r+1, newA, newB));
}

vector<int> processGrid(vector<vector<char>> g)
{
	int count = 0;
	int a = 0;
	int b = 0;
	int n = g.size();
	vector<int> result;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (g[i][j] == 'w')
			{
				count++;
				if (a == 0) a = j;
			}
			else
			{
				if (a != 0) b = j-1;
				count = processRow(g, i, a, b);
				if (count != 0)
					result.push_back(count);
				count = a = b = 0;
			}
		}
	}

	return (result);
}

int main(void)
{
	// g must have a black boundary. Use 'b' and 'w'.
	// vector<vector<char>> board = {{'b', 'b', 'b', 'b'},
	// 				{'b', 'w', 'w', 'b'},
	// 				{'b', 'w', 'w', 'b'},
	// 				{'b', 'b', 'b', 'b'}};
	char b = 'b';
	char w = 'w';
	vector<vector<char>> board = {{b, b, b, b, b, b, b, b, b, b},
					{b, w, b, b, w, w, b, w, w, b},
					{b, b, b, b, b, w, b, w, w, b},
					{b, w, w, w, b, b, w, w, w, b},
					{b, w, b, w, b, w, w, b, b, b},
					{b, w, b, w, w, w, b, w, b, b},
					{b, w, b, b, b, b, w, w, w, b},
					{b, w, b, w, b, b, w, w, w, b},
					{b, w, b, w, b, b, w, w, w, b},
					{b, b, b, b, b, b, b, b, b, b}};
	vector<int> result = processGrid(board);

	// 5 white areas of 1, 3, 21, 10, and 2 cells.
	cout << result.size() << " white area(s) of ";
	for (auto &e : result) cout << e << ", ";
	cout << "\b\b" << " cells." << '\n';

	return (EXIT_SUCCESS);
}
