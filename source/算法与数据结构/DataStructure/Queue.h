#pragma once
#include "LinkedList.h"

template <typename T> class Queue {
private:
	LinkedList<T> list;
public:
	int size() {
		return list.size();
	}

	bool empty() {
		return list.empty();
	}

	void enqueue(T const& e) { //入队，从尾部插入
		list.insertAsLast(e);
	}

	T dequeue() { //出队，从首部删除
		return list.remove(list.first());
	}

	T& front() { //队首
		return list.first()->data;
	}
};
