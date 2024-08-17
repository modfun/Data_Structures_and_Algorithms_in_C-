#include "genBST.h"

template<class T>
void BST<T>::clear(BSTNode<T> *p)
{
	if (p == nullptr)
		return;
	clear(p->left);
	clear(p->right);
	delete p;
}

template<class T>
T* BST<T>::search(BSTNode<T> *p, const T &el) const
{
	while (p != nullptr)
	{
		if (el == p->el)
			return (&p->el);
		else if (el < p->el)
			p = p->left;
		else
			p = p->right;
	}

	return (nullptr);
}

template<class T>
void BST<T>::breadthFirst()
{
	Queue<BSTNode<T> *> queue;
	BSTNode<T> *p = root;
	
	if (p != nullptr)
	{
		queue.enqueue(p);
		while (!queue.empty())
		{
			p = queue.dequeue();
			visit(p);
			if (p->left != nullptr)
				queue.enqueue(p->left);
			if (p->right != nullptr)
				queue.enqueue(p->right);
		}
	}
}

template<class T>
void BST<T>::inorder(BSTNode<T> *p)
{
	if (p != 0)
	{
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}

template<class T>
void BST<T>::preorder(BSTNode<T> *p)
{
	if (p != 0)
	{
		visit(p);
		preorder(p->left);
		preorder(p->right);
	}
}

template<class T>
void BST<T>::postorder(BSTNode<T>* p)
{
	if (p != 0)
	{
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}

template<class T>
void BST<T>::iterativePostorder()
{
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root, *q = root;

	while (p != nullptr)
	{
		for ( ; p->left != nullptr; p = p->left)
			travStack.push(p);
		while (p->right == nullptr || p->right == q)
		{
			visit(p);
			q = p;
			if (travStack.empty())
				return;
			p = travStack.pop();
		}
		travStack.push(p);
		p = p->right;
	}
}

template<class T>
void BST<T>::iterativeInorder()
{
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root;

	while (p != nullptr)
	{
		while (p != nullptr)
		{
			// stack the right child (if any)
			if (p->right)
				// and the node itself when going
				travStack.push(p->right); // to the left;
			travStack.push(p);
			p = p->left;
		}

		p = travStack.pop();
		// pop a node with no left child
		while (!travStack.empty() && p->right == nullptr)
		{ // visit it
			visit(p);
			// and all nodes with no right
			p = travStack.pop(); // child;
		}

		visit(p);
		// visit also the first node with
		if (!travStack.empty()) // a right child (if any);
			p = travStack.pop();
		else p = nullptr;
	}
}

template<class T>
void BST<T>::MorrisInorder()
{
	BSTNode<T> *p = root, *tmp;
	while (p != nullptr)
	{
		if (p->left == nullptr)
		{
			visit(p);
			p = p->right;
		}
		else
		{
			tmp = p->left;
			while (tmp->right != nullptr && tmp->right != p)
			// go to the rightmost node
			// of the left subtree or
			tmp = tmp->right;
			// to the temporary parent

			if (tmp->right == nullptr)
			{
				// of p; if 'true'
				tmp->right = p;
				// rightmost node was
				p = p->left;
				// reached, make it a
			}
			// temporary parent of the
			else
			{
				// current root, else
				// a temporary parent has
				visit(p);
				// been found; visit node p
				tmp->right = nullptr;
				// and then cut the right
				// pointer of the current
				p = p->right;
				// parent, whereby it
			}
		// ceases to be a parent;
		}
	}
}

template<class T>
void BST<T>::MorrisPreorder()
{
	BSTNode<T> *p = root, *tmp;
	while (p != nullptr)
	{
		if (p->left == nullptr)
		{
			visit(p);
			p = p->right;
		}
		else
		{
			tmp = p->left;
			while (tmp->right != nullptr && tmp->right != p)
			// go to the rightmost node
			// of the left subtree or
			tmp = tmp->right;
			// to the temporary parent

			if (tmp->right == nullptr)
			{
				visit(p); /* visit p moved from else to if clause */
				// of p; if 'true'
				tmp->right = p;
				// rightmost node was
				p = p->left;
				// reached, make it a
			}
			// temporary parent of the
			else
			{
				// current root, else
				// a temporary parent has
				// been found;
				tmp->right = nullptr;
				// and then cut the right
				// pointer of the current
				p = p->right;
				// parent, whereby it
			}
		// ceases to be a parent;
		}
	}
}

template<class T>
void BST<T>::insert(const T& el) {
	BSTNode<T> *p = root, *prev = nullptr;
	while (p != nullptr)
	{ // find a place for inserting new node;
		prev = p;
		if (el < p->el)
			p = p->left;
		else
			p = p->right;
	}
	if (root == nullptr)
		// tree is empty;
		root = new BSTNode<T>(el);
	else if (el < prev->el)
		prev->left = new BSTNode<T>(el);
	else
		prev->right = new BSTNode<T>(el);
}

template<class T>
void BST<T>::balance(T data[], int first, int last)
{
	if (first <= last)
	{
		int middle = (first + last)/2;
		insert(data[middle]);
		balance (data,first,middle-1);
		balance (data,middle+1,last);
	}
}

template<class T>
int BST<T>::countNodes(BSTNode<T> *p) // for all BT
{
	if (p == nullptr)
		return (0);
	else
		return (1 + countNodes(p->left) + (p->right));
}

template<class T>
int BST<T>::findHeight(BSTNode<T> *p) // for all BT
{
	int rheight, lheight, max;

	if (p == nullptr)
		return (-1);
	else
	{
		rheight = findHeight(p->right);
		lheight = findHeight(p->left);
		if (rheight > lheight) max = rheight;
		else max = lheight;
	}

	return (1 + max);
}

template<class T>
bool BST<T>::isPerfectlyBalanced() // for all BT
{
	if (root == nullptr)
		return (true);
	else
	{
		Queue<BSTNode<T> *> q;
		q.enqueue(root);
		bool reachedEnd = false;

		while (!q.empty())
		{
			auto node = q.dequeue();

			if (node->left != nullptr)
			{
				if (reachedEnd) return (false);
				q.enqueue(node->left);
			}
			else
				reachedEnd = true;
			if (node->right != nullptr)
			{
				if (reachedEnd) return (false);
				q.enqueue(node->right );
			}
			else
				reachedEnd = true;
		}

		return (true);
	}
}

template<class T>
bool BST<T>::isBST(BSTNode<T> *p, BSTNode<T> *gp)
{
	if (p == nullptr)
		return (true);
	return (isBST(p->left, p) && isBSTNode(p, gp) && isBST(p->right, p));
}

template<class T>
bool BST<T>::isBSTNode(BSTNode<T> *p, BSTNode<T> *gp)
{
	int l, r;

	if (p == nullptr)
		return (true);
	else
	{
		l = 0, r = p->el;

		if (p->left != nullptr)
			l = p->left->el;
		if (p->right != nullptr)
			r = p->right->el;

		if (gp != nullptr)
			return (l <= p->el && p->el <= r && r <= gp->el);
		else
			return (l <= p->el && p->el <= r);
	}
}

template<class T>
void BST<T>::printTree()
{
	if (root == nullptr)
	{
		std::cout << "Tree is empty." << std::endl;
		return;
	}

	std::queue<BSTNode<T>*> queue;
	queue.push(root);

	while (!queue.empty())
	{
		int levelSize = queue.size(); // Number of nodes at the current level

		for (int i = 0; i < levelSize; i++)
		{
			BSTNode<T>* current = queue.front();
			queue.pop();
			std::cout << current->el << " ";

			if (current->left != nullptr)
				queue.push(current->left);
			if (current->right != nullptr)
				queue.push(current->right);
		}
		std::cout << std::endl; // Move to the next line after printing each level
	}
}

using std::cout; using std::cin; using std::endl;

int main(void)
{
	BST<char> t;
	char data[26];

	for (int i = 0; i < 26; i++) data[i] = 'a' + i;

	t.balance(data, 0, 25);
	t.breadthFirst();
	cout << endl;
	t.inorder();
	cout << endl;
	t.printTree();
}
