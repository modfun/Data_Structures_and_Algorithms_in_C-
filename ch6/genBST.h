#ifndef GENBST_H
#define GENBST_H

#include <iostream>
#include <queue>
#include <stack>

using std::queue; using std::stack;

template<class T>
class Stack : public stack<T>
{
	public:
		T pop()
		{
			T tmp = queue<T>::top();
			stack<T>::pop();
			return (tmp);
		}
};

template<class T>
class Queue : public queue<T>
{
	public:
		T dequeue()
		{
			T tmp = queue<T>::front();
			queue<T>::pop();
			return (tmp);
		}

		void enqueue(const T &e)
		{
			queue<T>::push(e);
		}
};

template<class T>
struct BSTNode
{
	T el;
	BSTNode<T> *left, *right;

	BSTNode(): left(nullptr), right(nullptr) {}
	BSTNode(const T &e, BSTNode<T> *l = nullptr, BSTNode<T> *r = nullptr):
	el(e), left(l), right(r) {}
};

template<class T>
class BST
{
	public:
		BST() {root = nullptr;}
		~BST() {clear();}

		void clear() {clear(root); root = nullptr;}
		bool isEmpty() const {return root == nullptr;}
		void preorder()
		{
			preorder(root);
		}
		void inorder()
		{
			inorder(root);
		}
		void postorder()
		{
			postorder(root);
		}
		T* search(const T& el) const
		{
			return search(root,el);
		}

		void breadthFirst();
		void iterativePreorder();
		void iterativeInorder();
		void iterativePostorder();
		void MorrisInorder();
		void MorrisPreorder();
		void insert(const T&);
		void deleteByMerging(BSTNode<T>*&);
		void findAndDeleteByMerging(const T&);
		void deleteByCopying(BSTNode<T>*&);
		void balance(T*,int,int);

		int countNodes()
		{
			return (countNodes(root));
		}
		int findHeight()
		{
			return (findHeight(root));
		}
		bool isPerfectlyBalanced();
		bool isBST()
		{
			return (isBST(root, nullptr));
		}
		void printTree();

	protected:
		BSTNode<T>* root;

		void clear(BSTNode<T>*);
		T* search(BSTNode<T>*, const T&) const;
		void preorder(BSTNode<T>*);
		void inorder(BSTNode<T>*);
		void postorder(BSTNode<T>*);
		virtual void visit(BSTNode<T>* p)
		{std::cout << p->el << ' ';}

		int countNodes(BSTNode<T> *);
		int findHeight(BSTNode<T> *);
		bool isBST(BSTNode<T> *, BSTNode<T> *);
		bool isBSTNode(BSTNode<T> *, BSTNode<T> *);
};

#endif
