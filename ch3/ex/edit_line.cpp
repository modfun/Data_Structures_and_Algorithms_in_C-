#include "edit_line.h"

Text::Text(string str)
{
	fname = str;
	file.open(fname, std::ios::in | std::ios::out);
	if (file.is_open())
		load(*this);
	else
	{
		file.close();
		file.open(fname, std::ios::out | std::ios::trunc);
		if (!file.is_open())
			std::cerr << "[ERROR] Failed to open file: " << str << endl;
	}
}

Text::~Text()
{
	/* file.clear();
	file.seekp(0); */

	file.close();
	file.open(fname, std::ios::out | std::ios::trunc);

	for (auto &e : lines)
		file << e << endl;
	if (!file.is_open())
		std::cerr << "[WARNING] file is not open.";

	/* file.flush(); */
	file.close();
	cout << "[CLOSED] " << fname << endl;
}

unsigned int Text::size() const
{
	auto it = lines.begin();
	auto end = lines.end();
	unsigned int cnt = 0;
	for (; it != end; it++) cnt++;

	return (cnt);
}

void Text::insert(string s, unsigned int i)
{
	auto it = lines.begin();
	std::advance(it, i);
	lines.insert(it, s);
}

void Text::del(unsigned int n, unsigned int m)
{
	auto start = lines.begin();
	std::advance(start, n);
	auto end = start;
	std::advance(end, m - n);

	lines.erase(start, end);
}

void Text::lis(unsigned int n, unsigned int m) const
{
	auto start = lines.begin();
	std::advance(start, n);
	auto end = start;
	std::advance(end, m-n);

	for (; start != end; start++)
		cout << *start << endl;
}

void Text::app(string &s, unsigned int i)
{
	auto it = lines.begin();
	std::advance(it, i - 1);
	*it = (*it) + s;
}

unsigned int getIValue(unsigned int &i, unsigned int n, unsigned int m)
{
	if (!(i < n || i >= m))
	{
		if (n == 0)
			i = 0;
		else
			i = n - 1;
	}
	else if (i >= m)
		i = i - (m - n);

	return (i);
}

void listCommand(Text &t, vector<string> &v)
{
	unsigned int n;
	unsigned int m;
	auto size = t.size();

	if (v.size() == 3)
	{
		n = std::stoul(v[1]) - 1;
		m = std::stoul(v[2]) - 1;
		if (n > size-1 || m < 1 || m > size)
		{
			cout << "[ERROR] out of bounds" << endl;
			return;
		}
		t.lis(n, m);
	}
	else if (v.size() == 2)
	{
		n = std::stoul(v[1]) - 1;
		m = n + 1;
		if (n > size-1)
		{
			cout << "[ERROR] out of bounds" << endl;
			return;
		}
		t.lis(n, m);
	}
	else
	{
		t.lis(0, size);
	}
}

void deleteCommand(Text &t, vector<string> &v, unsigned int &i)
{
	unsigned int n;
	unsigned int m;
	auto size = t.size();

	if (v.size() == 3)
	{
		n = std::stoul(v[1]) - 1;
		m = std::stoul(v[2]) - 1;
		if (n > size-1 || m < 1 || m > size)
		{
			cout << "[ERROR] out of bounds" << endl;
			return;
		}
		getIValue(i, n, m);
		t.del(n, m);
	}
	else if (v.size() == 2)
	{
		n = std::stoul(v[1]) - 1;
		m = n + 1;
		if (n > size-1)
		{
			cout << "[ERROR] out of bounds" << endl;
			return;
		}
		getIValue(i, n, m);
		t.del(n, m);
	}
	else
	{
		if (i <= size)
		{
			t.del(i - 1, i);
			i--;
		}
	}
}

void startEditor(string str)
{
	Text t(str);
	if (!t.is_open())
	{
		cout << "[ERROR] Failed to open file: " 
			<< str << endl;
		return;
	}

	unsigned int i = t.size() + 1;
	cout << i << "> ";
	while (getline(cin, str))
	{
		string tmp;
		iss buf(str);
		vector<string> v;
		while (buf >> tmp) v.push_back(tmp);

		if (v.size() == 0)
		{
			t.insert("", i++ - 1);
		}
		else if (v.size() < 4 && v[0].size() == 1)
		{
			string s;
			unsigned int x = 0;
			switch (v[0][0])
			{
				case 'I':
					if (v.size() > 1) x = std::stoul(v[1]);
					if (x > t.size()) x = t.size();
					if (x < 1) x = 1;
					i = x;
					break;
				case 'D':
					deleteCommand(t, v, i);
					break;
				case 'L':
					listCommand(t, v);
					break;
				case 'A':
					getline(cin, s);
					t.app(s, i);
					break;
				case 'E':
					return;
					break;
				default:
					t.insert(str, i++ - 1);
					break;
			}
		}
		else
		{
			t.insert(str, i++ - 1);
		}
		cout << i << "> ";
	}
}

void run()
{
	cout << "Welcome to the Advanced Line Editor!" << endl;
	cout << "Enter your command: " << endl;
	cout << "#> ";
	string str;

	while (getline(cin, str))
	{
		iss s(str);
		string command = ""; s >> command;
		string option = ""; s >> option;
		string more = ""; s >> more;

		if (command == "QUIT")
			break;
		else if (command == "" || option == "" || more != "")
			cout << "Wrong Input!" << endl;
		else if (command == "EDIT")
		{
			startEditor(option);
		}
		else if (command == "PRINT")
		{
			Text t(option);
			if (t.is_open())
				print(t);
			else
				cout << "[ERROR] Failed to open file: "
					<< option << endl;
		}
		else
			cout << "Incorrect command." << endl;

		cout << "#> ";
	}
	cout << "[DONE]" << endl;
}

int main(void)
{
	run();

	return (EXIT_SUCCESS);
}
