#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;			//将int取别名为Status

typedef union
{
	char optr;	//运算符
	double opnd; //操作数
}Object;

typedef struct SNode
{
	Object date;		//结点数据域
	struct SNode* next;	//结点指针域
}SNode, * LinkStack;

//链栈的初始化
Status InitStack(LinkStack& S)
{
	S = NULL;
	return OK;
}

//链栈的销毁
Status DestoryStack(LinkStack& S)
{
	LinkStack p;		//临时位置指针
	while (S)			//只要S不为空，就说明S后面还接有结点
	{
		p = S; S = S->next; delete p;		//寄存，移动.删除
	}
	return OK;
}

//链栈访问栈顶元素
Object GetTop(LinkStack S)
{
	if (S == NULL) exit(1);
	return  S->date;		//结点数据域为Object类型
}

//链栈压入栈
Status Push(LinkStack& S, Object e)
{
	LinkStack p;

	p = new SNode;		//申请一个新结点
	if (!p) exit(OVERFLOW);
	p->date = e;

	p->next = S;	S = p;
	return OK;
}

//链栈弹出栈顶元素
Status Pop(LinkStack& S, Object& e)
{
	LinkStack p;

	if (S == NULL) return ERROR;
	e = S->date;
	p = S;	S = S->next;	delete p;
	return OK;
}

Status  EvaluateExpression(double &result);
char  Precede(char top, char ch);
double Operate(double lopnd, char optr, double ropnd);

int main()
{
	double result;		//保存最终的结果

	while (EvaluateExpression(result))		//通过返回值判断计算结果是否合法， 合法则进行输出，否则不输出
	{
		printf("%.2f\n", result);
		fflush(stdin);
	} 
	return 0;
}


//函数功能根据表格比较两个运算符的优先级+ - * / = (  )
char Precede(char top, char ch)
{
	switch (ch)				//根据刚读入的字符判断应该进行何种操作
	{
	case '+':
	case '-':
		if (top == '(' || top == '=')  return '<';
		else return '>';
		break;
	case '*':
	case '/':
		if (top == '*' || top == '/' || top == ')') return '>';
		else return '<';
		break;
	case '(':
		if (top == ')') return 'e';		//表示出错
		else return '<';
		break;
	case ')':
		if (top == '(')			return '=';
		else if (top == '=')	return 'e';
		else					return '>';
		break;
	case '=':
		if (top == '=')			return '=';
		else if(top == '(')		return 'e';
		else					return '>';
		break;
	default:
		return 'e';
	}
}

//函数功能：对两个double类型数据按照相应运算符进行运算
double Operate(double lopnd, char optr, double ropnd)
{
	double result = 0;		//实数运算结果
	switch (optr)
	{
	case '+':
		result = lopnd + ropnd;
		break;
	case '-':
		result = lopnd - ropnd;
		break;
	case '*':
		result = lopnd * ropnd;
		break;
	case '/':
		if (ropnd == 0) exit(1);		//发生除零错误，直接退出
		result = lopnd / ropnd;
		break;
	default:
		break;
	}
	return result;						//最后集中返回计算结果
}
//函数功能：表达式求值算法（表达式以#结尾）
Status EvaluateExpression(double &result)
{
	char ch;
	Object a, theta, b;			//用于运算时临时使用
	Object e, waste;			//e用于存储输入的数据，有数据覆盖的风险,waste用于表示待丢弃的数

	LinkStack OPND, OPTR;	//分别为操作数栈，运算符栈
	InitStack(OPND);
	InitStack(OPTR);
	
	e.optr = '=';	Push(OPTR, e);	//将'='压入栈底
	
	scanf(" %c", &ch, 1);							//初始读取一个字符作为开始条件,首次读取忽略空白字符的输入
	if (ch == '=') return FALSE;			//首个读取的就是=直接错误返回

	while (ch != '=' || GetTop(OPTR).optr != '=')			//当输入不为结束符“=”或者栈顶不为等号时，一直输入
	{
		if (isdigit(ch))
		{
			int flag = 1;				//flag作为标记当遇到小数点时改为0
			double temp = 0.1; e.opnd = 0; ;	//读取数初始化辅助变量
			do
			{
				if (flag)	e.opnd = e.opnd * 10 + (int)ch - 48;
				else
				{
					e.opnd = e.opnd + ((double)ch - 48) * temp;
					temp /= 10;				//每处理完一个小数temp除以10作为下一位的权
				}
				ch = getchar();					//读取下一个符号

				if (ch == '.')
				{
					flag = 0;		//当遇到小数点时flag标记为0, 并重新读入一个字符
					ch = getchar();
				}
			} while (isdigit(ch));		//循环结束时当前符号不是数字字符
			Push(OPND, e);	//将转换到的数存入操作数栈
		}
		else
		{
			switch (Precede(GetTop(OPTR).optr, ch))				//比较栈顶元素与读入字符的优先级
			{
			case '<':
				e.optr = ch;
				Push(OPTR, e);
				ch = getchar();			//读取下一个字符
				break;
			case '>':					//在进行运算的情况下是不读取新数据的
				Pop(OPTR, theta); 
				Pop(OPND, b); Pop(OPND, a);			//由于是栈，因此先出来的是右操作数b
				waste.opnd = Operate(a.opnd, theta.optr, b.opnd);		//对取出的两个数进行运算
				Push(OPND, waste);		//将计算结果压入操作数栈
				break;
			case '=':
				Pop(OPTR, waste);		//栈顶元素出栈
				ch = getchar();			//再次读取一个元素
				break;
			default:
				break;
			}
		}
	}
	 result = GetTop(OPND).opnd;		//返回存在于栈顶的结果
	 DestoryStack(OPND); DestoryStack(OPTR);
	 return OK;
}