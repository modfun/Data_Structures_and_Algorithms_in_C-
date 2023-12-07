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
};

#endif
