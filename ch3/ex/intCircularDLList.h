#ifndef INT_CIRCULAR_DLL
#define INT_CIRCULAR_DLL

#include <iostream>
using std::cout; using std::cin; using std::endl;

struct IntDLLNode
{
	int info;
	IntDLLNode *prev;
	IntDLLNode *next;

	IntDLLNode():
		prev(nullptr), next(nullptr) {}
	IntDLLNode(int e, IntDLLNode *p = nullptr, IntDLLNode *n = nullptr):
		info(e), prev(p), next(n) {}
};

class IntCircularDLList
{
	IntDLLNode *tail;

	public:
		IntCircularDLList():
			tail(nullptr) {}
		~IntCircularDLList();

		bool isEmpty() { return (tail == nullptr);}
		bool isInList(int) const;

		void addToList(int);
		int deleteFromList(void);
		void deleteNode(int);

		friend void show(const IntCircularDLList *);
};

void show(const IntCircularDLList *list)
{
	if (list->tail == nullptr)
		std::cout << "[NIL]\n";
	else if (list->tail == list->tail->next)
		std::cout << "-[" << list->tail->info << "]-\n";
	else
	{
		std::cout << "-";
		for (IntDLLNode *p = list->tail->next; p != list->tail; p = p->next)
			std::cout << "[" << p->info << "]-";
		std::cout << "[" << list->tail->info << "]-\n";
	}
}

#endif
