#ifndef CONCORDANCE_H
#define CONCORDANCE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin; using std::cout; using std::endl; using std::getline;
using std::string; using std::vector; using std::ifstream; using std::ofstream;
using std::ostream; using std::istringstream;

struct Entry
{
	int poemNum;
	int lineNum;
	string word;
	string context;

	public:
		bool operator<(const struct Entry &) const;
};
typedef struct Entry E;

class Concordance
{
	vector<E> ledger;
	ifstream file;
	string fileName;

	public:
		Concordance() {}
		Concordance(string fn):
			fileName(fn)
		{
			file = ifstream(fileName);
		}

		string getFileName() const { return (fileName);}
		bool operator<(const Concordance &) const;

		friend Concordance &load(Concordance &c);
		friend vector<E> &reconstruct(const Concordance &, vector<E> &);

	protected:
		friend ostream &operator<<(ostream &, const Concordance &c);
		ostream &writeCord(ostream &) const;
};

Concordance &load(Concordance &c)
{
	if (!c.fileName.empty() && c.file.is_open())
	{
		string line;
		while (getline(c.file, line))
		{
			istringstream iss(line);
			E entry_tmp;

			iss >> entry_tmp.poemNum >> entry_tmp.lineNum;
			getline(iss, entry_tmp.context);

			string word_tmp;
			istringstream iss2(entry_tmp.context);
			while (iss2 >> word_tmp)
				if (word_tmp[0] == '*')
					entry_tmp.word = word_tmp;

			c.ledger.push_back(entry_tmp);
		}
	}
	c.file.close();

	return (c);
}

ostream &operator<<(ostream &out, const Concordance &c)
{
	return (c.writeCord(out));
}

vector<E> &reconstruct(const Concordance &c, vector<E> &v)
{
	for (auto e : c.ledger) v.push_back(e);
	std::sort(v.begin(), v.end());

	for (const auto &e : v)
	{
		cout << e.context << " ";
	}
	cout << std::endl;

	return (v);
}

#endif
