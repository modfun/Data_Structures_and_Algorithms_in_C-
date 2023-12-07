#include <iostream>
#include <cstring>

class C
{
	public:
		C(char *s = "", int i = 0, double d = 1):
			dataMember2(i), dataMember3(d)
		{
			std::strcpy(dataMember1, s);
		}
		void memberFunction1()
		{
			std::cout << dataMember1 << " "
				<< dataMember2 << " "
				<< dataMember3 << std::endl;
		}
		void memberFunction2(int i, char *s = "unknown")
		{
			memberFunction2 = i;
			std::cout << i << " received from " << s
				<< std::endl;
		}

	protected:
		char *dataMember1[20];
		int dataMember2;
		double dataMember3;
}

int main()
{
	C object1("object1", 1000, 2000);
	C object2("object2");
	C object3;
}
