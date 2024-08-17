#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <cstdlib>
#include <iostream>

const int MAXLEVEL = 4;

template <class T>
struct SkipListNode
{
	T key;
	SkipListNode **next;

	public:
		SkipListNode() {}
		/* ~SkipListNode(); */
};

template <class T>
class SkipList
{
	typedef SkipListNode<T> *nodePtr;
	nodePtr root[MAXLEVEL];
	int powers[MAXLEVEL];

	public:
		SkipList();
		/* ~SkipList(); */

		bool isEmpty() const;
		void choosePowers();
		int chooseLevels() const;
		T *search(const T &) const;
		void insert(const T &);
		void remove(const T &);
};

#endif
