// make NO CHANGES to this file

#include <cstring>
#include <iostream>
#include "bst.h"

using namespace std;

static BST		*database;

static void displayDatabase(bool all)
{
	cout << ">>> array order:" << endl << endl;
	database->displayArrayOrder(cout);
	cout << endl;
	if (! all)
		return;
	cout << ">>> preorder:" << endl << endl;
	database->displayPreOrder(cout);
	cout << endl;
	cout << ">>> inorder:" << endl << endl;
	database->displayInOrder(cout);
	cout << endl;
	cout << ">>> postorder:" << endl << endl;
	database->displayPostOrder(cout);
	cout << endl;
}

static void insertItem(char *name)
{
	cout << ">>> insert " << name << endl << endl;

	GCS*	gcs;
	char	*nm = new char[strlen(name) + 1];
	
	strcpy(nm, name);
	gcs = new GCS(nm);
	database->insert(*gcs);
	delete[] nm;
	delete gcs;
}

static void retrieveItem(char *name)
{
	cout << ">>> retrieve " << name << endl << endl;

	GCS	const *gcs;

	if (database->retrieve(name, gcs))
		cout << *gcs << endl;
	else
		cout << "not found" << endl;
	cout << endl;
}

static void removeItem(char *name)
{
	cout << ">>> remove " << name << endl << endl;
	if (database->remove(name))
		cout << name << " removed";
	else
		cout << name << " not found";
	cout << endl << endl;
}

int main(int argc, char **argv)
{
	if (argc > 1)				// turn off cout
		std::cout.setstate(std::ios_base::badbit);

	cout << "CS260 - Assignment 4 - " << (BST::PREMIUM_VERSION ? "Premium" : "Regular")
		 << " - " << BST::YOUR_NAME << endl << endl
		 << "Database Of Great Computer Scientists" << endl << endl;

	database = new BST();

	insertItem("Ralston, Anthony");
	insertItem("Liang, Li");
	insertItem("Jones, Doug");
	insertItem("Goble, Colin");
	insertItem("Knuth, Donald");
	insertItem("Kay, Alan");
	insertItem("Von Neumann, John");
	insertItem("Trigoboff, Michael");
	insertItem("Turing, Alan");
	displayDatabase(true);

	retrieveItem("Trigoboff, Michael");
	retrieveItem("Kaye, Danny");

	if (BST::PREMIUM_VERSION) {
		cout << ">>> PREMIUM <<<" << endl << endl;
		removeItem("Ralston, Anthony");
		displayDatabase(true);
		removeItem("Jones, Doug");
		displayDatabase(true);
		removeItem("Kay, Alan");
		displayDatabase(true);
		removeItem("Kay, Alan");
		removeItem("Von Neumann, John");
		displayDatabase(true);
		removeItem("Turing, Alan");
		displayDatabase(true);
		removeItem("Goble, Colin");
		displayDatabase(true);
		}

	delete database;
	
	return 0;
}
