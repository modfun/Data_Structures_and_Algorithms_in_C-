#include <iostream>

using std::cout;

class genClass
{
	public:
		virtual void process1(char)
		{ cout << "gen p1\n";}
		virtual void process2(char)
		{ cout << "gen p2\n";}
};

class derivedClass : public genClass
{
	public:
		void process1(int)
		{ cout << "der p1\n";}
		int process2(char)
		{ cout << "der p2\n"; return 0;}
};

int main(void)
{
	genClass * objptr1 = &derivedClass;
	genClass * objptr2 = &derivedClass;

	objptr1->process1(1000);
	objptr2->process2('A');
}
