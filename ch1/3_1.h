#ifndef T3_1
#define T3_1

#include <iostream>

class BaseClass
{
	public:
		BaseClass() {}

		void f(char *s = "unknown")
		{
			std::cout << "Function f() in BaseClass called from "
				<< s << std::endl;
			h();
		}
	protected:
		void g(char *s = "unknown")
		{
			std::cout << "Function g() in BaseClass called from "
				<< s << std::endl;
		}
	private:
		void h()
		{
			std::cout << "Function h() in BaseClass\n";
		}
};

class Derived1Level1 : public virtual BaseClass
{
	public:
		void f(char *s = "unknown")
		{
			std::cout << "Function f() in Derived1Level1 called from "
				<< s << std::endl;
			g("Derived1Level1");
			h("Derived1Level1");
		}
		void h(char *s = "unknown")
		{
			std::cout << "Function h() in Derived1Level1 called from "
				<< s << std::endl;
		}
};

class Derived2Level1 : public virtual BaseClass
{
	public:
		void f(char *s = "unknown")
		{
			std::cout << "Function f() in Derived2Level1 called from "
				<< s << std::endl;
			g("Derived2Level1");
			h();	// Error
		}
};

class DerivedLevel2 : public Derived1Level1, public Derived2Level1
{
	void f(char *s = "unknown")
	{
			std::cout << "Function f() in DerivedLevel2 called from "
				<< s << std::endl;
			g("DerivedLevel2");
			Derived1Level1::h("DerivedLevel2");
			BaseClass::f("DerivedLevel2");
	}
};

#endif
