#include "intCircularSLList.h"
#include <iostream>
#include <cstddef>
#include <cassert>

using std::cout; using std::cin; using std::endl;

IntCircularSLList::~IntCircularSLList()
{
	if (head == nullptr)
		return;

	IntSLLNode *prev = head->next;
	for (; prev != head; prev = prev->next);
	prev->next = nullptr;

	IntSLLNode *p = nullptr;
	while(!isEmpty())
	{
		p = head->next;
		delete head;
		head = p;
	}
}

bool IntCircularSLList::isInList(int e) const
{
	if (head == nullptr)
		return (false);
	else if (head->info == e)
		return (true):
	for(auto p = head->next; p != head; p = p->next)
		if (p->info == e) return (true);
	return (false);
}

void IntCircularSLList::addToList(int e)
{
	IntSLLNode *n = new IntSLLNode(e);
	if (head != nullptr)
	{
		n->next = head->next;
		head->next = n;
	}
	else
	{
		n->next = n;
	}
	head = n;
}

int IntCircularSLList::deleteFromList(void)
{
	assert(head != nullptr);
	int e = 0;

	IntSLLNode *prev = head->next;
	for (; prev != head; prev = prev->next);

	if (prev == head)
	{
		head = nullptr;
		e = prev->info;
		delete prev;
	}
	else
	{
		head = head->next;
		e = prev->next->info;
		delete prev->next;
		prev->next = head;
	}

	return (e);
}

void IntCircularSLList::deleteNode(int e)
{
	assert(head != nullptr);

	IntSLLNode *curr = head;
	IntSLLNode *prev = head;
	for (curr = head->next; curr != head; curr = curr->next, prev = prev->next)
		if (curr->info == e) break;
	if (curr->info == e)
	{
		prev->next = curr->next;
		head = curr->next;
		delete curr;
	}
}

int main(void)
{
	auto lt = new IntCircularSLList();

	show(lt);
	for (int i = 0; i < 8; i++) lt->addToList(i);
	show(lt);
	lt->addToList(9); show(lt);

	delete lt;

	return (EXIT_SUCCESS);
}
