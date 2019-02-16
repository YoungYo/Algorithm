#pragma once
#include "print.h"
#include "../DataStructure/Stack.h"
#include "../DataStructure/Queue.h"

template <typename T> struct BinTreeNode {
	T data; //数据域
	BinTreeNode * LeftChild; //左孩子指针
	BinTreeNode * RightChild; //右孩子指针
	BinTreeNode * parent; //父节点指针
};

/*先序遍历*/
template <typename T, typename VST>
void travPre_R(BinTreeNode<T> * root, VST& visit) {
	if (!root)
		return;
	visit(root->data);
	travPre_R(root->LeftChild);
}

template <typename T>
void travPre_R(BinTreeNode<T> * root) {//二叉树先序遍历算法（递归版）
	if (!root)
		return;
	cout << root->data;
	travPre_R(root->LeftChild);
	travPre_R(root->RightChild);
}

template <typename T>
void travPre_I1(BinTreeNode<T> * root) {//二叉树先序遍历算法（迭代版#1）
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
	  if(x->RightChild)
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
/*先序遍历结束*/

/*中序遍历*/
template <typename T>
void travIn_R(BinTreeNode<T> * root) {//二叉树先序遍历算法（递归版）
	if (!root)
		return;
	travIn_R(root->LeftChild);
	cout << root->data;
	travIn_R(root->RightChild);
}

template <typename T> //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongLeftBranch ( BinTreeNode<T> * x, Stack<BinTreeNode<T> * >& S ) {
	while (x) { S.push(x); x = x->LeftChild; } //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
}

template <typename T> //元素类型、操作器
void travIn_I(BinTreeNode<T> * root) {//二叉树先序遍历算法（迭代版）
   Stack<BinTreeNode<T> *> S; //辅助栈
   while ( true ) {
      goAlongLeftBranch ( root, S ); //从当前节点出发，逐批入栈
      if ( S.empty() ) break; //直至所有节点处理完毕
      root = S.pop(); 
	  cout << root->data; //弹出栈顶节点并访问之
      root = root->RightChild; //转向右子树
   }
}

template <typename T> //元素类型、操作器
void travIn_I2 ( BinTreeNode<T>* root ) { //二叉树中序遍历算法（迭代版#2）
   Stack<BinTreeNode<T>*> S; //辅助栈
   while ( true )
      if ( root ) {
         S.push ( root ); //根节点进栈
         root = root->LeftChild; //深入遍历左子树
      } else if ( !S.empty() ) {
         root = S.pop(); //尚未访问的最低祖先节点退栈
         cout << root->data; //访问该祖先节点
         root = root->RightChild; //遍历祖先的右子树
      } else
         break; //遍历完成
}
/*中序遍历结束*/

/*后序遍历*/
template <typename T>
void travPost_R(BinTreeNode<T> * root) {//二叉树先序遍历算法（递归版）
	if (!root)
		return;
	travPost_R(root->LeftChild);
	travPost_R(root->RightChild);
	cout << root->data;
}

template <typename T> //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoHLVFL ( Stack<BinTreeNode<T>*>& S ) { //沿途所遇节点依次入栈
   while ( BinTreeNode<T>* x = S.top() ) //自顶而下，反复检查当前节点（即栈顶）
      if ( x->LeftChild ) { //尽可能向左
         if ( x->RightChild ) S.push ( x->RightChild ); //若有右孩子，优先入栈
         S.push ( x->LeftChild ); //然后才转至左孩子
      } else //实不得已
         S.push ( x->RightChild ); //才向右
   S.pop(); //返回之前，弹出栈顶的空节点
}

template <typename T>
void travPost_I ( BinTreeNode<T>* root ) { //二叉树的后序遍历（迭代版）
   Stack<BinTreeNode<T>*> S; //辅助栈
   if ( root ) S.push ( root ); //根节点入栈
   while ( !S.empty() ) {
      if ( S.top() != root->parent ) //若栈顶非当前节点之父（则必为其右兄），此时需
         gotoHLVFL ( S ); //在以其右兄为根之子树中，找到HLVFL（相当于递归深入其中）
      root = S.pop(); cout << root->data; //弹出栈顶（即前一节点之后继），并访问之
   }
}
/*后序遍历结束*/

/*层次遍历*/
template <typename T> //元素类型
void travLevel ( BinTreeNode<T>* root ) { //二叉树层次遍历算法
   Queue<BinTreeNode<T>*> Q; //辅助队列
   Q.enqueue ( root ); //根节点入队
   while ( !Q.empty() ) { //在队列再次变空之前，反复迭代
      BinTreeNode<T>* x = Q.dequeue(); cout << x->data; //取出队首节点并访问之
      if ( x->LeftChild ) Q.enqueue ( x->LeftChild ); //左孩子入队
      if ( x->RightChild ) Q.enqueue ( x->RightChild ); //右孩子入队
   }
}
/*层次遍历结束*/