#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <list>
#include <algorithm>
#include <string>

using std::cout; using std::cin; using std::cerr; using std::endl;
using std::string; using std::list; using std::find;
using std::ostream;

class IdNode
{
	private:
		string id;
		double value;

		friend class Statement;
		friend ostream &operator<<(ostream &, const IdNode &);
	
	public:
		IdNode(string s = "", double e = 0.0): id(s), value(e) {}
		bool operator==(const IdNode &Node) const
		{
			return (Node.id == id);
		}
};

class Statement
{
	private:
		list<IdNode> idList;
		char ch;
		
		double factor();
		double term();
		double expression();
		void readId(string);
		void issueError(string s) 
		{
			cerr << s << endl;
			exit(1);
		}
		double findValue(string);
		void processNode(string, double);
		friend ostream &operator<<(ostream &, const Statement &);

	public:
		Statement() {}
		void getStatement();
};

ostream &operator<<(ostream &out, const IdNode &n)
{
	out << n.id << " = " << n.value << endl;
	return (out);
}

ostream &operator<<(ostream &out, const Statement &s)
{
	auto i = s.idList.begin();
	auto f = s.idList.end();
	for (; i != f; i++)
		out << *i;
	out << endl;
	return (out);
}

#endif
