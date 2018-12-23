/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#include <iostream>
#include "insertion_sort.h"

using namespace std;


int main() {
	int A[8] = { 6, 5, 3, 1, 8, 7, 2, 4 };
	insertionSort(A, 0, 8);

	for (int i = 0; i < 8; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
	cout << endl;
	
	LinkedList<int> list; //创建一个LinkedList对象

	list.insertAsLast(6); //作为末节点插入
	list.insertAsLast(5);
	list.insertAsLast(3);
	list.insertAsLast(1);
	list.insertAsLast(8);
	list.insertAsLast(7);
	list.insertAsLast(2);
	list.insertAsLast(4);

	ListNode<int>* p = list.first(); //获取首节点的引用

	int n = list.size();
	insertionSort(list, p, n); //list.size()是获取链表的规模（即链表中的节点数）

	p = list.first();
	for (int i = 0; i < n; i++) {
		cout << p->data << " "; //p->data 指的是节点 p 中存储的数据
		p = p->succ; //令 p 指向 p 的后继
	}
	cout << endl;
	cout << endl;
	system("pause");
	return 0;
}