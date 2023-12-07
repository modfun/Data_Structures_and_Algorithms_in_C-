class classf
{
	public:
		classf() {}
		double operator()(double x)
		{
			return (2 * x);
		}
};

double sum(classf f, int n, int m)
{
	double result = 0;
	for (int i = n; i <= m; i++)
		result += i;
	return (result);
}

#include <functional>
using std::negate;
/**
 * template<class T>
 * struct negate : public unary_function<T, T>
 * {
 * 	T operator()(const T& x) const
 * 	{
 * 		return (-x);
 * 	}
 * };
 */

template<class F>
double sum(F f, int n, int m)
{
	int res = 0;
	for (int i = n; i <= m; ++i)
		res += i;
	return (res);
}

int main()
{
	std::cout << sum(classf(), 2, 5) << std::endl;
	std::cout << sum(negate<double>(), 3, 5) << std::endl;
}
