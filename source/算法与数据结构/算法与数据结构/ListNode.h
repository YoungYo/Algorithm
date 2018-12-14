#pragma once

template <typename T> class ListNode {
public:
	T data; //微信
	ListNode<T> * pred; //前驱
	ListNode<T> * succ; //后继
	ListNode(){} //针对header和trailer的构造
	ListNode(T e, ListNode<T> * p = NULL, ListNode<T> * s = NULL) :data(e), pred(p), succ(s) {} //默认构造器
};
