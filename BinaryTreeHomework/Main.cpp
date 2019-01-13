#include <iostream>

#include "BinaryTree.h"

using namespace std;

int main()
{
	Tree<int> tree;
	tree.Add(50);
	tree.Add(23);
	tree.Add(55);
	tree.Add(27);
	tree.Add(28);
	tree.Add(21);
	tree.Add(25);
	tree.Print(tree.GetRoot());
	cout << endl;
	//tree.Print(tree.Maximum(tree.GetRoot()));
	//cout << endl;
	//tree.Print(tree.Minimum(tree.GetRoot()));
	//cout << endl;
	//cout << tree.GetSize() << endl;
	//tree.Print(tree.Previous(tree.GetRoot()));
	//cout << endl;
	//tree.Print(tree.Search(28));
	//cout << endl;
	cout << tree.Remove(21) << endl;
	tree.Print(tree.GetRoot());
	cout << endl;
	cout << tree.Remove(55) << endl;
	tree.Print(tree.GetRoot());
	cout << endl;
}