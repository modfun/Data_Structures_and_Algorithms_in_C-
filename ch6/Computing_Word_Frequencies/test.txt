#ifndef GENSPLAY_H
#define GENSPLAY_H

#include <iostream>
#include <stdlib.h>

template<class T> class SplayTree;

template<class T>
class SplayingNode
{
	public:
		T info;
		SplayingNode<T> *left, *right, *parent;

	public:
		SplayingNode()
		{
			left = right = parent = nullptr;
		}
		SplayingNode(const T& e, SplayingNode *l, SplayingNode *r,
				SplayingNode *p): info(e), left(l), right(r), 
				parent(p) {}
};

template<class T>
class SplayTree
{
	protected:
		SplayingNode<T> *root;

	public:
		SplayTree():
			root(nullptr) {}
		~SplayTree()
		{
			destroyTree(root);
		}

		void inorder()
		{
			inorder(root);
		}
		T* search(const T&);
		void insert(const T&);

	protected:
		void rotateR(SplayingNode<T>*);
		void rotateL(SplayingNode<T>*);
		void continueRotation(SplayingNode<T> *gr, SplayingNode<T> *par,
				SplayingNode<T> *ch, SplayingNode<T> *desc);
		void semiSplay(SplayingNode<T> *);
		void inorder(SplayingNode<T> *);
		void destroyTree(SplayingNode<T> *);

		void virtual visit(SplayingNode<T> *) {}
};


template<class T>
void SplayTree<T>::continueRotation(SplayingNode<T> *gr, SplayingNode<T> *par,
		SplayingNode<T> *ch, SplayingNode<T> *desc)
{
	if (gr != nullptr)
	{
		if (gr->right == ch->parent)
			gr->right = ch;
		else // (gr->right != ch->parent)
			gr->left = ch;
	}
	else
		root = ch;
	if (desc != nullptr)
		desc->parent = par;
	par->parent = ch;
	ch->parent = gr;
}

template<class T>
void SplayTree<T>::rotateR(SplayingNode<T> *p)
{
	p->parent->left = p->right;
	p->right = p->parent;
	continueRotation(p->parent->parent, p->right, p, p->right->left);
}

template<class T>
void SplayTree<T>::rotateL(SplayingNode<T> *p)
{
	p->parent->right = p->left;
	p->left = p->parent;
	continueRotation(p->parent->parent, p->left, p, p->left->right);
}

template<class T>
void SplayTree<T>::semiSplay(SplayingNode<T> *p)
{
	while (p != root)
	{
		if (p->parent->parent == nullptr) // if p parent is root
		{
			if (p->parent->left == p)
				rotateR(p);
			else
				rotateL(p);
		}
		else if (p->parent->left == p)	// p is a left child
		{
			if (p->parent->parent->left == p->parent)
			{
				rotateR(p);
				p = p->parent;
			}
			else
			{
				rotateR(p);
				rotateL(p);
			}
		}
		else // (p is a right child)
		{
			if (p->parent->parent->right == p->parent)
			{
				rotateL(p);
				p = p->parent;
			}
			else
			{
				rotateL(p);
				rotateR(p);
			}
		}

		if (root == nullptr)
			root = p;
	}
}

template<class T>
T* SplayTree<T>::search(const T& el)
{
	SplayingNode<T> *p = root;

	while(p != nullptr)
	{
		if (p->info == el)
		{
			semiSplay(p);
			return (&p->info);
		}
		else if (el < p->info)
			p = p->left;
		else
			p = p->right;
	}

	return (nullptr);
}

template<class T>
void SplayTree<T>::insert(const T& el)
{
	SplayingNode<T> *p = root, *prev = nullptr, *newNode;

	while (p != nullptr)
	{
		prev = p;

		if (el < p->info)
			p = p->left;
		else
			p = p->right;
	}

	newNode = new SplayingNode<T>(el, nullptr, nullptr, prev);
	if (newNode == nullptr)
	{
		std::cerr << "no room for more nodes.\n";
		exit(1);
	}

	if (root == nullptr)
		root = newNode;
	else if (el < prev->info)
		prev->left = newNode;
	else
		prev->right = newNode;
}

template<class T>
void SplayTree<T>::inorder(SplayingNode<T> *p)
{
	if (p != nullptr)
	{
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}

template<class T>
void SplayTree<T>::destroyTree(SplayingNode<T> *p)
{
	if (p != nullptr)
	{
		destroyTree(p->left);
		destroyTree(p->right);
		delete p;
	}
}

#endif
