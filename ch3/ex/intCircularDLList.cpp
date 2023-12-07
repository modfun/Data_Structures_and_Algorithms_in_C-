#include "intCircularDLList.h"
#include <cstddef>
#include <cassert>
#include <cstdlib>
#include <ctime>

IntCircularDLList::~IntCircularDLList()
{
	if (tail == nullptr)
		return;
	IntDLLNode *p = nullptr;
	tail->prev->next = nullptr;
	while(!isEmpty())
	{
		p = tail->next;
		delete tail;
		tail = p;
	}
}

bool IntCircularDLList::isInList(int e) const
{
	if (tail == nullptr) return (false);
	else if (tail->info == e) return (true);
	for (auto p = tail->next; p != tail; p = p->next)
		if (p->info == e) return (true);
	return (false);
}

void IntCircularDLList::addToList(int e)
{
	if (tail == nullptr)
	{
		IntDLLNode *n = new IntDLLNode(e);
		tail = n;
		tail->next = tail->prev = tail;
	}
	else
	{
		IntDLLNode *n = new IntDLLNode(e, tail, tail->next);
		tail->next->prev = n;
		tail->next = n;
		tail = n;
	}
}

int IntCircularDLList::deleteFromList(void)
{
	int e;
	assert(tail != nullptr);
	
	if (tail->next == tail)
	{
		e = tail->info;
		delete tail;
		tail = nullptr;
	}
	else
	{
		IntDLLNode *temp = tail->prev;
		tail->next->prev = tail->prev;
		tail->prev->next = tail->next;
		e = tail->info;
		delete tail;
		tail = temp;
	}
	return (e);
}

void IntCircularDLList::deleteNode(int e)
{
	assert(tail != nullptr);

	auto p = tail->next;
	for (; p != tail; p = p->next)
		if (p->info == e) break;
	if (p->info == e)
	{
		auto temp = p->prev;
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		tail = temp;
	}
}

/* int main(void)
{
	IntCircularDLList *lt = new IntCircularDLList();

	show(lt);
	std::srand(std::time(nullptr));
	for (int i = 0; i < 9; i++)
	{
		int x = std::rand() % 10;
		lt->addToList(x);
	}
	show(lt);
	cout << "(" << lt->isInList(9) << ")" << endl;
	lt->deleteNode(19);
	show(lt);
	lt->deleteNode(9);
	show(lt);

	lt->addToList(std::rand() % 10);
	show(lt);
	lt->deleteFromList();
	lt->deleteFromList();
	lt->deleteFromList();
	show(lt);
	lt->deleteFromList();
	show(lt);
	lt->addToList(std::rand() % 10);
	show(lt);
	lt->deleteFromList();
	show(lt);

	delete lt;

	return (EXIT_SUCCESS);
} */
