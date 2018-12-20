/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#pragma once

#include "LinkedList.h"

/*对起始于位置 p 的 n 个元素进行排序*/
template <typename T>
void insertionSort(LinkedList<T> &list, ListNode<T>* p, int n) {
	for (int r = 0; r < n; r++) { //逐一为各节点
		ListNode<T>* pos = list.search(p->data, r, p); //查找合适的位置，p->data指的是节点 p 中存储的数据
		list.insertAfter(pos, p->data); //插入
		p = p->succ; //令 p 指向它的后继
		list.remove(p->pred); //删除 p 的前驱
	}
}

/*对数组A[low, high)进行排序*/
void insertionSort(int A[], int low, int high) {
	for (int i = low + 1; i < high; i++) { //从第 2 个元素开始迭代
		int temp = A[i]; //备份 A[i]
		int pos = i - 1;
		while (pos >= low && A[pos] > temp)
			A[pos + 1] = A[pos--];
		A[++pos] = temp;
	}
}
