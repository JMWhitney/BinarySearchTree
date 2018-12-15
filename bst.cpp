#include <iostream>
#include <iomanip>
#include "bst.h"

using namespace std;

// change the value of this variable to be your own name instead of "I. Forgot"
const char	BST::YOUR_NAME[]{"Justin Whitney"};

// change the value of this variable to true if you're doing the Premium version
const bool	BST::PREMIUM_VERSION{true};

const int BST::columnWidths[3] = {23, 6, 6};

BST::BST(int capacity) : items{new Item[capacity +1]},
						 capacity{capacity},
						 nNodes{0}
{
}

BST::~BST()
{
	delete [] items;
}

bool BST::goLeft(int& i) const
{
	//If there is space for a left child, go there
	//Otherwise return false

	if ((2*i + 1) < capacity) {
		i = 2*i + 1;
		return true;
	} else {
		return false;
	}
}

bool BST::goRight(int& i) const
{
	//If there is space for a right child, go there
	//Otherwise return false
	if ((2*i + 2) < capacity) {
		i = 2*i + 2;
		return true;
	} else { 
		return false;
	}
}

void BST::displayHeadings(std::ostream& out)
{
	//Print something like this:
	// name				leaf?	index
	// ----				-----	-----
	out << left << setw(columnWidths[0]) << "name"
		<< left << setw(columnWidths[1]) << "leaf?"
		<< left << setw(columnWidths[2]) << "index" << endl
		<< left << setw(columnWidths[0]) << "----"
		<< left << setw(columnWidths[1]) << "-----"
		<< left << setw(columnWidths[2]) << "-----" << endl;
}
void BST::growArray(void) 
{
	//Create new array twice the size of current array
	//Copy the values from old array to new array
	//delete old array
	//Reassign 
	Item* temp = new Item[2*capacity];
	for(int i = 0; i < capacity; i++) {
		temp[i].gcs = items[i].gcs;
		temp[i].free = items[i].free;
	}
	delete [] items;
	items = temp;
	capacity *=2;
}

bool BST::isLeaf(int i) const 
{
	//If we have reached capacity, or there are no child nodes
	if((2*i+1) >= capacity-1 || (items[2*i+1].free && items[2*i+2].free)) {
		return true;
	} else {
		return false;
	}
}

void BST::printNode(int i, std::ostream& out) const
{
	//Print a node, if it is a leaf, and its index with formatting
	out << left << setw(columnWidths[0]) << items[i].gcs; 
	if (isLeaf(i)) {
		out << left << setw(columnWidths[1]) << "leaf";
	} else {
		out << left << setw(columnWidths[1]) << ' ';
	}
		out << left << setw(columnWidths[2]) << i << endl;

}

// insert a new item into the BST
//left  = 2i=1
//right = 2i+2
//parent = (i-1)/2
void BST::insert(const GCS& gcs)
{
	//If the tree is empty, insert to the first array position.
	//Otherwise compare gcs to the parent nodes and traverse
	//Either right or left depending on the comparision until 
	//a free node is reached. If the capacity is exceeded
	//(Can't go left or right) grow the array and continue. 
	if(nNodes == 0) {
		items[0].gcs = gcs;
		items[0].free = false;
		nNodes++;
		return;
	} else {
		int i = 0;
		while(true) {
			if (gcs < items[i].gcs) {
				if(goLeft(i) == false) {
					growArray();
					goLeft(i);
				}
				if(items[i].free) {
					items[i].gcs = gcs;
					items[i].free = false;
					nNodes++;
					return;
				}
			} else if (gcs == items[i].gcs) {
				return;
			} else {
				if(goRight(i) == false) {
					growArray();
					goRight(i);
				}
				if(items[i].free) {
					items[i].gcs = gcs;
					items[i].free = false;
					nNodes++;
					return;
				}
			}
		}
	}	
}

// retrieve item associated with key
// returns true if it finds key, false if it can't
bool BST::retrieve(const char* key, GCS const *& gcs) const
{
	GCS Key(key);
	//start at head, and traverse the list either left or right
	//Depending on the comparision of the key to the current node. If the key is the same as the
	//Current node return true. If a leaf node is reached and the key is not found
	//The key is not on the tree.
	int i = 0;
	while(true) {
		if (Key == items[i].gcs) { //Compare to current node
			gcs = &items[i].gcs;
			return true;
		} else if (Key < items[i].gcs) { //traverse left tree
			if(goLeft(i) == false){ //Reached the height of the tree
				return false;
			}
			if(items[i].free) {		//Reached an empty node
				return false;
			}
		} else { //Traverse right tree
			if(goRight(i) == false) {  
				return false;			 
			}
			if(items[i].free) {
				return false;		
			}
		}
	}
	return false;
}

// remove item associated with key from BST
bool BST::remove(const char* key)
{
	int i = 0;
	GCS Key(key);
	//Search the tree until the key or an empty node is found.
	//If the key is found, delete it. If the key is not found return false.
	while (i < capacity) {
		if (items[i].free) {
			return false;
		}else if (Key == items[i].gcs) {
			deleteNode(i);
			return true;
		} else if (Key < items[i].gcs) {
			goLeft(i);
		} else {
			goRight(i);
		}
	}
	return false;
}

void BST::deleteNode(int i) 
{
	int j = i;
	//a leaf
	if (items[2*i+1].free && items[2*i+2].free) {
		items[i].free = true; //All we need to do is indicate it is not on the tree anymore.	
	}
	//No Right child
	else if (!items[2*i+1].free && items[2*i+2].free) {
		//find inorder predecessor
		goLeft(j);
		while ((2*j+2) < capacity && !items[2*j+2].free){
			goRight(j);
		}
		items[i].gcs = items[j].gcs;
		items[j].free = true;
	}
	//two or right children
	else {
		//find the inorder successor
		goRight(j);
		while((2*j+1) < capacity && !items[2*j+1].free) {
			goLeft(j);
		}
		items[i].gcs = items[j].gcs;
		items[j].free = true;

	}
	nNodes--; 
}

// return number of items contained in the BST
int BST::getSize(void) const
{
	return nNodes;
}

// display items in the tree by traversing the array from beginning to end
void BST::displayArrayOrder(std::ostream& out) const
{
	displayHeadings(out);
	int i = 0;
	int n = 0;
	while(n < nNodes) {
		if(!items[i].free) {
			printNode(i, out);
			n++;
		}
		i++;
	}
	cout << "(items printed)" << setw(20) << ' ' << '(' << n << ')' << endl;
}

// display items in the tree in preorder
void BST::displayPreOrder(std::ostream& out) const
{
	displayHeadings(out);
	int n = preOrder(0 , out);
	out << "(items printed)" << setw(20) << ' ' << '(' << n << ')' << endl;
}

int BST::preOrder(int i, std::ostream& out) const
{
	static int n{0};
	//root, then left, then right while in bounds of the tree and array
	if (i < capacity && !items[i].free) {
		n++;
		printNode(i, out);
		preOrder(2*i+1 , out);
		preOrder(2*i+2 , out);
	}
	return n;
}

// display items in the tree in inorder
void BST::displayInOrder(std::ostream& out) const
{
	displayHeadings(out);
	int n = inOrder(0, out);
	out << "(items printed)" << setw(20) << ' ' << '(' << n << ')' << endl;
}

int BST::inOrder(int i, std::ostream& out) const
{
	static int n{0};
	//left, then root, then right
	if (i < capacity && !items[i].free) {
		inOrder(2*i+1, out);
		n++;
		printNode(i, out);
		inOrder(2*i+2, out);
	}
	return n;
}

// display items in the tree in postorder
void BST::displayPostOrder(std::ostream& out) const
{
	displayHeadings(out);
	int n = postOrder(0, out);
	out << "(items printed)" << setw(20) << ' ' << '(' << n << ')' << endl;
}

int BST::postOrder(int i, std::ostream& out) const
{
	static int n{0};
	//left, then right, then root.
	if (i < capacity && !items[i].free) {
		postOrder(2*i+1, out);
		postOrder(2*i+2, out);
		n++;
		printNode(i, out);
	}
	return n;
}
