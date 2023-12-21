#include "disk_management.h"

using std::cout; using std::endl;

Disk::Disk()
{
	freeSectors = numOfSectors;
	pool = new Block(0, numOfSectors - 1);
	files = nullptr;
}

Disk::~Disk()
{
	for (Block *it = pool; pool != nullptr;)
	{
		it = pool->next;
		delete pool;
		pool = it;
	}

	for (File *it = files; files != nullptr;)
	{
		it = files->next;
		delete files;
		files = it;
	}
}

File::~File()
{
	for (Block *it = content; content != nullptr;)
	{
		it = content->next;
		delete content;
		content = it;
	}
}

Block *Disk::claim(int bytes)
{
	cout << "DEBUG(claim-start)\n";
	int required = (bytes / sizeOfSector) + 1;
	if (pool == nullptr || freeSectors < required)
		return (nullptr);
	freeSectors -= required;

	Block *allocated = pool;
	Block *allocatedHead = allocated;

	while (required > 0 && pool != nullptr)
	{
		if (pool->getSize() > required)
		{
			if (allocated == pool)
			{
				allocated = new Block(pool->begin,
						pool->begin + required - 1);
				allocatedHead = allocated;
			}
			else
				allocated->next = new Block(pool->begin,
						pool->begin + required - 1);
			pool->begin = pool->begin + required;
			required = 0;
		}
		else if (pool->getSize() < required)
		{
			if (allocated == pool)
			{
				allocated = pool;
				pool = pool->next;
				allocated->next = nullptr;
				required -= allocated->getSize();
			}
			else
			{
				allocated->next = pool;
				pool = pool->next;
				allocated = allocated->next;
				allocated->next = nullptr;
			}
		}
		else
		{
			if (allocated == pool)
			{
				allocated = new Block(pool->begin,
						pool->begin + required - 1);
				allocatedHead = allocated;
			}
			else
				allocated->next = new Block(pool->begin,
						pool->begin + required - 1);
			pool = pool->next;
			required = 0;
		}
	}

	cout << "DEBUG(claim-end)\n";
	return (allocatedHead);
}

void Disk::addToFiles(File *f)
{
	cout << "DEBUG(addToFiles-start)\n";
	if (files == nullptr)
	{
		files = f;
		f->next = nullptr;
	}
	else
	{
		File *it = files;
		cout <<"Debug\n";
		for (; it->next != nullptr; it = it->next);
		it->next = f;
		f->next = nullptr;
	}
	cout << "DEBUG(addToFiles-end)\n";
}

bool Disk::saveFile(File *f)
{
	cout << "DEBUG(saveFile-start)\n";
	if (f->getSize() == 0)
		return (false);

	f->content = claim(f->getSize());
	if (f->content == nullptr)
		return (false);

	addToFiles(f);
	cout << "DEBUG(saveFile-end)\n";
	return (true);
}

void Disk::declaim(Block *b)
{
	cout << "DEBUG(declaim-start)\n";
	if (b == nullptr)
		return;

	if (pool == nullptr)
		pool = b;
	else
	{
		auto tmp = pool;
		auto it = b;
		for (; it->next != nullptr; it = it->next);
		pool = b;
		it->next = tmp;
	}
		cout << "DEBUG(declaim-end)\n";
}

bool Disk::deleteFile(File *f)
{
	cout << "DEBUG(deleteFile-start)\n";
	if (files == nullptr || f == nullptr)
		return (false);

	auto it = files;
	auto prev = files;
	if (f == files)
	{
		files = f->next;
		declaim(f->content);
		freeSectors += (f->getSize() / sizeOfSector) + 1;
		f->content = nullptr;
		return (true);
	}
	else
	{
		for (; it->next != nullptr; it = it->next)
		{
			if (it == f)
			{
				prev->next = f->next;
				declaim(f->content);
				freeSectors += (f->getSize() / sizeOfSector) + 1;
				f->content = nullptr;
			}
			prev = it;
		}
	}
	if (it == nullptr && prev != f)
		return (false);

	cout << "DEBUG(deleteFile-end)\n";
	return (true);
}

void File::info(void) const
{
	cout << "----------------" << endl;
	cout << "file: " << getName() << endl;
	cout << "\tSize: " << getSize() << endl;

	cout << "\tBlocks: ";
	auto it = content;
	for (; it ->next != nullptr; it = it->next)
	{
		cout << "[" << it->begin << ":"
			<< it->end << "] ";
	}
	cout << "[" << it->begin << ":"
		<< it->end << "] " << endl;
}

void Disk::info(void) const
{
	int cnt = 0;
	if (files != nullptr)
	{
		auto it = files;
		for (; it->next != nullptr; it = it->next)
		{
			it->info();
			cnt++;
		}
		it->info();
		cnt++;
	}
	else
	{
		cout << "----------------" << endl;
		cout << "no files." << endl;
	}
	cout << "================" << endl;
	cout << "No of Files: " << cnt << endl;
	cout << "Disk Size: " << getSize() 
		<< ", Used: " << getSize() - (getFreeSectors() * sizeOfSector)
		<< ", Free: " << getFreeSectors() * sizeOfSector << endl;
	cout << "Total Sectors: " << numOfSectors
		<< ", Free Sectors: " << getFreeSectors() << endl;
	cout << "================" << endl;
}

bool Disk::writeToFile(File *f, const string &s)
{
	if (f->content == nullptr)
		return (false);
	if (static_cast<unsigned int>(f->getSize()) != s.length())
		cout << "WARNING" << f->getSize() << ":" << s.length() << endl;

	auto it = f->content;
	unsigned int i = 0;
	for (; it->next != nullptr; it = it->next)
	{
		for (int j = it->begin; j <= it->end; j++)
			for (int k = 0; k < sizeOfSector; k++)
				disk[j * sizeOfSector + k] = s[i++];
	}
	for (int j = it->begin; j <= it->end; j++)
		for (int k = 0; k < sizeOfSector; k++)
			if (i < s.length())
				disk[j * sizeOfSector + k] = s[i++];
			else
				disk[j * sizeOfSector + k] = '\0';

	return (true);
}

void Disk::printBlock(Block *b) const
{
	for (int i = b->begin; i <= b->end; i++)
		for (int k = 0; k < sizeOfSector; k++)
			cout << disk[i * sizeOfSector + k];
}

void Disk::printFile(File *f) const
{
	if (f->content == nullptr)
		return;

	cout << "****************" << endl;
	cout << "File: " << f->getName() << ", Size: " << f->getSize() << endl;
	auto it = f->content;
	for (; it->next != nullptr; it = it->next)
		printBlock(it);
	printBlock(it);
	cout << endl;
	cout << "****************" << endl;
}

/*==============================================================================
	Testing
==============================================================================*/

void freeBlock(Block *b)
{
	for (Block *it = b; b != nullptr;)
	{
		it = b->next;
		delete b;
		b = it;
	}
}

int main(void)
{
	Disk diskOne;
	File *f1 = new File("myFile", 12);
	File *f2 = new File("abc", 18);
	File *f3 = new File("newone", 14);
	File *f4 = new File("non", 16);

	diskOne.saveFile(f1);
	diskOne.saveFile(f2);
	diskOne.saveFile(f3);
	diskOne.saveFile(f4);
	diskOne.info();

	diskOne.deleteFile(f3);
	f3 = new File("dtot", 42);
	diskOne.saveFile(f3);
	diskOne.info();

	diskOne.writeToFile(f1, "hello World!");
	diskOne.printFile(f1);
	diskOne.writeToFile(f3, "this is some file for testing this program");
	diskOne.printFile(f3);

	// ~File() is called deleting the files.
	return (0);
}
