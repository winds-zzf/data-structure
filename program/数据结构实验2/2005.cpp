#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;			//将int取别名为Status

typedef struct
{
	char optr;	//运算符
	double opnd; //操作数
	int counter;	//用于计数才操作符找到了几个操作数
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

//已存在链栈的清空
Status ClearStack(LinkStack& S)	//链栈没有头结点，清空链栈需要修改S
{
	LinkStack p;			//临时结点指针p寄存栈顶待删除元素
	if (!S) return OK;		//S==NULL说明链空
	while (S)				//因为s是直接指向栈顶元素的，因此只要S不为空，就说明栈顶元素仍有
	{
		p = S; S = S->next; delete p;		//寄存，移动，删除
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

//非空链栈的遍历
Status StackTraverse(LinkStack S)
{
	LinkStack p = S;
	if (!S) return ERROR;
	while (p)
	{
		printf("%c\t%d\t", p->date.optr, p->date.counter);
		p = p->next;
	}
	printf("\n");
	return OK;
}

//判断已存在的链栈是否为空
Status StackEmpty(LinkStack S)
{
	return S ? 0 : 1;
}

Status ExpressionPush(LinkStack& EPSN);
Status  EvaluateExpression(double& result);
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
Status EvaluateExpression(double& result)
{	
	Object e, temp;
	Object a, theta, b;				//临时用于计算结果
	LinkStack EPSN, OPTR, OPND;		//申请三个栈分别来存储表达式，操作数， 运算符
	InitStack(EPSN);  InitStack(OPND);  InitStack(OPTR);
	
	if (!ExpressionPush(EPSN))	return ERROR;		//表达式入栈,入栈失败返回ERROR

	while (!StackEmpty(EPSN))
	{
		Pop(EPSN, e);		//从栈顶弹出一个符号
		if (!isdigit(e.optr))
		{
			e.counter = 0;		//新入栈的操作符计数值为零
			Push(OPTR, e);			//如果是运算符直接入栈
		}
		else
		{
			temp.opnd = (double)e.optr - 48;		//如果是数字字符转换为与之等大的实数
			Push(OPND, temp);
			OPTR->date.counter++;	//新栈顶元素计数值加一（栈名即是栈顶指针）
			while(!StackEmpty(OPTR)&&GetTop(OPTR).counter==2)									//栈顶操作符操作数够两个
			{
				Pop(OPTR, theta);
				Pop(OPND, a); Pop(OPND, b);		//右操作数后入栈， 先出栈
				temp.opnd = Operate(a.opnd, theta.optr, b.opnd);
				Push(OPND, temp);		//运算结果入栈
				if(!StackEmpty(OPTR))	OPTR->date.counter++;	//新栈顶元素计数值加一（栈名即是栈顶指针）
			} 
		}
	}
	result = GetTop(OPND).opnd;
	return OK;
}

//函数功能：将输入缓冲区的表达式存入EPSN栈中
Status ExpressionPush(LinkStack &EPSN)
{
	Object e;				//动态存储输入的字符
	ClearStack(EPSN);		//使用前清空栈空间
	scanf(" %c", &e.optr, 1);
	if (e.optr == '=')		return ERROR;		//如果开始就读的是'='直接错误返回
	while (e.optr != '=')
	{
		if (e.optr != ' ') Push(EPSN, e);		//只要不是空格，就入栈
		e.optr = getchar();		//处理完后再次读入一个字符
	}
	return OK;
}