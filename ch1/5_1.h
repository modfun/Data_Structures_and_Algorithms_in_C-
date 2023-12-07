#include <iostream>

class class1
{
	public:
		virtual void f()
			std::cout << "Function f() in class1.\n";
		void g()
			std::cout << "Function g() in class2.\n";
};

class class2
{
	public:
		virtual void f()
			std::cout << "Function f() in class1.\n";
		void g()
			std::cout << "Function g() in class2.\n";
};

class class3
{
	public:
		virtual void h()
			std::cout << "Function h() in class3.\n";
};
