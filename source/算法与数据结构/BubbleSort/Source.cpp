#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	/*如果是其他类型，应该选择下面这种交换方式*/
	//int temp = a;
	//a = b;
	//b = temp;
}

/*A：数组首地址
  low：要排序的序列的第一个元素的位置
  high：要排序的序列的最后一个元素的位置*/
void bubbleSort(int *A, int low, int high) {
	for (int i = high; i > low; i--) {
		for (int j = low; j < i; j++) {
			if (A[j] > A[j + 1]) {
				swap(A[j], A[j + 1]);
			}
		}
		for(int i = 0; i < 8; i++)
			cout << A[i] << " ";
		cout << endl;
	}
}

/*A：数组首地址
  low：要排序的序列的第一个元素的位置
  high：要排序的序列的最后一个元素的位置*/
void bubbleSort2(int *A, int low, int high) {
	for (int i = high; i > low; i--) {
		bool flag = false; //记录是否发生过元素交换
		for (int j = low; j < i; j++) {
			if (A[j] > A[j + 1]) {
				swap(A[j], A[j + 1]);
				flag = true;
			}
		}
		for(int i = 0; i < 8; i++)
			cout << A[i] << " ";
		cout << endl;
		if (flag == false)
			return;
	}
}

/*A：数组首地址
  low：要排序的序列的第一个元素的位置
  high：要排序的序列的最后一个元素的位置*/
void bubbleSort3(int *A, int low, int high) {
    while(low < high){

		int last = low;//最右侧的逆序对初始化为[low, low+1]
        for(int j = low; j < high; j++){
            if (A[j] > A[j+1]){
                last = j;
                swap(A[j], A[j + 1]);
            }
        }
		high = last;
		cout << "last= " << last << " " ;
		for(int i = 0; i < 8; i++)
			cout << A[i] << " ";
		cout << endl;
    }
}

int main() {
	int A[8] = { 19,14,96,10,20,15,4,26 };
	int B[8] = { 19,14,10,4,15,26,20,96 };
	//int a = 1, b = 2;
	//swap(a, b);
	bubbleSort(B, 0, 7);
	cout << endl;

	int C[8] = { 19,14,10,4,15,26,20,96 };
	bubbleSort2(C, 0, 7);
	cout << endl;

	int D[8] = { 19,14,10,4,15,26,20,96 };
	bubbleSort3(D, 0, 7);
	//for(int i = 0; i < 8; i++)
	//	cout << B[i] << " ";
	system("pause");
}
