#include <fstream>
#include <cstring>
#include <cctype>
#include "genSplay.h"

using namespace std;

class Word
{
	public:
		char *word;
		int freq;

	public:
		Word(): freq(1) {}
		
		int operator==(const Word &ir) const
		{
			return (strcmp(word, ir.word) == 0);
		}
		int operator<(const Word &ir) const
		{
			return (strcmp(word, ir.word) < 0);
		}

	private:
		friend class wordSplay;
		friend ostream &operator<<(ostream &, const Word &);
};

class WordSplay : public SplayTree<Word>
{
	int differentWords;
	int wordCount;

	public:
		WordSplay(): differentWords(0), wordCount(0) {}

		void run(ifstream &, char *);

	private:
		void visit(SplayingNode<Word> *p);
};

void WordSplay::run(ifstream &fIn, char *fileName)
{
	char ch = ' ', i;
	char s[100];
	Word rec;

	while (fIn.eof())
	{
		while (true)
		{
			if (!fIn.eof() && !isalpha(ch))
				fIn.get(ch);
			else
				break;
		}
		if(fIn.eof())
			break;

		for (i = 0; !fIn.eof() && isalpha(ch); i++)
		{
			s[(int)i] = toupper(ch);
			fIn.get(ch);
		}
		s[(int)i] = '\0';

		rec.word = new char[strlen(s) + 1];
		if (rec.word == nullptr)
		{
			cerr << "no room for new words.\n";
			exit(1);
		}

		strcpy(rec.word, s);
		Word *p = search(rec);
		if (p == nullptr)
			insert(rec);
		else
			(p->freq)++;
	}

	inorder();
	cout << "\n\nFile " << fileName
		<< " contains " << wordCount << " words among which "
		<< differentWords << " are different\n";
}

void WordSplay::visit(SplayingNode<Word> *p)
{
	differentWords++;
	wordCount += p->info.freq;
}


int main(int argc, char **argv)
{
	char fileName[80];
	WordSplay splayTree;

	if (argc != 2)
	{
		cout << "Enter a file name: ";
		cin >> fileName;
	}
	else
		strcpy(fileName, argv[1]);

	ifstream fIn(fileName);
	if (fIn.fail())
	{
		cerr << "Cannot open " << fileName << endl;
		return (EXIT_FAILURE);
	}

	splayTree.run(fIn, fileName);
	fIn.close();

	return (EXIT_SUCCESS);
}
