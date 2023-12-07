#include "farey.h"

int Farey::addLevel(void)
{
	auto it = l.begin();
	auto end = l.end();
	end--;
	level++;
	while (it != end)
	{
		int x = it->nom;
		int y = it->den;
		std::advance(it, 1);
		Fraction f(x + (it->nom), y + (it->den));
		if (f.den <= level)
			l.insert(it, f);
	}

	return (level);
}

void Farey::raiseTo(int n)
{
	int i = n - level;
	while(i > 0)
	{
		addLevel();
		i--;
	}
}

int main(void)
{
	Farey f, q;
	show(f);
	
	cout << f.addLevel() << endl;
	show(f);

	cout << f.addLevel() << endl;
	show(f);

	cout << f.addLevel() << endl;
	show(f);

	f.raiseTo(9);
	show(f);

	cout << "n=4,\n";
	q.raiseTo(4);
	show(q);

	return (EXIT_SUCCESS);
}
