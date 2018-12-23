//#include <iostream>
//using namespace std;

#include "../DataStructure/LinkedList.h"

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
	//insertionSort(list, p, n); //list.size()是获取链表的规模（即链表中的节点数）

	p = list.first();
	for (int i = 0; i < n; i++) {
		//cout << p->data << " "; //p->data 指的是节点 p 中存储的数据
		p = p->succ; //令 p 指向 p 的后继
	}
	//cout << endl;
	//cout << endl;
	return 0;
}
