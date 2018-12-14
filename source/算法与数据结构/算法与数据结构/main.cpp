#include <iostream>
#include "LinkedList.h"

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

template <typename T>
void insertionSort(LinkedList<T> &list, ListNode<T>* p, int n) {
	for (int r = 0; r < n; r++) { //逐一为各节点
		ListNode<T>* pos = list.search(p->data, r, p); //查找合适的位置，p->data指的是节点 p 中存储的数据
		list.insertAfter(pos, p->data); //插入
		p = p->succ; //令 p 指向它的后继
		list.remove(p->pred); //删除 p 的前驱
	}
}

int main() {
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
	system("pause");
	return 0;
}