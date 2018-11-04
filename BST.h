//Header File created by Dr.Ravikumar 2012

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iomanip>
#include <vector>
#include <iostream>    // For NULL
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
//void findWord( x )	  --> linenumber
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted



template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree() :root(NULL)
	{
	}

	BinarySearchTree(const BinarySearchTree & rhs) : root(NULL)
	{
		*this = rhs;
	}

	/**
	* Destructor for the tree
	*/
	void InOrder(vector<int> & B) {
		Inorder(root, B);
	}
	~BinarySearchTree()
	{
		makeEmpty(root);
	}
	Comparable  RankOfKey(const Comparable  x)
	{
		return RankOfKey(x, root);
	}
	Comparable KeyOfRank(const Comparable x)
	{
		return KeyOfRank(x, root);
	}
	/**
	* Find the smallest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMin() const
	{

		return findMin(root)->element;
	}
	Comparable & deleteMin()
	{
		return deleteMin(root)->element;

	}
	/**
	* Find the largest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMax() const
	{

		return findMax(root)->element;
	}

	long int treeSize() const
	{
		return treeSize(root);
	}

	void findWord(const Comparable & word)
	{
		return findWord(word, root);
	}

	/**
	* Returns true if x is found in the tree.
	*/
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == NULL;
	}

	/**
	* Print the tree contents in sorted order.
	*/
	void printTree(ostream & out = cout) const
	{
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}
	/**
	* Make the tree logically empty.

	void makeEmpty()
	{
		makeEmpty(root);
	}
	*/
	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(Comparable & x, vector<int> key, double f_value)
	{
		insert(x, root, key, f_value);
	}
	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(Comparable && x, vector<int> key, double f_value)
	{
		insert(std::move(x), root, key, f_value);
	}
	/**
	* Remove x from the tree. Nothing is done if x is not found.
	*/
	bool remove(const Comparable & x)
	{
		if (remove(x, root))
			return true;
		return false;
	}

	/**
	* Deep copy.
	*/
	const BinarySearchTree & operator=(const BinarySearchTree & rhs)
	{
		if (this != &rhs)
		{
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}

private:
	struct BinaryNode
	{
		Comparable element;		//Node
		BinaryNode *left;
		BinaryNode *right;
		//int size;
		//int height;
		vector<int> key;
		//long int parent;
		//int g;
		double f;
		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt,/* int s, int h,*/ vector<int> k, double f)
			: element(theElement), left(lt), right(rt),/* size(s), height(h),*/ key(k), f(f) { }

		//int getHeight() { return height; }
	};

	BinaryNode *root;

	Comparable RankOfKey(const Comparable  x, BinaryNode *  T)
	{
		if (T == NULL) return 0;
		if (x < root->element)
		{
			return RankOfKey(x, T->left);
		}
		//the rank of x in the left subtree;
		else if (x == root->element)
		{
			return 1 + size(T->left);
		}
		// be careful with the case in which the left subtree is empty
		else {
			return 1 + size(T->left) + RankOfKey(x, T->right);
		}
		// note again that left subtree could be empty
	}
	/////////////////////////////////////////////////////////////////////
	Comparable KeyOfRank(const Comparable k, BinaryNode * T)
	{
		if (T == NULL || k > size(T))
		{
			return 0;
		}
		if (size(T->left) == k - 1)
		{
			return T->element; // note: left subtree could be NULL
		}
		else if (size(T->left) >= k)
			return KeyOfRank(k, T->left);

		else  // in this case, size of the left subtree of T is < k-1)
			return KeyOfRank(k - size(T->left) - 1, T->right);
	}
	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	/*bool insert(Comparable & x, BinaryNode * & t, vector<int> key, int g, int f)
	{
		if (t == NULL)
		{
			t = new BinaryNode(x, NULL, NULL, 1, 0, key, g, f);
			return true;
		}
		else if (f < t->f)
		{
			if (insert(x, t->left, parent, key, g, f))
			{
				t->size++;
				t->height = height(t);
				return true;
			}
		}
		else if (f > t->f)
		{
			t->size++;
			t->height = height(t);
			return true;
		}
	}*/

	bool insert(const Comparable & x, BinaryNode * & t, vector<int> key, double f)
	{
		if (t == NULL)
		{
			t = new BinaryNode{ x, nullptr, nullptr,/* 1, 0,*/ key, f };
			//t->height = 0;
			//t->size = 1;
			return true;
		}
		else if (f <= t->f)
		{
			bool insertBool = insert(x, t->left, key, f);
			if (insertBool)
			{
				//t->height = max(findLeftHeight(t), findRightHeight(t)) + 1;
				//t->size++;
				return true;
			}
		}
		/*else if (key == t->key)
			return false;*/
		else
		{
			bool insertBool2 = insert(x, t->right, key, f);
			if (insertBool2)
			{
				//t->height = max(findLeftHeight(t), findRightHeight(t)) + 1;
				//t->size++;
				return true;
			}
		}
	}

/*	int findLeftHeight(BinaryNode* t)
	{
		if (t->left == NULL)
			return -1;
		else
			return t->left->getHeight();
	}
	int findRightHeight(BinaryNode* t)
	{
		if (t->right == NULL)
			return -1;
		else
			return t->right->getHeight();
	}*/



	/**
	* Internal method to find the smallest item in a subtree t.
	* Return node containing the smallest item.
	*/
	BinaryNode * findMin(BinaryNode * t) const
	{
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}
	/**
	* Internal method to remove from a subtree.
	* x is the item to remove.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	bool remove(const Comparable & x, BinaryNode * & t)
	{
		if (t == NULL)
			return false;   // Item not found; do nothing
		if (x->f < t->f)
		{
			bool removeBool = remove(x, t->left);
			if (removeBool)
			{
				//t->size--;
				return true;
			}
			else
				return false;
		}
		else if (t->f < x->f)
		{
			bool removeBool2 = remove(x, t->right);
			if (removeBool2)
			{
			//	t->size--;
				return true;
			}
			else
				return false;
		}
		else
		{
			if (t->left == NULL && t->right == NULL)
			{
				t = NULL;
				return true;
			}
			else if (t->left != NULL && t->right == NULL)
			{
				t = t->left;
				return true;
			}
			else if (t->left == NULL && t->right != NULL)
			{
				t = t->right;
				return true;
			}
			else
			{
				BinaryNode* y = deleteMin(t->right);
				t->element = y->element;
				//t->size--;
				return true;
			}
		}
	}

	BinaryNode * deleteMin(BinaryNode *&t) {

		if (t == NULL)
			return NULL;
		if (t->left == NULL) {
			BinaryNode* temp = t;
			t = t->right;
			return temp;
		}
		BinaryNode* temp = deleteMin(t->left);
		//t->size = t->size = 1;
		//t->height = max(findLeftHeight(t), findRightHeight(t)) + 1;
		return temp;
	}









	/*bool remove(const Comparable & x, BinaryNode * & t)	//element == key
	{
		if (t == NULL)
			return false;   // Item not found; do nothing
		if (x < t->element)
		{
			if (remove(x, t->left))
			{
				//t->size--;
				//t->height = height(t);
				return true;
			}
			else
				return false;
		}
		else if (t->element < x)
		{
			if (remove(x, t->right))
			{
				//t->size--;
				//t->height = height(t);
				return true;
			}
			else
				return false;
		}
		else if (t->element == x)
		{
			if (t->left == NULL && t->right == NULL)	//no children
			{
				//delete t;
				makeEmpty(t);
				return true;
			}
			else if (t->left == NULL && t->right != NULL) //right
			{
				//t->size--;
				//t->height = height(t);
				t = t->right;
				//delete t;
				makeEmpty(t->right);
				return true;
			}
			else if (t->left != NULL && t->right == NULL)//left
			{
				//t->size--;
				t = t->left;
				//t->height = height(t);
				//delete t->left;
				makeEmpty(t->left);
				return true;
			}
			else if (t->left != NULL && t->right != NULL) // Two children
			{
				//t->size--;
				//t->height = height(t);
				t = findMin(t->right);
				deleteMin(t->right);
				return true;
			}
		}
		else {
			BinaryNode * y = deleteMin(t->right);
			t = y;
			//t->height = height(t);
			//t->size--;
			return true;
		}

		return false;
	}*/

	/*BinaryNode * deleteMin(BinaryNode *&t) {

		if (t == NULL)
			return NULL;
		if (t->left == NULL) {
			BinaryNode* temp = t;
			t = t->right;
			return temp;
		}
		BinaryNode* temp = deleteMin(t->left);
		//t->size = t->size = 1;
		//t->height = max(findLeftHeight(t), findRightHeight(t)) + 1;
		return temp;
	}*/

	//BinaryNode * deleteMax(BinaryNode * & t)	///////////////////////
	//{
	//	if (t == NULL)
	//		return NULL;
	//	if (t->right != NULL)
	//	{
	//		makeEmpty(findMax(t));
	//	}
	//}
	/**
	* Internal method to find the largest item in a subtree t.
	* Return node containing the largest item.
	*/
	BinaryNode * findMax(BinaryNode *t) const
	{
		if (t != NULL)
			while (t->right != NULL)
				t = t->right;
		return t;
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}

	void findWord(const Comparable & x, BinaryNode *t)
	{
		while (t != NULL)
			if (x < t->element)
				t = t->left;
			else if (t->element < x)
				t = t->right;
			else {
				//cout << "Line numbers<BST>: " << t->linenumber << endl;
				return;    // Match
			}
	}
	/**
	* Internal method to test if an item is in a subtree.
	* x is item to search for.
	* t is the node that roots the subtree.
	*/

	bool contains(const Comparable x, BinaryNode *t) const
	{
		if (t == NULL)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
	bool contains( const Comparable & x, BinaryNode *t ) const
	{
	while( t != NULL )
	if( x < t->element )
	t = t->left;
	else if( t->element < x )
	t = t->right;
	else
	return true;    // Match

	return false;   // No match
	}
	*****************************************************/


	// Internal method to make subtree empty.

	void makeEmpty(BinaryNode * & t)
	{
		if (t != NULL)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}

	/**
	* Internal method to print a subtree rooted at t in sorted order.
	*/
	void printTree(BinaryNode *t, ostream & out) const
	{
		if (t != NULL)
		{
			printTree(t->left, out);
			out << t->element << setw(19) << t->size << endl;
			printTree(t->right, out);
		}
	}
	////////////////////////////////////////////////
	void Inorder(BinaryNode *t, vector<int> & B)
	{
		if (t != NULL)
		{
			Inorder(t->left, B);
			B.push_back(t->element);
			Inorder(t->right, B);
		}
	}
	/**
	* Internal method to clone subtree.
	*/
	BinaryNode * clone(BinaryNode *t) const
	{
		if (t == NULL)
			return NULL;
		else
			return new BinaryNode(t->element, clone(t->left), clone(t->right));
	}
	long int treeSize(BinaryNode* t) const
	{
		if (t == NULL)
			return 0;
		else
			return treeSize(t->left) + treeSize(t->right) + 1;
	}

public:

	static int height(BinaryNode* t) {
		// returns the height of the tree t
		if (t == NULL) return 0;
		else {
			int p = height(t->left);
			int q = height(t->right);
			if (p < q)
				return 1 + q;
			else return 1 + p;

		}
	}

	static int size(BinaryNode* t) {
		if (t == NULL) return 0;
		else
			return /*1 + size(t->left) + size(t->right);*/ t->size;
	}

	BinaryNode* getRoot() {
		return root;
	}

};

#endif
#pragma once
#pragma once
