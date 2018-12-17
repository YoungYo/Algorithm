#pragma once
#include "Stack.h"

/*s：一个栈对象
  n：将要被转换的十进制数
  base：进制，若是二进制，则输入 2，若是八进制，则输入 8，以此类推*/
void convert(Stack<char> &s, __int64 n, int base) { //迭代版
	//0 < n, 1 < base <= 16，新进制下的数位符号，可视 base 取值范围适当扩充
	static char digit[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	while (n > 0) { //由低到高，逐一计算出新进制下的各数位
		s.push(digit[n % base]);//余数（当前位）入栈
		n /= base; //将 n 更新为其对 base 的除商
	}
}//新进制下由高到低的各数位，自顶而下保存在栈 s 中

//void convert(Stack<char> &s, __int64 n, int base) { //将十进制转换成其他进制，递归版
//	static char digit[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	//0 < n, 1 < base <= 16，新进制下的数位符号，可视 base 取值范围适当扩充
//	if (n > 0) { //在尚有余数之前，反复地
//		s.push(digit[n % base]); //逆向记录当前最低位，再
//		convert(s, n / base, base); //通过递归得到所有更高位
//	}
//}//新进制下由高到低的各数位，自顶而下保存在栈 s 中

/*检查表达式exp[low, high]中的括号是否匹配*/
bool paren(const char exp[], int low, int high) {
	Stack<char> S;
	while (low <= high) {
		switch (exp[low]) {
			case '(':
			case '[':
			case '{':
				S.push(exp[low]); break;
			case ')':
				if ((S.empty()) || ('(' != S.pop())) return false;
				break;
			case ']':
				if ((S.empty()) || ('[' != S.pop())) return false;
				break;
			case '}':
				if ((S.empty()) || ('{' != S.pop())) return false;
				break;
			default: break; //非括号字符一律忽略
		}
		low++;
	}
	return S.empty();
}

