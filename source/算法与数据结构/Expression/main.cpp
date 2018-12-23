/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#include <iostream>
using namespace std;

#include "parentheses.h"
#include "convert.h"
#include "evaluate.h"

int main() {

	char k[] = "{ ( ) [ ( { } ) ] }";
	
	bool res = checkParen(k, 0, 19);
	if (res)
		cout << "true" << endl;
	else
		cout << "false" << endl;


	//char S[] = "(0! + 1) * 2 ^ (3 ! + 4) - ( 5 ! - 67 - ( 80 + 90 ) )";
	//char S[] = "0 + ( 1 + 23 )/ 4 * 5 * 67 - 8 + 9";
	char S[] = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";

	char* RPN = ( char* ) malloc ( sizeof ( char ) * 1 );   
	RPN[0] = '\0'; //逆波兰表达式
	char* RPN1 = ( char* ) malloc ( sizeof ( char ) * 1 );   
	RPN1[0] = '\0'; //逆波兰表达式
	in2rpn(S, RPN1);
	cout << RPN1 << endl;

	cout << evaluate(S, RPN) << endl;
	cout << RPN << endl;
	//cout << optr2rank('+') << endl;
	cout << evaluate(RPN) << endl;
	system("pause");
	return 0;
}
