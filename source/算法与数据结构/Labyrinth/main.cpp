/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;

#include "../DataStructure/Stack.h" //使用栈
#include "Cell.h" //迷宫格点类

int labySize;
Cell* startCell;
Cell* goalCell;

#include "neighbor.h"
#include "advance.h"

#include "displayLaby.h"
#include "laby.h"

#include "randLaby.h"
#include "readLaby.h"

/******************************************************************************************
 * 迷宫寻径
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   srand ( ( unsigned int ) time ( NULL ) ); //设置随机种子
   //( 1 < argc ) ? readLaby ( argv[1] ) : randLaby(); //使用指定迷宫文件，或随机生成
   randLaby();
   labyrinth ( laby, startCell, goalCell ) ? //启动算法
   printf ( "\nRoute found\a\n" ) :
   printf ( "\nNo route found\a\n" );

   //static char   pattern[5][5][5] = {
   //   "┼", "┼", "┼", "┼", "┼",
   //   "┼", "  ", "┌", "─", "└",
   //   "┼", "┌", "  ", "┐", "│",
   //   "┼", "─", "┐", "  ", "┘",
   //   "┼", "└", "│", "┘", "  "
   //};

   //for (int i = 0; i < 5; i++) {
	  // for (int j=0; j<5; j++)
		 //  printf("%s\t", pattern[i][j]);
	  // cout << endl << endl;
   //}

   //printf("%s ", pattern[0][0]);
   //printf ( "  " );
   //printf ( "█\n" );
   //printf ( "█" );
   //printf ( "█" );
   //printf ( "█\n" );

   getchar();
   return 0;
}