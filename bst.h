#ifndef _BST_H_
#define _BST_H_

// do not change this file except within the private section of the BST class,
// where you can declare variables and/or functions

#include "gcs.h"

class BST								// a Binary Search Tree (BST)
{
public:
	static const char	YOUR_NAME[];		// used for printing out programmer's name
	static const bool	PREMIUM_VERSION;	// used to designate Regular vs. Premium

	BST(int capacity = 5);				// constructor (default if no argument supplied)
	~BST();								// destructor

	void insert(const GCS& gcs);		// insert a new item into BST
	bool remove(const char* key);		// remove item associated with key from BST
	bool retrieve(const char* key, GCS const *& gcs) const;	// retrieve item associated with key, if any
	int getSize(void) const;			// return number of items contained in the BST

	// see comments in bst.cpp for what these member functions do
	void displayArrayOrder(std::ostream& out) const;
	void displayPreOrder(std::ostream& out) const;
	void displayInOrder(std::ostream& out) const;
	void displayPostOrder(std::ostream& out) const;

private:
	// specify what is stored at each position in the array
	// (you can add additional items to this struct)
	struct Item
	{
		GCS		gcs;		// the GCS instance must be specified this way, NOT as a pointer
		bool 	free = true;// Is the node available or not (Is it NOT on the tree)
	};
	
	static const int columnWidths[3];

	//data values
	Item*			 items;
	int 			 capacity;		//size of array
	int 			 nNodes;			//Number of nodes in the tree

	//Functions
	bool 			 goLeft(int& i) const; //get the left child index
	bool			 goRight(int& i) const; //get the right child index
	void 			 growArray(void); //Double the size of the array
	int 			 preOrder(int i , std::ostream& out) const;	//recursive helper
	int			 	 inOrder(int i , std::ostream& out) const;	//recursive helper
	int 			 postOrder(int i , std::ostream& out) const;	//recursive helper
	static void		 displayHeadings(std::ostream& out);
	bool 			 isLeaf(int i) const;	//Determine if node at index i is a leaf
	void 			 printNode(int i, std::ostream& out) const;
	void 			 deleteNode(int i);    
};

#endif
