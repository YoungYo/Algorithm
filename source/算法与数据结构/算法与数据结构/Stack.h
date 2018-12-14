#pragma once

/*
#include "Vector.h"

template <typename T> class Stack { //将向量的首端作为栈底，末端作为栈顶
private:
	Vector<T> v;
public:

	//返回栈的规模（栈中元素的个数）
	int size() {
		return v.size();
	}

	//判断栈是否为空
	bool empty() {
		return v.empty();
	}

	//入栈，等效于将新元素作为向量的末元素插入
	void push(T const& e) { //入栈
		v.insert(size(), e);
	}

	//出栈，等效于删除向量的末元素
	T pop() {
		return v.remove(size() - 1);
	}

	//取顶，直接返回向量的末元素
	T& top() {
		return v[v.size() - 1];
	}
};*/

#include "LinkedList.h"

template <typename T> class Stack {
private:
	LinkedList<T> list;
public:

	//返回栈的规模（栈中元素的个数）
	int size() {
		return list.size();
	}

	//判断栈是否为空
	bool empty() {
		return list.empty();
	}

	//入栈，等效于将新元素作为向量的末元素插入
	void push(T const& e) { //入栈
		list.insertAsLast(e);
	}

	//出栈，等效于删除向量的末元素
	T pop() {
		return list.remove(list.last());
	}

	//取顶，直接返回向量的末元素
	T& top() {
		return list.last()->data;
	}
};
