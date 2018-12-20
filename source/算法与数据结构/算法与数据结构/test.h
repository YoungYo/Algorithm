/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
/*测试用的头文件*/
#pragma once

#include <iostream>
#include "LinkedList.h"
#include "Application_of_Stack.h"
//#include "Stack.h"

using namespace std;

template <typename T>
void print(LinkedList<T> list) {
	ListNode<T> * p = list.first();
	while (p != list.last()->succ) {
		cout << p->data;
		p = p->succ;
		if (p == list.last()->succ)
			cout << endl;
		else
			cout << " ";
	}
}

void generateTable() {
	//char optr[] = "+      -      *      /      ^      !      (      )      \\0";
	char optr[] = { '+', '-', '*', '/', '^', '!', '(', ')', 'N' };

	const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
	   /*              |-------------------- 当 前 运 算 符 --------------------| */
	   /*              +      -      *      /      ^      !      (      )      \0 */
		/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
		/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
		/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
		/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
		/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
		/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
		/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
	};
	cout << ".";
	for (int i = 0; i < N_OPTR; i++) {
		cout << ',' << optr[i];
	}
	cout << endl;
	for (int i = 0; i < N_OPTR; i++) {
		cout << optr[i];
		for (int j = 0; j < N_OPTR; j++) {
			cout << ',' << pri[i][j];
		}
		cout << endl;
	}

	//for (int i = 0; optr[i] != '\0'; i++) {
	//	if (!isspace(optr[i])) cout << '\'';
	//	while (!isspace(optr[i]) && optr[i]) cout << optr[i++];
	//	if (!isspace(optr[i-1])) cout << "\', ";
	//}
}

void test() {
	//cout << facI(3) << endl;
	//char S[] = "(0! + 1) * 2 ^ (3 ! + 4) - ( 5 ! - 67 - ( 80 + 90 ) )";
	//char S[] = "0 + ( 1 + 23 )/ 4 * 5 * 67 - 8 + 9";
	char S[] = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";

	char* RPN = ( char* ) malloc ( sizeof ( char ) * 1 );   
	RPN[0] = '\0'; //逆波兰表达式
	char* RPN1 = ( char* ) malloc ( sizeof ( char ) * 1 );   
	RPN1[0] = '\0'; //逆波兰表达式
	in2rpn(S, RPN1);
	cout << RPN1 << endl;

	cout << evaluate(S, RPN) << endl;
	cout << RPN << endl;
	//cout << optr2rank('+') << endl;
	cout << evaluate(RPN) << endl;

	//char k[] = "{ ( ) [ ( { } ) ] }";
	//cout << paren(k, 0, 19) << endl;

	//Stack<int> s;
	//convert(s, 19960206, 2);
	//while (s.empty() == false) {
	//	cout << s.pop();
	//}
	//cout << s.size() << endl;
	//cout << s.empty() << endl;

	//s.push(1);
	//s.push(2);
	//s.push(3);

	//cout << s.size() << endl;
	//cout << s.top() << endl;

	//int ascii = '0';
	//for (int i = 0; i < 10; i++) {
	//	printf("\'%c\', ", ascii + i);
	//}
	//ascii = 'A';
	//for (int i = 0; i < 6; i++) {
	//	printf("\'%c\', ", ascii + i);
	//}
	//LinkedList<int> list; //创建一个LinkedList对象

	//list.insertAsLast(6); //作为末节点插入
	//list.insertAsLast(5);
	//list.insertAsLast(3);
	//list.insertAsLast(1);
	//list.insertAsLast(8);
	//list.insertAsLast(7);
	//list.insertAsLast(2);
	//list.insertAsLast(4);

	//ListNode<int>* p = list.first(); //获取首节点的引用

	//int n = list.size();
	//insertionSort(list, p, n); //list.size()是获取链表的规模（即链表中的节点数）

	//p = list.first();
	//for (int i = 0; i < n; i++) {
	//	cout << p->data << " "; //p->data 指的是节点 p 中存储的数据
	//	p = p->succ; //令 p 指向 p 的后继
	//}
	//cout << endl;
	//cout << endl;

	//cout << "链表规模：" << list.size() << endl; //测试size
	//cout << "链表是否为空：" << list.empty() << endl; //测试size

	//ListNode<int> * first = list.first(); //测试first
	//ListNode<int> * last = list.last(); //测试last
	//cout << first->data << ", " << last->data << endl;
	//list.insertBefore(first, -1); //测试insertBefore
	//list.insertAfter(first, 0); //测试insertAfter

	//print(list);

	//ListNode<int>* p = first->succ->succ;
	//ListNode<int>* q = first->succ->succ->succ;
	//cout << q->data << endl;
	//list.merge(p, 1, list, q, 1);
	//list.sort(); //测试sort
	//list.deduplicate(); //测试deduplicate
	//print(list);
	//list.set(-1, 100);
	//cout << list.get(7) << endl;
	//list.uniquify();
	//print(list);
	//cout << "search: " << list.search(5, 5, last)->data << endl; //测试search

	//cout << list.disordered() << endl; //测试disordered

	//cout << list.remove(list.first()->succ) << endl; //测试remove
	//print(list);

	//ListNode<int>* target = list.find(1, 5, list.last()); //测试find
	//cout << target->data << endl;

	//cout << list[3] << endl; //测试重载操作符 “[]”
	/*
	int a[11] = { 1,2,2,3,4,4, 5,5,5,7,7};
	int A[8] = { 19,14,96,10,20,15,4,26 };
	//int B[8] = { 1,2,4,6,2,3,3,5 };
	int B[8] = { 6,3,2,7,1,5,8,4 };
	//int B[2] = { 2, 1 };
	Vector<int> v(B, 0, 8);
	//v.deduplicate();
	//v.increase();
	//v.uniquify();
	//cout << v.binSearch(2, 0, 11) << endl;
	//v.merge(0, 4, 8);
	v.mergeSort(0, 8);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}*/
}
