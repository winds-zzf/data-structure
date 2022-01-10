#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef int Status;			//将int取别名为Status

typedef struct SNode
{
	char date;		//结点数据域
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
char GetTop(LinkStack S)
{
	if (S == NULL) exit(1);
	return  S->date;		//结点数据域为Object类型
}

//链栈压入栈
Status Push(LinkStack& S, char e)
{
	LinkStack p;

	p = new SNode;		//申请一个新结点
	if (!p) exit(OVERFLOW);
	p->date = e;

	p->next = S;	S = p;
	return OK;
}

//链栈弹出栈顶元素
Status Pop(LinkStack& S, char& e)
{
	LinkStack p;

	if (S == NULL) return ERROR;
	e = S->date;
	p = S;	S = S->next;	delete p;
	return OK;
}

//判断已存在的链栈是否为空
Status StackEmpty(LinkStack S)
{
	return S ? 0 : 1;
}

char  Precede(char top, char ch);
Status TransferExpression(void);

int main()
{

	while (TransferExpression())		//通过返回值判断计算结果是否合法， 合法则进行输出，否则不输出
	{
		while(getchar() !='\n') ;
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
		if (top == '(')  return '<';
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
		else					return '>';
		break;
	default:
		return 'e';
	}
}

//函数功能：中缀表达式后缀表达式算法（表达式均以=结尾）
Status TransferExpression(void)
{
	char ch, e;
	LinkStack OPTR;			//仅仅需要一个操作符栈，操作数直接输出
	InitStack(OPTR);
	scanf(" %c", &ch, 1);
	if (ch == '=') return ERROR;		//首字母为等号，直接退出

	while (ch != '=')
	{
		if (isdigit(ch))
		{
			printf("%c", ch);		//读入操作数直接输出
		}
		else
		{
			if (ch == ')')					//当读到),操作符出栈，直到栈顶为左括号
			{
				while (GetTop(OPTR) != '(')
				{
					Pop(OPTR, e);
					printf("%c", e);
				}
				Pop(OPTR, e);		//舍弃栈顶元素：(
			}
			else							//读到其他操作符，不是大于就是小于，不可能为等于
			{
				while (!StackEmpty(OPTR) && Precede(GetTop(OPTR), ch) == '>')
				{
					Pop(OPTR, e);		//弹出栈顶元素，并输出，直到遇到比自己优先级低的位置
					printf("%c", e);	//输入的字符是要最后入栈的，为了防止被覆盖，不应该使用ch接收字符
				}
				Push(OPTR, ch);			//循环结束后自身入栈
			}
		}

		ch = getchar();
	}
	while (!StackEmpty(OPTR))		//遇到等于时，一直出栈
	{
		Pop(OPTR, e);
		printf("%c", e);
	}
	printf("\n");		//输出结束符'='
	return OK;
}