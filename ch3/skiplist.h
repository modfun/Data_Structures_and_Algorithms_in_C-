#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <cstdlib>

const int maxLevel = 4;

template<class T>
class SkipListNode
{
	public:
		T key;
		SkipListNode **next;

		SkipListNode() {}
};

template<class T>
class SkipList
{
	typedef SkipListNode<T> *nodePtr;
	nodePtr root[maxLevel];
	int powers[maxLevel];

	public:
		SkipList();
		bool isEmpty() const;
		void choosePowers();
		int  chooseLevel();
		T* skipListSearch(const T&);
		void skipListInsert(const T&);
};

#endif
