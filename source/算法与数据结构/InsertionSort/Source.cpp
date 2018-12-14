#include <iostream>

using namespace std;

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

int main() {
	int A[8] = { 6, 5, 3, 1, 8, 7, 2, 4 };
	insertionSort(A, 0, 8);

	for (int i = 0; i < 8; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
	cout << endl;
	system("pause");
	return 0;
}