/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/

#include <iostream>
using namespace std;

#include "convert.h"

int main() {
	Stack<char> s;
	convert(s, 8, 2);
	while (s.empty() == false) {
		cout << s.pop();
	}

	system("pause");
}
