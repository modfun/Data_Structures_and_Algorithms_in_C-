#include "concordance.h"

bool E::operator<(const E &e) const
{
	return (this->poemNum < e.poemNum ||
		(this->poemNum == e.poemNum &&
		this->lineNum < e.lineNum));
}

ostream &Concordance::writeCord(ostream &out) const
{
	for (auto e : ledger)
	{
		out << e.poemNum << ":" << e.lineNum << ' '
			<< e.context << '\n';
	}

	return (out);
}

int main()
{
	Concordance conOne("con_file");
	vector<E> vec;

	load(conOne);
	cout << conOne;
	reconstruct(conOne, vec);

	return (0);
}
