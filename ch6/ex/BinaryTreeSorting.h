#ifndef BINARYTREESORTING_H
#define BINARYTREESORTING_H

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>

using std::vector;

template <class T>
struct BTNode
{
	T value;
	BTNode<T> *left;
	BTNode<T> *right;

	BTNode(T v, BTNode<T> *l = nullptr, BTNode<T> *r = nullptr):
		value(v), left(l), right(r) {}
};

/* 
 * A Binary Sorting Tree
 */
template <class T>
class BTree
{
	BTNode<T> *root;
	int height;
	size_t size;
	T max;

	public:
		vector<T> *data;
		vector<T> *result;

	public:
		BTree(vector<T> *d, T m);
		~BTree()
		{
			deleteTree(root);
			delete result;
		}

	private:
		void init()
		{
			if (size == 0)
				return;

			root = initTree(root, 1);
		}
		BTNode<T> *initTree(BTNode<T> *, int);
		void sort();
		void setMin(BTNode<T> *);
		void print(BTNode<T> *, int);
		void deleteTree(BTNode<T> *);
};

template<class T>
BTree<T>::BTree(vector<T> *d, T m)
{
	data = d;
	root = nullptr;
	max = m;
	size = data->size();
	result = new vector<T>();

	if (size != 0)
	{
		height = (std::ceil(std::log2(size)) + 1);
		init();
		print(root, 1);
		sort();
	}
	else
		height = 0;
}

template <class T>
void BTree<T>::print(BTNode<T> *n, int level)
{
	if (n == nullptr)
		return;

	std::cout << '[' << level << ']';
	std::cout << n->value << '\n';
	print(n->left, ++level);
	print(n->right, level);
}

template <class T>
void BTree<T>::sort()
{
	if (root == nullptr)
		return;

	for (size_t i = 0; i < size; i++)
	{
		setMin(root);
		result->push_back(root->value);
		root->value = max;
	}
}

template <class T>
void BTree<T>::setMin(BTNode<T> *n)
{
	if (n->left == nullptr || n->right == nullptr)
		return;

	setMin(n->left);
	setMin(n->right);
	if (n->left->value < n->right->value)
	{
		if (n->left->value < n->value)
		{
			n->value = n->left->value;
			n->left->value = max;
		}
	}
	else
	{
		if (n->right->value < n->value)
		{
			n->value = n->right->value;
			n->right->value = max;
		}
	}
}

template <class T>
BTNode<T> *BTree<T>::initTree(BTNode<T> *n, int level)
{
	if (level < height)
	{
		n = new BTNode<T>(max);
		n->left = initTree(n->left, ++level);
		n->right = initTree(n->right, level);
	}
	else if (level == height)
	{
		auto val = max;
		if (data->size() != 0)
		{
			val = data->back();
			data->pop_back();
		}
		n = new BTNode<T>(val);
	}

	return (n);

}

template <class T>
void BTree<T>::deleteTree(BTNode<T> *n)
{
	if (n != nullptr)
	{
		deleteTree(n->left);
		deleteTree(n->right);
		delete n;
	}
}

#endif
