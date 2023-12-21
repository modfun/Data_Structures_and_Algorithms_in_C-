#ifndef EDIT_LINE_H
#define EDIT_LINE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>

using std::string; using std::vector; using std::list;
using std::fstream; using std::istringstream;
using std::cout; using std::cin; using std::endl; using std::getline;
typedef istringstream iss;

class Text
{
	list<string> lines;
	string fname;
	fstream file;

	public:
		Text(string str);
		~Text();
		string getName() const { return (fname);}
		unsigned int size() const;
		bool is_open() const { return (file.is_open());}

		void insert(string, unsigned int);
		void del(unsigned int, unsigned int);
		void lis(unsigned int, unsigned int) const;
		void app(string &, unsigned int i);

		friend void load(Text &);
		friend void print(Text &);
};

void load(Text &t)
{
	string s;
	int i = 0;
	while (getline(t.file, s))
	{
		t.lines.push_back(s);
		i++;
	}
	cout << "[LOADED] " << t.fname << endl;
	/* print(t); */
}

void print(Text &t)
{
	for (auto &e : t.lines)
		cout << e << endl;
}

#endif
