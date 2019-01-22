#pragma once
#include "display.h"

int nSolu = 0; //解的总数
int nCheck = 0; //尝试的总次数

/*判断第 k 个皇后是否与之前的 k-1 个皇后冲突（既可以互相攻击）
  如果与任一皇后冲突，则返回 true，否则返回false*/
bool conflict(int k, int* solu) {
	for (int i = 0; i < k; i++) {
		if (solu[k] == solu[i] || (k + solu[k]) == (i + solu[i]) || (k - solu[k]) == (i - solu[i])) {
			return true;
		}
	}
	return false;
}

/*利用纯数组解决 N 皇后问题*/
void placeQueensWithPureArray(unsigned int N) {
	int* solu = new int[N];
	int size = 0;
	solu[0] = 0; //从原点位置出发
	do { //反复试探、回溯
		if (N <= size || N <= solu[size]) { //若以出界
			size--;	solu[size]++; //回溯一行，并继续试探下一列
		}else { //否则，试探下一行
			while (solu[size] < N && conflict(size, solu)) { //通过与已有皇后的比对
				solu[size]++; //尝试找到可摆放下一皇后的列
				nCheck++;
			}
			if (solu[size] < N) { //若存在可摆放的列
				size++; //当前解的规模加 1
				if (N <= size) { //若解的规模已构成全局解
					nSolu++; //全局解的数量加 1
					displaySolution(solu, N); //打印全局解
				}
				solu[size] = 0; //转入下一行，从第0列开始，试探下一皇后
			}
		}
	} while (0 < size || solu[size] < N);
}
