/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#include <iostream>
#include "Queue.h"
#include "CircularQueue.h"

using namespace std;

int main() {

	CircularQueue<int> queue;
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	queue.enqueue(4);
	queue.enqueue(5);
	queue.enqueue(6);
	queue.enqueue(7);
	queue.enqueue(8);
	queue.enqueue(9);
	queue.enqueue(10);

	cout << queue.enqueue(11) << endl;

	queue.dequeue();

	cout << queue.front() << endl;
	cout << queue.size() << endl;
	
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
	system("pause");
	return 0;
}