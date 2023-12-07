#ifndef INTCIRCULARSLLIST_H
#define INTCIRCULARSLLIST_H

#include <iostream>

struct IntSLLNode
{
	int info;
	IntSLLNode *next;

	IntSLLNode(): next(nullptr) {}
	IntSLLNode(int e, IntSLLNode *ptr = nullptr):
		info(e), next(ptr) {}
};

class IntCircularSLList
{
	struct IntSLLNode *head;

	public:
		IntCircularSLList():
			head(nullptr) {}
		~IntCircularSLList();

		bool isEmpty() { return (head == nullptr);}
		bool isInList(int) const;

		void addToList(int);
		int deleteFromList(void);
		void deleteNode(int);

		friend void show(const IntCircularSLList *);
};

void show(const IntCircularSLList *list)
{
	if (list->head == nullptr)
		std::cout << "{[nil]}\n";
	else if (list->head == list->head->next)
		std::cout << "{[" << list->head->info << "]}\n";
	else
	{
		std::cout << "{";
		for (IntSLLNode *p = list->head->next; p != list->head; p = p->next)
			std::cout << "[" << p->info << "]-";
		std::cout << "[" << list->head->info << "]-";
		std::cout << "[NIL]}\n";
	}
}

#endif
