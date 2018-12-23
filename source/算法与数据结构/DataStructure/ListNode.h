/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#pragma once

template <typename T> class ListNode {
public:
	T data; //微信
	ListNode<T> * pred; //前驱
	ListNode<T> * succ; //后继
	ListNode(){} //针对header和trailer的构造
	ListNode(T e, ListNode<T> * p = NULL, ListNode<T> * s = NULL) :data(e), pred(p), succ(s) {} //默认构造器
};
