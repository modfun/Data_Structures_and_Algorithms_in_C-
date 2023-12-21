#ifndef DISK_MANAG_H
#define DISK_MANAG_H

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using std::string; using std::list;

struct Block
{
	int begin;
	int end;
	Block *next;

	public:
		Block(int b, int e, Block *n = nullptr):
			begin(b), end(e), next(n) {}
		Block()
		{
			Block(0, 0);
		}

		int getSize() const { return (end - begin + 1);}
};

class File
{
	string name;
	int size;

	public:
		Block *content;
		File *next;

	public:
		File(string n, int s, File *p = nullptr):
			name(n), size(s), content(nullptr), next(p) {}
		File(string n)
		{
			File(n, 0);
		}
		~File();

		int getSize() const { return (size);}
		const string &getName() const { return (name);}
		void info() const;
};

class Disk
{
	const static int numOfSectors = 128;
	const static int sizeOfSector = 16;
	int freeSectors;
	char disk[numOfSectors * sizeOfSector];
	Block *pool;
	File *files;

	private:
		Block *claim(int);
		void declaim(Block *);
		void addToFiles(File *);
		void printBlock(Block *) const;

	public:
		Disk();
		~Disk();

		bool saveFile(File *);
		bool deleteFile(File *);
		bool writeToFile(File *, const string &);
		void printFile(File *) const;

		int getSize() const { return (numOfSectors * sizeOfSector);}
		int getFreeSectors() const { return (freeSectors);}
		void info(void) const;
};

#endif
