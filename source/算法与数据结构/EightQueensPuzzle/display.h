#pragma once

#include <stdio.h>
#include <iostream>
using namespace std;
#include "../DataStructure/Stack.h" //栈
#include "queen.h" //栈

void displayRow ( Queen& q, int N) { //打印当前皇后（放置于col列）所在行
   printf ( "%2d: ", q.x );
   int i = 0;
   while ( i++ < q.y ) printf ( "[]" );
   printf ( "█" );
   while ( i++ < N ) printf ( "[]" );
   printf ( "%2d\n", q.y );
}

void displayRow (int row, int column, int N) { //打印当前皇后（放置于col列）所在行
   printf ( "%2d: ", row );
   int i = 0;
   while ( i++ < column ) printf ( "[]" );
   printf ( "█" );
   while ( i++ < N ) printf ( "[]" );
   printf ( "%2d\n", column );
}

void displaySolution(Vector<Queen> solu_vector, int N) {
	for (int i = 0; i < solu_vector.size(); i++)
		displayRow(solu_vector[i], N);
	for (int i = 0; i < solu_vector.size(); i++) {
		printf("(%d, %d) ", solu_vector[i].x, solu_vector[i].y);
		if (i % 4 == 3)
			cout << endl;
	}
	cout << endl;
}

void displaySolution(int* solu, int N) {
	for (int i = 0; i < N; i++)
		displayRow(i, solu[i], N);
	for (int i = 0; i < N; i++) {
		printf("(%d, %d) ", i, solu[i]);
		if (i % 4 == 3)
			cout << endl;
	}
	cout << endl;
}

