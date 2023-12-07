#ifndef QUATERNION_T
#define QUATERNION_T

#include <iostream>

using std::ostream; using std::istream;

/**
 * class Quaternion - Quaternion numbers are quadruples of Real numbers.
 * @a: int associated with real part.
 * @b: int associated with complex part.
 * @c: int associated with j part.
 * @d: int associated with k part.
 *
 * Description: Defined by william Hamilton, are extension of the complex
 * numbers. Quaternions are quadruples of real numbers (a, b, c, d) =
 * a + bi + cj + dk, where 1 = (1,0,0,0), i = (0,1,0,0), j = (0,0,1,0),
 * k = (0,0,0,1). i^2 = j^2 = k^2 = -1. ij=k, jk=i, ki=j, ji=-k, kj=-i, ik=-j.
 */
class Quaternion
{
	private:
		int a, b, c, d;
	
	public:
		Quaternion(): a(0), b(0), c(0), d(0) {}
		Quaternion(int aa, int bb = 0, int cc = 0, int dd = 0):
			a(aa), b(bb), c(cc), d(dd) {}
		Quaternion(Quaternion &q):
			a(q.getA()), b(q.getB()), c(q.getC()), d(q.getD()) {}

		int getA() const {return (a);}
		int getB() const {return (b);}
		int getC() const {return (c);}
		int getD() const {return (d);}

		Quaternion operator+(const Quaternion &) const;
		Quaternion operator*(const Quaternion &) const;

	protected:
		friend ostream &operator<<(ostream &, const Quaternion &);
		friend istream &operator>>(istream &, Quaternion &);

		ostream &writeQuat(ostream &, const Quaternion &) const;
		istream &readQuat(istream &, Quaternion &);
};

ostream &operator<<(ostream &out, const Quaternion &q)
{
	return (q.writeQuat(out, q));
}

istream &operator>>(istream &in, Quaternion &q)
{
	return (q.readQuat(in, q));
}

#endif
