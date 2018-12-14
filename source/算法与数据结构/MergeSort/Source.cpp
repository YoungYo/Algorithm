#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*合并Array[low, mid)和Array[mid, high)
  合并前应保证Array[low, mid)和Array[mid, high)中的元素都是有序的*/
void merge(int* Array, int low, int mid, int high){
	int* A = Array + low; //合并后的向量A[0, high - low) = _elem[low, high)
	int lb = mid - low;
	int* B = new int[lb]; //前子向量B[0, lb) = _elem[low, mid)
	for (int i = 0; i < lb; B[i] = A[i++]); //复制前子向量B
	int lc = high - mid;
	int* C = Array + mid; //后子向量C[0, lc) = _elem[mid, high)

	/*i, j, k分别指向A, B, C中的元素*/
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc);) { //B[j]和C[k]中小者转至A的末尾
		if (j < lb && k < lc) //如果j和k都没有越界，那么就选择B[j]和C[k]中的较小者放入A[i]
			A[i++] = B[j] < C[k] ? B[j++] : C[k++];
		if (j < lb && lc <= k) //如果j没有越界而k越界了，那么就将B[j]放入A[i]
			A[i++] = B[j++];
		if (lb <= j && k < lc) //如果k没有越界而j越界了，那么就将C[k]放入A[i]
			A[i++] = C[k++];
	}

	delete[] B; //释放临时空间B
}

/*非递归版 打印信息*/
void mergeSort_print(int* Array, int low, int high)
{
	int step = 1;
	while (step < high) {
		for (int i = low; i < high; i += step << 1) {
			int lo = i, hi = (i + (step << 1)) <= high ? (i + (step << 1)) : high; //定义二路归并的上界与下界 
			int mid = i + step <= high ? (i + step) : high;
			cout << "lo=" << lo << ", high=" << hi << endl;
			merge(Array, lo, mid, hi);
			for (int i = low; i < high; i++) {
				cout << Array[i] << " ";
			}
			cout << endl;
		}

		//将i和i+step这两个有序序列进行合并
		//序列长度为step
		//当i以后的长度小于或者等于step时，退出
		step <<= 1;//在按某一步长归并序列之后，步长加倍
	}
}

/*递归版 打印信息*/
void mergeSort_Recursive_print(int* Array, int low, int high) {
	if (low + 1 < high) {
		int mid = low + (high - low + 1) / 2;
		cout << "排序前：";
		for (int i = low; i < mid; i++) {
			cout << Array[i] << " ";
		}
		cout << endl;
		mergeSort_Recursive_print(Array, low, mid);
		cout << "排序后：";
		for (int i = low; i < mid; i++) {
			cout << Array[i] << " ";
		}
		cout << endl;

		cout << "排序前：";
		for (int i = mid; i < high; i++) {
			cout << Array[i] << " ";
		}
		cout << endl;
		mergeSort_Recursive_print(Array, mid, high);
		cout << "排序后：";
		for (int i = mid; i < high; i++) {
			cout << Array[i] << " ";
		}
		cout << endl;
		merge(Array, low, mid, high);
	}
}

/*非递归版*/
void mergeSort(int* Array, int low, int high)
{
	int step = 1;
	while (step < high - low) {
		for (int i = low; i < high; i += step << 1) {
			int lo = i, hi = (i + (step << 1)) <= high ? (i + (step << 1)) : high; //定义二路归并的上界与下界 
			int mid = i + step <= high ? (i + step) : high;
			merge(Array, lo, mid, hi);
		}

		//将i和i+step这两个有序序列进行合并
		//序列长度为step
		//当i以后的长度小于或者等于step时，退出
		step <<= 1;//在按某一步长归并序列之后，步长加倍
	}
}

/*递归版
  Array：待排序的数组首地址
  low：待排序的范围的下界
  high：待排序的范围的上界的后一个位置
  比如你要对数组Array[0]~Array[5]进行排序，那么low=0，high=6*/
void mergeSort_Recursive(int* Array, int low, int high) {
	if (low + 1 < high) { //当子数组的长度大于1时，不断对数组进行分解
		int mid = low + (high - low + 1) / 2; //将数组分解成Array[low, mid)和A[mid, high)，圆括号表示开区间，即数组中不包含此元素
		mergeSort_Recursive(Array, low, mid);
		mergeSort_Recursive(Array, mid, high);
		merge(Array, low, mid, high); //合并Array[low, mid)和A[mid, high)
	}
}

int main() {
	int B[8] = { 1,2,4,6,2,3,3,5 };
	int A[11] = { 2,1,6,4,2,3,3,9,2,8,5 };
	int C[2] = { 2,1 };
	int D[9] = { 2,1,6,4,2,3,3,9,2 };

	srand(time(0));
	mergeSort(A, 0, 4);
	/*
	for (int n = 0; n < 5; n++) {
		int length = rand() % 20;
		int* Array = new int[length];
		for (int i = 0; i < length; i++) {
			Array[i] = rand() % 100;
			cout << Array[i] << " ";
		}
		cout << endl;
		mergeSort(Array, 0, length);
		for (int i = 0; i < length; i++) {
			cout << Array[i] << " ";
		}
		cout << endl;
		cout << endl;
		delete[] Array;
	}*/
	//mergeSort(A, 0, 11);
	//mergeSort_Recursive(D, 0, 9);
	//merge(A, 0, 7);
	for (int i = 0; i < 11; i++) {
		cout << A[i] << " ";
	}
	system("pause");
	return 0;
}