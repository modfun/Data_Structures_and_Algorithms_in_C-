#ifndef FAREY
#define FAREY

#include <iostream>
#include <list>
#include <algorithm>
#include <cstddef>

using std::list;
using std::cout; using std::cin; using std::endl;
typedef struct Fraction Fraction;

struct Fraction
{
	int nom;
	int den;

	Fraction(int a, int b): nom(a), den(b) {}
	void print(void)
	{
		cout << "(" << nom << "/" << den << ")";
	}
};

class Farey
{
	int level;
	list<Fraction> l;

	public:
		Farey(): level(1)
		{
			l.push_front(Fraction(0, 1));
			l.push_back(Fraction(1, 1));
		}
		Farey(int n)
		{
			Farey();
			if (n > 1) raiseTo(n);
		}

		int getLevel(void) const { return (level);}
		int addLevel(void);
		void raiseTo(int);

		friend void show(Farey);
};

void show(Farey f)
{
	cout << "{";
	for (auto &e : f.l)
	{
		e.print();
		cout << ", ";
	}
	cout << "\b }" << endl;
}

#endif
