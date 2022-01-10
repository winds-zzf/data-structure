#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct
{
	int top[2], base[2];	//栈顶，栈底指针
	int *V;					//栈数组名,指针
	int stacksize;			//栈可用最大容量
}SqStack;		//定义一个类型为SqStack的顺序栈

//函数功能：初始化双向顺序栈
Status InitDuStack(SqStack &S, int m)
{
	S.V = new int[m];		//申请大小为m的数组空间
	if (!S.V) exit(OVERFLOW);

	S.top[0] = -1; S.base[0] = 0;
	S.top[1] = m; S.base[1] = m-1;
	S.stacksize = m;		//顺序栈可用最大容量为m
	return OK;
}

//函数功能：双栈入栈(select表示栈的选择栈0或栈1)
Status Push(SqStack &S, int e, int select)
{
	if (S.top[0] + 1 == S.top[1]) return ERROR;
	if (select)		//选择栈1
	{
		S.V[--S.top[1]] = e;
	}
	else			//选择栈0
	{
		S.V[++S.top[0]] = e;
	}
	return OK;
}

//函数功能：双栈出栈
Status Pop(SqStack &S, int &e, int select)
{
	if (select)		//选择栈1
	{
		if (S.top[1]-1== S.base[1]) return ERROR;
		e = S.V[S.top[1]++];
	}
	else			//选择栈0
	{
		if (S.top[0]+1 == S.base[0]) return ERROR;
		e = S.V[S.top[0]--];
	}
	return OK;
}

//函数功能：判断栈空
Status StackEmpty(SqStack S, int select)
{
	if (select)		//选择栈1
	{
		if (S.top[1] - 1 == S.base[1]) return TRUE;
		else return FALSE;
	}
	else			//选择栈0
	{
		if (S.top[0] + 1 == S.base[0]) return TRUE;
		else return FALSE;
	}
	return OK;
}

//函数功能：清空双栈
Status ClearStatck(SqStack &S)
{
	if (!S.V) return OK;
	delete S.V; S.V = NULL;	//释放申请的内存空间，并初始化数组指针
	return OK;
}

//函数功能：判断是否栈栈满
Status StackFull(SqStack S)		
{
	if (S.top[0] + 1 == S.top[1]) return TRUE;
	else return FALSE;
}

int main()
{
	int m, e;
	int e0, e1, d0, d1;
	SqStack S;			//定义一个双栈

	scanf("%d", &m);
	do
	{		
		InitDuStack(S, m);
		scanf("%d%d%d%d", &e0, &e1, &d0, &d1);
		for (int i = 0; i < e0; i++)		//读入
		{
			scanf("%d", &e);
			Push(S, e, 0);
		}
		for (int i = 0; i < e1; i++)
		{
			scanf("%d", &e);
			Push(S, e, 1);
		}
		printf("%d\n", StackFull(S));		//栈满？

		for (int i = 0; i <d0; i++)			//删除
		{
			Pop(S, e, 0);
			printf("%d ", e);
		}
		printf("%d\n", !StackEmpty(S, 0));		//栈空？

		for (int i = 0; i < d1; i++)
		{
			Pop(S, e, 1);
			printf("%d ", e);
		}
		printf("%d\n", !StackEmpty(S, 1));		//栈空？

		ClearStatck(S);
		scanf("%d", &m);
	} while (m);



	return 0;
}