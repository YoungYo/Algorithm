/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#include "eightQueensPuzzle.h"
//#include "eightQueenPuzzle_pureArray.h"

int main() {
	//placeQueensWithPureArray(8);
	placeQueens(8);

	cout << nSolu << " solution(s) found after " << nCheck << " check(s)\a";
	system("pause");
	return 0;
}
