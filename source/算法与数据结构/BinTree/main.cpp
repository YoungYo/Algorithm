#include "BinTreeNode.h"
#include "print.h"
#include "print_elem.h"
#include "double_elem.h"
#include <iostream>

using namespace std;

int main() {
	BinTreeNode<int> root = { 1, NULL, NULL };
	BinTreeNode<int> b = { 2, NULL, NULL };
	BinTreeNode<int> c = { 3, NULL, NULL };
	BinTreeNode<int> d = { 4, NULL, NULL };
	BinTreeNode<int> e = { 5, NULL, NULL };
	BinTreeNode<int> f = { 6, NULL, NULL };
	BinTreeNode<int> g = { 7, NULL, NULL };
	
	root.LeftChild = &b; b.parent = &root;
	b.LeftChild = &c; c.parent = &b;
	b.RightChild = &d; d.parent = &b;
	d.LeftChild = &e; e.parent = &d;
	d.RightChild = &g; g.parent = &d;
	e.RightChild = &f; f.parent = &e;
	//cout << root.LeftChild->LeftChild->data;
	//travPost_R(&root); cout << endl;
	//travPost_I(&root); cout << endl;
	//travIn_I2(&root);
	travLevel(&root); cout << endl;
	system("pause");
	return 0;
}