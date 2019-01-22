/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#pragma once
#include "../DataStructure/Stack.h" //栈
#include "queen.h" //栈
#include "display.h" //栈

int nSolu = 0; //解的总数
int nCheck = 0; //尝试的总次数

void placeQueens ( int N ) { //N皇后算法（迭代版）：采用试探/回溯的策略，借助栈记录查找的结果
   Stack<Queen> solu; //存放（部分）解的栈
   Queen q ( 0, 0 ); //从原点位置出发
   Vector<Queen> solu_vector;

   do { //反复试探、回溯
      if ( N <= solu.size() || N <= q.y ) { //若已出界，则
         q = solu.pop(); q.y++; //回溯一行，并继续试探下一列
      } else { //否则，试探下一行
         while ( ( q.y < N ) && ( 0 <= solu.find ( q ) ) ) //通过与已有皇后的比对
            /*DSA*///while ((q.y < N) && (solu.find(q))) //（若基于List实现Stack，则find()返回值的语义有所不同）
            { q.y++; nCheck++; } //尝试找到可摆放下一皇后的列
         if ( N > q.y ) { //若存在可摆放的列，则
            solu.push ( q ); //摆上当前皇后，并
			if (N <= solu.size()) {
				nSolu++; //若部分解已成为全局解，则通过全局变量nSolu计数
				displaySolution(solu.toVector(), N);
			}
            q.x++; q.y = 0; //转入下一行，从第0列开始，试探下一皇后
         }
      }/*DSA*/
   } while ( ( 0 < q.x ) || ( q.y < N ) ); //所有分支均已或穷举或剪枝之后，算法结束
}

