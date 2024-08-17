#include "skip_list.h"

using std::cout; using std::cin; using std::endl; using std::getline;

template <class T>
SkipList<T>::SkipList(void)
{
	for (int i = 0; i < MAXLEVEL; i++)
		root[i] = nullptr;
	choosePowers();
}

template <class T>
bool SkipList<T>::isEmpty(void) const
{
	bool b = root[0] == nullptr;
	return (b);
}

template <class T>
void SkipList<T>::choosePowers(void)
{
	powers[MAXLEVEL - 1] = (2 << (MAXLEVEL - 1)) - 1;	//(2^MAXLEVEL)-1
	for (int i = MAXLEVEL - 2, j = 0; i >= 0; i--, j++)
		powers[i] = powers[i + 1] - (2 << j);		//- 2^(j+1)
}

template <class T>
int SkipList<T>::chooseLevels(void) const
{
	int r = std::rand() % (powers[MAXLEVEL - 1] + 1);
	int i = 1;
	for (; i < MAXLEVEL; i++)
		if (r < powers[i])
			return (i - 1);
	return (i - 1);
}

template <class T>
T *SkipList<T>::search(const T &key) const
{
	if (isEmpty())
		return (nullptr);

	nodePtr prev, curr;
	int lvl;
	for (lvl = MAXLEVEL - 1;
		(lvl >= 0) && (root[lvl] == nullptr);
		lvl--);
	prev = curr = root[lvl];

	while (true)
	{
		if (key == curr->key)
		{
			return (&(curr->key));
		}
		else if (key < curr->key)
		{
			if (lvl == 0)
				return (nullptr);
			else if (curr == root[lvl])
				curr = root[--lvl];
			else
				curr = *(prev->next + --lvl);
		}
		else
		{
			prev = curr;
			if (*(curr->next + lvl) != nullptr)
				curr = *(curr->next + lvl);
			else
			{
				for (lvl--; lvl >= 0 
					&& *(curr->next + lvl) == nullptr;
					lvl--);
				if (lvl >= 0)
					curr = *(curr->next + lvl);
				else
					return (nullptr);
			}
		}
	}
}

template <class T>
void SkipList<T>::insert(const T &key)
{
	nodePtr curr[MAXLEVEL], prev[MAXLEVEL];
	nodePtr newNode;
	int lvl, i;
	curr[MAXLEVEL - 1] = root[MAXLEVEL - 1];
	prev[MAXLEVEL - 1] = nullptr;

	for (lvl = MAXLEVEL - 1; lvl >= 0; lvl--)
	{
		while ((curr[lvl] != nullptr) && (curr[lvl]->key < key))
		{
			prev[lvl] = curr[lvl];
			curr[lvl] = *(curr[lvl]->next + lvl);
		}
		if ((curr[lvl] != nullptr) && (curr[lvl]->key == key)) // unique L
			return;

		if (lvl > 0)
		{
			if (prev[lvl] == nullptr)
			{
				curr[lvl - 1] = root[lvl - 1];
				prev[lvl - 1] = nullptr;
			}
			else
			{
				curr[lvl - 1] = *(prev[lvl]->next + (lvl - 1));
				prev[lvl - 1] = prev[lvl];
			}
		}
	}

	int newlvl = chooseLevels();
	newNode = new SkipListNode<T>;
	newNode->next = new nodePtr[sizeof (nodePtr) * (newlvl + 1)];
	newNode->key = key;

	for (i = 0; i <= newlvl; i++)
	{
		*(newNode->next + i) = curr[i];
		if (prev[i] == nullptr)
			root[i] = newNode;
		else
			*(prev[i]->next + i) = newNode;
	}
}

template <class T>
void SkipList<T>::remove(const T &key)
{
	if (isEmpty())
		return;

	nodePtr prev, curr;
	int lvl;
	for (lvl = MAXLEVEL - 1;
		(lvl >= 0) && (root[lvl] == nullptr);
		lvl--);
	prev = curr = root[lvl];
	cout << prev->key << endl;

	while (true)
	{
		if (key == curr->key)
		{
			if (prev == curr)
			{
				for (int i = 0; i <= lvl; i++)
					root[i] = *(curr->next + i);
			}
			else
				prev->next = curr->next;
			cout << "[DEBUG] \n";
			cout << curr->key << endl;
			cout << prev->key << endl;
			delete curr;
			return;
		}
		else if (key < curr->key)
		{
			if (lvl == 0)
				return;
			else if (curr == root[lvl])
				curr = root[--lvl];
			else
				curr = *(prev->next + --lvl);
		}
		else
		{
			prev = curr;
			if (*(curr->next + lvl) != nullptr)
				curr = *(curr->next + lvl);
			else
			{
				for (lvl--; lvl >= 0 
					&& *(curr->next + lvl) == nullptr;
					lvl--);
				if (lvl >= 0)
					curr = *(curr->next + lvl);
				else
					return;
			}
		}
	}
}

int main(void)
{
	SkipList<int> sl;
	int j = 5;

	cout << sl.isEmpty() << endl;
	for (int i = 0; i < 64; i++) sl.insert(i);
	cout << sl.isEmpty() << "\n";
	cout << *sl.search(j) << "\n";
	cout << *sl.search(55) << "\n";
	sl.remove(j);
	cout << *sl.search(j) << "\n";

	return (EXIT_SUCCESS);
}
