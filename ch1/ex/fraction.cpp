#include "fraction.h"

using std::cout; using std::endl;

bool Fraction::isReduced() const
{
	return
	(isReduced(this->getnum(), this->getden()));
}

bool Fraction::isReduced(const int &a, const int &b) const
{
	if (a > b || (gcd(a, b) != 1))
		return (false);
	return (true);
}

Fraction Fraction::operator+(const Fraction &a) const
{
	int tmpden = den * a.den;
	int tmpnum = num * a.den + den * a.num;
	Fraction tmp(tmpnum, tmpden);
	Fraction &tmpref = reduce(tmp);

	return (tmpref);
}

Fraction Fraction::operator-(const Fraction &a) const
{
	int tmpden = den * a.den;
	int tmpnum = num *a.den - den * a.num;
	Fraction tmp(tmpnum, tmpden);
	Fraction &tmpref = reduce(tmp);

	return (tmpref);
}

Fraction Fraction::operator*(const Fraction &a) const
{
	int tmpnum = num * a.num;
	int tmpden = den * a.den;
	Fraction tmp(tmpnum, tmpden);
	Fraction &tmpref = reduce(tmp);

	return (tmpref);
}

Fraction Fraction::operator/(const Fraction &a) const
{
	Fraction reciprocal(a.den, a.num);

	return (*this * reciprocal);
}

ostream &Fraction::writeFrac(ostream &out) const
{
	if (den != 1)
		out << num << "/" << den;
	else out << num;

	return (out);
}

istream &Fraction::readFrac(istream &in)
{
	cout << "Enter Numerator:";
	in >> num;
	cout << "Enter Denomninator:";
	in >> den;
	reduced = isReduced(num, den);
	
	return (in);
}

int gcd(int x, int y)
{
	while (x != y)
	{
		if (x > y) x = x - y;
		else y = y - x;
	}
	/* std::cout << "[DEBUG] " << x << " (gcd)\n"; */

	return (x);
}

int main()
{
	Fraction q(4, 6);
	Fraction k;

	cout << q << endl;
	cout << reduce(q) << endl;
	/* std::cin >> k; */
	cout << k << endl;
	cout << reduce(k) << endl;
	cout << q + k << endl;
	cout << Fraction(4, 5) - Fraction(1, 5) << endl;
	cout << Fraction(1, 2) * Fraction(2, 5) << endl;
	cout << Fraction(1, 2) / Fraction(1, 2) << endl;
	cout << Fraction(1, 3) / Fraction(2, 5) << endl;

	return (0);
}
