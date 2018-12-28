/******************************************************************************************
 * 循环队列
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#pragma once

#define MAX_SIZE 10 //最大容量
template <typename T> class CircularQueue {
private:
	int _size = 0; //队列当前规模
	int _front = 0; //队首指针
	int _rear = 0; //队尾指针
	T* _elem; //数据区
public:
	CircularQueue() {
		_elem = new T[MAX_SIZE];
	}

	int size() {
		return _size;
	}

	bool empty() {
		/*队空或队满时，队首指针和队尾指针都会相遇，此时应该根据队列的规模 size 来判断
		  若 size=0，则队空，若 size=max_size，则队满*/
		return _front == _rear && _size == 0; 
	}

	bool enqueue(T const& e) { //入队
		if (_size == MAX_SIZE) return false; //若队已满，则返回false
		_elem[_rear] = e;
		_rear = (_rear + 1) % MAX_SIZE;
		_size++;
		return true;
	}

	T dequeue() { //出队
		if (empty()) return 0;
		T e = _elem[_front];
		_front = (_front + 1) % MAX_SIZE;
		_size--;
		return e;
	}

	T& front() {
		return _elem[_front];
	}
};
