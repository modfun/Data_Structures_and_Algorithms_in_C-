#include "singly_linked_list.h"
#include <iostream>
#include <cstddef>

using std::cout; using std::cin; using std::endl;

IntSLList::~IntSLList()
{
	for(IntSLLNode *p; !isEmpty();)
	{
		p = head->next;
		delete head;
		head = p;
	}
}

void IntSLList::addToHead(int e)
{
	head = new IntSLLNode(e, head);
	if (tail == nullptr)
		tail = head;
}

void IntSLList::addToTail(int e)
{
	if (tail != nullptr)
	{
		tail->next = new IntSLLNode(e);
		tail = tail->next;
	}
	else
		head = tail = new IntSLLNode(e);
}

int IntSLList::deleteFromHead()
{
	int e = head->info;
	IntSLLNode *tmp = head;

	if (head == tail)
		head = tail = nullptr;
	else
		head = head->next;
	delete tmp;

	return (e);
}

int IntSLList::deleteFromTail()
{
	int e = tail->info;

	if (head == tail)
	{
		delete tail;
		head = tail = nullptr;
	}
	else
	{
		IntSLLNode *tmp;
		for (tmp = head; tmp->next != tail; tmp = tmp->next);
		delete tail;
		tail = tmp;
		tail->next = nullptr;
	}

	return (e);
}

void IntSLList::deleteNode(int e)
{
	if (head != nullptr)
	{
		if (head == tail && e == head->info)
		{
			delete head;
			head = tail = nullptr;
		}
		else if (e == head->info)
		{
			IntSLLNode *tmp = head->next;
			head = head->next;
			delete tmp;
		}
		else
		{
			IntSLLNode *tmp, *pred;

			for (pred = head, tmp = head->next;
				tmp != nullptr && tmp->info != e;
				pred = pred->next, tmp = tmp->next);

			if (tmp != nullptr)
			{
				pred->next = tmp->next;
				if (tmp == tail)
					tail = pred;
				delete tmp;
			}
		}
	}
}

bool IntSLList::isInList(int e) const
{
	IntSLLNode *tmp;
	for (tmp = head; tmp != nullptr && tmp->info != e; tmp = tmp->next);
	return (tmp != 0);
}

bool IntSLList::isEqual(const IntSLList &list) const
{
	auto p1 = head;
	auto p2 = list.head;

	while(p1 != nullptr && p2 != nullptr)
	{
		if ((p1->info) != (p2->info)) return (false);
		cout << "[DEB] " << p1->info << ", "
			<< p2->info << ".\n";
		p1 = p1->next;
		p2 = p2->next;
	}

	if (p1 != p2)
		return (false);
	return (true);
}

int main()
{
	IntSLLNode *p = new IntSLLNode(10);
	p->next = new IntSLLNode(8);
	p->next->next = new IntSLLNode(50);

	IntSLList *lt = new IntSLList();
	IntSLList *lt2 = new IntSLList();
	cout << "?:" << lt->isEqual(*lt) << "\n";
	lt->addToHead(5);
	cout << "?:" << lt->isEqual(*lt) << "\n";
	cout << "?:" << lt->isEqual(*lt2) << "\n";
	cout << endl;

	cout << p->info << "\n";

	return (EXIT_SUCCESS);
}
