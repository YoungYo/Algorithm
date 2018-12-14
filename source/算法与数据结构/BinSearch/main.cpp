#include <iostream>

using namespace std;

/* A：数组首地址
 * target：查找的目标元素
 * low：查找范围的下界位置
 * high：查找范围的上界位置
 *
 * 返回值：若查找成功，则返回目标元素的位置，若查找失败，则返回-1*/
int binSearch(int * A, int target, int low, int high){
    while(low <= high){ //每步迭代可能都要做两次比较判断，有三个分支
        //int mid = int((low + high) * 0.618); //以中点为轴点 
        int mid = (low + high) >> 1; //以中点为轴点
        cout << A[mid] << endl;
        if(target < A[mid])
            high = mid - 1 ; //深入前半段[low, mid]继续查找 
        else if(A[mid] < target)
            low = mid + 1; //深入后半段[mid+1, high]继续查找
        else 
            return mid; //在mid处命中
    }
    return -1; //查找失败，返回-1
}
/* A：数组首地址
 * target：查找的目标元素
 * low：查找范围的下界位置
 * high：查找范围的上界位置
 *
 * 返回值：若查找成功，则返回目标元素的位置，若查找失败，则返回-1*/
int binSearch2(int * A, int target, int low, int high) {
	high++;
	int n = 0;
	while (1 < high - low) {
		int mid = (low + high) >> 1; //以中点为轴点，经比较后确定深入
		(target < A[mid]) ? high = mid : low = mid; //查找区间为[lwo, mid-1]或[mid, high]
		n++;
	}//出口时high = low
	cout << n;
	return (target == A[low]) ? low : -1; //返回命中元素所在的位置或-1
}

/*参数a：斐契那波数列中的某一个数
  返回值：该数在斐契那波数列中的位置*/
int fibLength(int a) {
	int f = 0, f1 = 0, f2 = 1, index = 1;
	if (f1 == a)
		return 1;
	if (f2 == a)
		return 2;
	while (f <= a) {
		f = f1 + f2;
		f1 = f2;
		f2 = f;
		index++;
	}
	return index;
}

/*参数len：斐契那波数列的长度
  返回值：返回一个数组指针，改指针指向长度为len的数组，该数组中存放着前len个斐契那波数*/
int * createFibSequence(int len) {
	int * fib = new int[len];
	if (len == 1) {
		fib[0] = 0;
		return fib;
	}else if (len == 2) {
		fib[0] = 0;
		fib[1] = 1;
		return fib;
	}
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i < len; i++) {
		fib[i] = fib[i - 2] + fib[i - 1];
	}
	return fib;
}

/* A：数组首地址
 * target：查找的目标元素
 * low：查找范围的下界位置
 * high：查找范围的上界位置
 *
 * 返回值：若查找成功，则返回目标元素的位置，若查找失败，则返回-1*/
int fibSearch(int * A, int target, int low, int high) {
	high++;
	int fib_len = fibLength(high - low + 1);
	int * fib = createFibSequence(fib_len); //创建斐契那波数列

	fib_len--;
	while (low < high)
	{
		while (high - low < fib[fib_len])
			fib_len--; //通过向前顺序查找，确定形如Fib[k] - 1的轴点
		int mid = low + fib[fib_len] - 1; //按黄金比例切分
		if (target < A[mid]) //深入前半段[low, mid)继续查找
			high = mid;
		else if (A[mid] < target) //深入后半段[mid+1, low)
			low = mid + 1;
		else
			return mid; //在mid处命中
	}
	delete[] fib; //释放斐契那波数列占用的内存
	return -1; //查找内存
}

int main(){
    //int nums[10] = {5, 12, 23, 43, 66, 98, 100, 290, 300, 555};
    int nums[7] = {5, 12, 23, 43, 66, 98, 100};

	//for (int i = 0; i < 7; i++)
		//cout << binSearch2(nums, nums[i], 0, 6) << endl;
	int len = 40;
	int * fib = createFibSequence(len);
	delete[] fib;

	for (int i = 0; i < 7; i++)
		cout << fibSearch(nums, nums[i], 0, 6) << endl;

	system("pause");
    return 0;
}
