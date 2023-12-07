#ifndef SINGLY
#define SINGLY

class IntSLLNode
{
	public:
		int info;
		IntSLLNode *next;
	public:
		IntSLLNode():
			next(nullptr) {}
		IntSLLNode(int i, IntSLLNode *in = nullptr):
			info(i), next(in) {}
};

class IntSLList
{
	private:
		IntSLLNode *head, *tail;
	public:
		IntSLList():
			head(nullptr), tail(nullptr) {}
		~IntSLList();

		int isEmpty() { return head == nullptr;}
		bool isInList(int) const;
		bool isEqual(const IntSLList &) const;

		void addToHead(int);
		void addToTail(int);
		int deleteFromHead();
		int deleteFromTail();
		void deleteNode(int);
		
		void show(void) const;

		friend IntSLList *reverse(IntSLList *);
};

IntSLList *reverse(IntSLList *list)
{
	if (list->head == list->tail)
		return (list);

	IntSLLNode *temp = list->head->next;
	IntSLLNode *prev = nullptr;
	IntSLLNode *curr = list->head;
	while (temp->next != nullptr)
	{
		curr->next = prev;
		prev = curr;
		curr = temp;
		temp = temp->next;
	}
	curr->next = prev;
	temp->next = curr;

	temp = list->head;
	list->head = list->tail;
	list->tail = temp;

	return (list);
}

#endif
