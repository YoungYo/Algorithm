#pragma once
#include "print.h"
#include "../DataStructure/Stack.h"

template <typename T> struct BinTreeNode {
	T data; //数据域
	BinTreeNode * LeftChild; //左孩子指针
	BinTreeNode * RightChild; //右孩子指针
};

template <typename T>
void travPre_R(BinTreeNode<T> * root) {
	if (!root)
		return;
	cout << root->data;
	travPre_R(root->LeftChild);
	travPre_R(root->RightChild);
}

template <typename T>
void travPre_I1(BinTreeNode<T> * root) {
	Stack<BinTreeNode<T>*> s; //辅助栈
	if (root) //如果根节点不为空
		s.push(root); //则令根节点入栈
	while (!s.empty()) { //在栈变空之前反复循环
		root = s.pop(); cout << root->data; //弹出并访问当前节点
		if (root->RightChild)
			s.push(root->RightChild); //右孩子先入后出
		if (root->LeftChild)
			s.push(root->LeftChild); //左孩子后入先出
	}
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T> //元素类型、操作器
static void visitAlongLeftBranch ( BinTreeNode<T>* x, Stack<BinTreeNode<T>*>& S ) {
   while ( x ) {
      cout << x->data; //访问当前节点
      S.push ( x->RightChild ); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
      x = x->LeftChild;  //沿左分支深入一层
   }
}

template <typename T> //元素类型、操作器
void travPre_I2 ( BinTreeNode<T>* root) { //二叉树先序遍历算法（迭代版#2）
   Stack<BinTreeNode<T>*> S; //辅助栈
   while ( true ) {
      visitAlongLeftBranch ( root, S ); //从当前节点出发，逐批访问
      if ( S.empty() ) break; //直到栈空
      root = S.pop(); //弹出下一批的起点
   }
}

template <typename T, typename VST>
void travPre_R(BinTreeNode<T> * root, VST& visit) {
	if (!root)
		return;
	visit(root->data);
	//travPre_R(root->LeftChild);
}