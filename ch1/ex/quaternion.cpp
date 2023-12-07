#include "quaternion.h"

Quaternion Quaternion::operator+(const Quaternion &q) const
{
	Quaternion tmp;
	tmp.a = a + q.a;
	tmp.b = b + q.b;
	tmp.c = c + q.c;
	tmp.d = d + q.d;

	return (tmp);
}

Quaternion Quaternion::operator*(const Quaternion &q) const
{
	Quaternion tmp;
	tmp.a = a * q.a - b * q.b - c * q.c - d * q.d;
	tmp.b = a * q.b + b * q.a + c * q.d - d * q.c;
	tmp.c = a * q.c + c * q.a + d * q.b - b * q.d;
	tmp.d = a * q.d + d * q.a + b * q.c - c * q.b;

	return (tmp);
}

ostream &Quaternion::writeQuat(ostream &out, const Quaternion &q) const
{
	out << "(" << q.getA() << ", "
		<< q.getB() << ", "
		<< q.getC() << ", "
		<< q.getD() << ")";

	return (out);
}

istream &Quaternion::readQuat(istream &in, Quaternion &q)
{
	int t1, t2, t3, t4;
	std::cout << "Enter the Numbers from a to d: ";
	std::cin >> t1 >> t2 >> t3 >> t4;
	q.a = t1, q.b = t2, q.c = t3, q.d = t4;

	return (in);
}

int main()
{
	Quaternion q(4, 5, 6, 7), k;

	std::cout << q << '\n';
	std::cout << Quaternion(1, 3, 3, 3) << std::endl;
	std::cin >> k;
	std::cout << k << '\n';
	std::cout << "(.): " << q * k << std::endl;
	std::cout << "(+): " << q + k << std::endl;

	return (0);
}
