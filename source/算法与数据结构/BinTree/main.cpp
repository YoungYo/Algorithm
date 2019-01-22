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
	
	root.LeftChild = &b;
	b.LeftChild = &c;
	b.RightChild = &d;
	d.LeftChild = &e;
	d.RightChild = &g;
	e.RightChild = &f;
	//cout << root.LeftChild->LeftChild->data;
	travPre_R(&root); cout << endl;
	travPre_I2(&root);
	system("pause");
	return 0;
}