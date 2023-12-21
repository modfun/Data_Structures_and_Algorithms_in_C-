#include "airline_reservation.h"

void Flight::reserve(string s)
{
	pl.push_back(s);
	pl.sort();
	size++;
}

bool Flight::cancel(string s)
{
	bool found;
	auto it = pl.begin();
	for (; it != pl.end(); it++)
	{
		if (*it == s) 
		{
			pl.erase(it);
			size--;
			found = true;
			break;
		}
	}

	return (found);
}

bool Flight::check(string s) const
{
	for (auto &e : pl)
		if (s == e) return (true);

	return (false);
}

void Flight::display() const
{
	cout << "Flight: " << code << ", NOP: " << size << endl;
	cout << "Passengers:\n";
	for (auto &e : pl)
	{
		cout << "\t\t" << e << ".\n";
	}
	cout << endl;
}

Airline::~Airline()
{
	for (auto &e : fl)
		delete e;
}

Flight *Airline::getFlight(int c) const
{
	for (auto &e : fl)
		if (e->getCode() == c) return (e);
	return (nullptr);
}

void Airline::addFlight(Flight *f)
{
	fl.push_back(f);
	size++;
}

bool Airline::endFlight(Flight *f)
{
	bool found;
	auto it = fl.begin();
	for (; it != fl.end(); it++)
	{
		if (*it == f)
		{
			fl.erase(it);
			found = true;
		}
	}
	delete f;
	size--;

	return (found);
}

void Airline::display() const
{
	cout << "#####################################################\n";
	cout << "Airline " << name << " with " << size << " flight(s):\n";
	for (auto &e : fl)
		e->display();
	cout << "#####################################################\n";
}

void printOptions()
{
	cout << "================================================\n";
	cout << "(a) reserve a ticket (b) cancel a reservation\n" <<
		"(c) check a reservation for a person\n" <<
		"(d) display the passengers (e) Exit flight" << endl;
	cout << "================================================\n";
	cout << "Enter your choice: ";
}

void menu(Flight *passlist)
{
	cout << "this is flight (" << passlist->getCode() << ")\n";
	printOptions();

	char c;
	while (cin >> c)
	{
		string s;
		switch (c)
		{
			case 'a':
				cin.ignore();
				cout << "Enter the passenger name: ";
				std::getline(cin, s);
				passlist->reserve(s);
				cout << "[Added] " << s << endl;
				break;
			case 'b':
				cin.ignore();
				cout << "Enter the passenger name: ";
				std::getline(cin, s);
				cout << "[Status]: " << passlist->cancel(s)
					<< endl;
				break;
			case 'c':
				cin.ignore();
				cout << "Enter the passenger name: ";
				std::getline(cin, s);
				cout << "[status]: " << passlist->check(s)
					<< endl;
				break;
			case 'd':
				passlist->display();
				break;
			case 'e':
				return;
			default:
				cout << "Wrong Input." << endl;
		}
		printOptions();
	}
}

void run(Airline *al)
{
	cout << "Welcome to the Airline Reservation program!" << endl;
	cout << "Enter flight Code (or EOL to exit): ";
	int c;
	while (cin >> c)
	{
		Flight *f = al->getFlight(c);
		if (f != nullptr)
			menu(f);
		else
		{
			f = new Flight(c);
			al->addFlight(f);
			menu(f);
		}
		cout << "Enter flight Code (or EOL to exit): ";
	}
	cout << endl;
	al->display();
}

int main(void)
{
	Airline *egyptair = new Airline("Egypt Air");
	run(egyptair);
	delete egyptair;

	return (EXIT_SUCCESS);
}
