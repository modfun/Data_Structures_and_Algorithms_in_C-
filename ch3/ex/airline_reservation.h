#ifndef AIRLINE_RESERVE
#define AIRLINE_RESERVE

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector; using std::list;
using std::sort;

class Flight
{
	list<string> pl;
	int code;
	int size;

	public:
		Flight(int c): code(c) {}

		int getSize() const { return (size);}
		int getCode() const { return (code);}
		void reserve(string);
		bool cancel(string);
		bool check(string) const;
		void display() const;
};

class Airline
{
	list<Flight *> fl;
	string name;
	int size;

	public:
		Airline(string n): name(n) {}
		~Airline();

		int getSize() const { return (size);}
		Flight *getFlight(int) const;
		void addFlight(Flight *);
		bool endFlight(Flight *);
		void display() const;
};

#endif
