#include <iostream>
#include <vector>

using std::cout; using std::endl;
using std::vector;

int addNumbers(const int *start, const int *end);
int strlen(const char *s);
int strcmp(const char *s1, const char *s2);
const char *strchr(const char *s, char c);
char *strcat(char *dest, const char *src);

int main()
{
	int iarr[] = {1, 2, 3}, *p = iarr;
	char str1[32] = "his name is ";

	cout << addNumbers(p, iarr + 3)  << endl;
	cout << strlen("hello") << endl;
	cout << strcmp("aac", "aaab") << endl;
	cout << strcat(str1, "cat") << endl;
}

int addNumbers(const int *start, const int *end)
{
	int sum = 0;
	for (; start != end; )
		sum += *start++;

	return (sum);
}

vector<int> &rmOdds(int *start, int *end, vector<int> &v)
{
	for (; start != end; start++)
	{
		if (*start % 2 == 0)
			continue;
		v.push_back(*start);
	}
	return (v);
}

int strlen(const char *s)
{
	int cnt = 0;
	while (*s != '\0')
		cnt++, s++;
	return (cnt);
}
int strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 > *s2)
			return (1);
		if (*s2 > *s1)
			return (-1);
		s1++, s2++;
	}
	return (0);
}

const char *strchr(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (nullptr);
}

char *strcat(char *dest, const char *src)
{
	char *tmp = dest;

	while (*tmp != '\0') tmp++;
	while (*src != '\0') *tmp++ = *src++;

	return (dest);
}
