#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;	//将int取别名为Status


typedef struct SNode	//S为Stack所以是栈结点Stack Node
{
	int date;			//链栈结点数据域
	struct SNode* next;	//链栈结点指针域
}SNode, * LinkStack;

//链栈的初始化：创建一个空链栈
Status InitStack(LinkStack& S)	//S是指向SNode结点的指针因此应该是结构体指针类型LinkStack
{
	S = NULL;		//由于没有头结点，因此直接令头指针为空，表示空链栈
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

//非满链栈入栈
Status Push(LinkStack& S, int e)
{
	LinkStack p;	//临时栈结点指针
	p = new SNode;
	if (!p) exit(OVERFLOW);
	p->date = e;

	p->next = S;
	S = p;

	return OK;
}

//非空链栈弹出栈顶元素
Status Pop(LinkStack& S, int &e)
{
	LinkStack p;
	if (!S) return ERROR;
	e = S->date;
	p = S;	S = S->next; delete p;
	return OK;
}


int main()
{
	int m, e;
	LinkStack S;
	InitStack(S);

	scanf("%d", &m);
	while (m)		//当输入为0是停止
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &e);
			if (e == -1)
			{
				if (Pop(S, e))	printf("%d\n", e);		//出栈正常，输出结果
				else
				{
					printf("POP ERROR\n");				//出栈异常，返回错误提示
					while (getchar() != '\n') ;			//清空本组剩余项
					break;
				}
			}
			else
			{
				Push(S, e);
			}
		}

		scanf("%d", &m);		//再次读取
		ClearStack(S);				//再次使用前清空栈空间
	}

	return 0;
}