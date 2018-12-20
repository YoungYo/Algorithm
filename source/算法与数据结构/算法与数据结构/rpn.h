/******************************************************************************************
 * 如果你对代码有什么疑问，可以关注微信公众号：AProgrammer
 * 或者添加作者微信：91395421
 * 我会免费为你解答
 ******************************************************************************************/
#pragma once
#include <math.h>
#include <cstring>

#define N_OPTR 9 //运算符总数

typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
   /*              |-------------------- 当 前 运 算 符 --------------------| */
   /*              +      -      *      /      ^      !      (      )      \0 */
   /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
   /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
   /* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
   /* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
   /* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
   /* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
   /* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
   /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
   /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

Operator optr2rank ( char op ) { //由运算符转译出编号
   switch ( op ) {
      case '+' : return ADD; //加
      case '-' : return SUB; //减
      case '*' : return MUL; //乘
      case '/' : return DIV; //除
      case '^' : return POW; //乘方
      case '!' : return FAC; //阶乘
      case '(' : return L_P; //左括号
      case ')' : return R_P; //右括号
      case '\0': return EOE; //起始符与终止符
      default  : exit ( -1 ); //未知运算符
   }
}

char orderBetween ( char op1, char op2 ) //比较两个运算符之间的优先级
{ return pri[optr2rank ( op1 ) ][optr2rank ( op2 ) ]; }

void readNumber ( char*& p, Stack<float>& stk ) { //将起始于p的子串解析为数值，并存入操作数栈
   stk.push ( ( float ) ( *p - '0' ) ); //当前数位对应的数值进栈
   while ( isdigit ( * ( ++p ) ) ) //只要后续还有紧邻的数字（即多位整数的情况），则
      stk.push ( stk.pop() * 10 + ( *p - '0' ) ); //弹出原操作数并追加新数位后，新数值重新入栈
   if ( '.' != *p ) return; //此后非小数点，则意味着当前操作数解析完成
   float fraction = 1; //否则，意味着还有小数部分
   while ( isdigit ( * ( ++p ) ) ) //逐位加入
      stk.push ( stk.pop() + ( *p - '0' ) * ( fraction /= 10 ) ); //小数部分
}

void append ( char*& rpn, float opnd ) { //将操作数接至RPN末尾
   int n = strlen ( rpn ); //RPN当前长度（以'\0'结尾，长度n + 1）
   char buf[64];
   if ( opnd != ( float ) ( int ) opnd ) sprintf ( buf, "%.2f \0", opnd ); //浮点格式，或
   else                          sprintf ( buf, "%d \0", ( int ) opnd ); //整数格式
   rpn = ( char* ) realloc ( rpn, sizeof ( char ) * ( n + strlen ( buf ) + 1 ) ); //扩展空间
   strcat ( rpn, buf ); //RPN加长
}

void append(char*& rpn, char*& infix) {
    int n = strlen ( rpn ); //RPN当前长度（以'\0'结尾，长度n + 1）
	char buf[64];
	int i = 0;
	while (isdigit(*infix) || '.' == *infix) {
		buf[i++] = *infix;
		infix++;
	}
	buf[i++] = ' ';
	buf[i] = '\0';
    rpn = ( char* ) realloc ( rpn, sizeof ( char ) * ( n + strlen ( buf ) + 1 ) ); //扩展空间
    strcat ( rpn, buf ); //RPN加长
}

void append ( char*& rpn, char optr ) { //将运算符接至RPN末尾
   int n = strlen ( rpn ); //RPN当前长度（以'\0'结尾，长度n + 1）
   rpn = ( char* ) realloc ( rpn, sizeof ( char ) * ( n + 3 ) ); //扩展空间
   sprintf ( rpn + n, "%c ", optr ); rpn[n + 2] = '\0'; //接入指定的运算符
}

int  facI(int n) { //计算 n 的阶乘
	int res = 1;
	if (n == 0)
		return res;
	while (n > 0) {
		res *= n--;
	}
	return res;
}

float calcu ( float a, char op, float b ) { //执行二元运算
   switch ( op ) {
      case '+' : return a + b;
      case '-' : return a - b;
      case '*' : return a * b;
      case '/' : if ( 0==b ) exit ( -1 ); return a/b; //注意：如此判浮点数为零可能不安全
      case '^' : return pow ( a, b );
      default  : exit ( -1 );
   }
}

float calcu ( char op, float b ) { //执行一元运算
   switch ( op ) {
      case '!' : return ( float ) facI ( ( int ) b ); //目前仅有阶乘，可照此方式添加
      default  : exit ( -1 );
   }
}

char* removeSpace ( char* s ) { //剔除s[]中的白空格
   char* p = s, *q = s;
   while ( true ) {
      while ( isspace ( *q ) ) q++;
      if ( '\0' == *q ) { *p = '\0'; return s; }
      *p++ = *q++;
   }
}

/*中缀表达式转换成后缀表达式*/
void in2rpn(char* infix, char*& RPN) {
	Stack<char> optr; //存放操作符的栈
	optr.push('\0');
	while (!optr.empty()) { //当运算符栈非空时，逐个处理表达式中的各字符
		if (isspace(*infix)) infix++; //遇到空格，直接忽略，读取下一个字符
		else if (isdigit(*infix)) { //若当前字符为操作数，则
			append(RPN, infix); //直接追加至RPN末尾
		}
		else { //若遇到操作符，则
			switch (orderBetween(optr.top(), *infix)) { //将栈顶操作符与当前操作符作对比
				case '<': //若栈顶操作符优先级小于当前操作符的优先级
					optr.push(*infix); infix++; break; //则将当前操作符入栈
				case '=': //若栈顶操作符的优先级等于当前操作符的优先级（此时只可能是遇到了括号）
					optr.pop(); infix++; break; //则直接将栈顶操作符弹出，并接收下一字符
				case '>': //若栈顶操作符的优先级大于当前操作符的优先级
					append(RPN, optr.pop()); break; //则将栈顶操作符追加至RPN末尾，并继续拿当前操作符与新的栈顶操作符相比较
				default: //若遇到非法字符，直接退出程序
					exit(-1);
			}
		}
	}
}
