/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#pragma once
#include "Stack.h"
#include "rpn.h"
#include <iostream>
using namespace std;

float evaluate ( char* S, char*& RPN ) { //对（已剔除白空格的）表达式S求值，并转换为逆波兰式RPN
   Stack<float> opnd; Stack<char> optr; //运算数栈、运算符栈 /*DSA*/任何时刻，其中每对相邻元素之间均大小一致
   S = removeSpace(S); //剔除 S 中多余的空格
   optr.push ( '\0' ); //尾哨兵'\0'也作为头哨兵首先入栈
   while ( !optr.empty() ) { //在运算符栈非空之前，逐个处理表达式中各字符
      if ( isdigit ( *S ) ) { //若当前字符为操作数，则
         readNumber ( S, opnd ); append ( RPN, opnd.top() ); //读入操作数，并将其接至RPN末尾
      } else //若当前字符为运算符，则
         switch ( orderBetween ( optr.top(), *S ) ) { //视其与栈顶运算符之间优先级高低分别处理
            case '<': //栈顶运算符优先级更低时
               optr.push ( *S ); S++; //计算推迟，当前运算符进栈
               break;
            case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
               optr.pop(); S++; //脱括号并接收下一个字符
               break;
            case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
               char op = optr.pop(); append ( RPN, op ); //栈顶运算符出栈并续接至RPN末尾
               if ( '!' == op ) { //若属于一元运算符
                  float pOpnd = opnd.pop(); //只需取出一个操作数，并
                  opnd.push ( calcu ( op, pOpnd ) ); //实施一元计算，结果入栈
               } else { //对于其它（二元）运算符
                  float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //取出后、前操作数 /*DSA*/提问：可否省去两个临时变量？
                  opnd.push ( calcu ( pOpnd1, op, pOpnd2 ) ); //实施二元计算，结果入栈
               }
               break;
            }
            default : exit ( -1 ); //逢语法错误，不做处理直接退出
         }//switch
   }//while
   return opnd.pop(); //弹出并返回最后的计算结果
}

float evaluate(char*& RPN) {
	Stack<float> opnd;
	readNumber(RPN, opnd); //后缀表达式开头肯定是一个数
	while (true) {
		if (isspace(*RPN)) RPN++; //如果是空格，就继续读取下一个字符
		else if (isdigit(*RPN)) readNumber(RPN, opnd); //如果是数字，就读取数字
		else if (0 <= optr2rank(*RPN) && optr2rank(*RPN) <=  optr2rank ('!')) { 
			if (*RPN == '!') {
				float pOpnd = opnd.pop();
				opnd.push(calcu(*RPN, pOpnd)); //如果是一元操作符，就令栈顶出栈
				RPN++;
			}
			else { //否则，就令栈顶和次栈顶出栈
				float pOpnd2 = opnd.pop(); 
				float pOpnd1 = opnd.pop();
				opnd.push(calcu(pOpnd1, *RPN, pOpnd2));
				RPN++;
			}
		}
		else if (*RPN == '\0') { //遇到空字符，说明到达结尾，退出循环
			break;
		}
	}
	return opnd.pop(); //最后返回栈顶元素
}

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
