#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

template<class T>
void printVector(char *s, const vector<T> &v)
{
	cout << s << " = (";
	if (v.size() == 0)
	{
		cout << ")\n";
		return;
	}
	
	typename vector<T>::const_iterator i = v.begin();
	for (; i != v.end() - 1; ++i)
		cout << *i << ' ';
	cout << *i << ")\n";
}

bool f1(int n)
{
	return (n < 4);
}

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	vector<int> v1;

	printVector("v1", v1);
	for (int j = 1; j <= 5; ++j)
	{
		v1.push_back(j);
	}

	vector<int> v2(3, 7);

	vector<int> ::iterator il = v1.begin() + 1;
	vector<int> v3(il, il + 2);

	vector<int> v4(v1);
	
	vector<int> v5(5);
	v5[1] = v5.at(3) = 9;

	replace_if(v5.begin(), v5.end(), bind2nd(less<int>(), 4), 7);

	return (0);
}
