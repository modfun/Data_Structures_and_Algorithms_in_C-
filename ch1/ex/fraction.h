#ifndef FRACTION_T
#define FRACTION_T

#include <iostream>

using std::istream; using std::ostream;

int gcd(int, int);

class Fraction
{
	private:
		int num;
		int den;
		bool reduced;

	public:
		Fraction():
			num(0), den(1), reduced(true) {}
		Fraction(int n, int d = 1):
			num(n), den(d) 
		{
			reduced = isReduced(n, d);
		}
		Fraction(const Fraction &a):
			num(a.getnum()), den(a.getden()), reduced(a.isReduced())
		{}

		bool isReduced() const;
		bool isReduced(const int &, const int &) const;
		int getnum() const { return (num);}
		int getden() const { return (den);}

		Fraction operator+(const Fraction &) const;
		Fraction operator-(const Fraction &) const;
		Fraction operator*(const Fraction &) const;
		Fraction operator/(const Fraction &) const;

		friend Fraction &reduce(Fraction &);

	protected:
		friend ostream &operator<<(ostream &, const Fraction &);
		friend istream &operator>>(istream &, Fraction &);

		ostream &writeFrac(ostream &) const;
		istream &readFrac(istream &);
};

/* friends */
Fraction &reduce(Fraction &a)
{
	if (!a.reduced)
	{
		int factor = gcd(a.num, a.den);
		a.num = a.num / factor;
		a.den = a.den / factor;
	}
	
	return (a);
}

ostream &operator<<(ostream &out, const Fraction &a)
{
	return (a.writeFrac(out));
}

istream &operator>>(istream &in, Fraction &a)
{
	return (a.readFrac(in));
}

#endif
