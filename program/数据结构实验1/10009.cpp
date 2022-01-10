#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LMAXSIZE 200
typedef int Status;
typedef struct
{
	char bookNum[15];	//书号
	char bookName[40];	//书名
	float bookPrice;	//书籍价格
}Book;			//定义Book类型结构体变量存储书籍信息
typedef struct
{
	Book* base;		//顺序表数组基地址
	int length;		//顺序表表长
}SqList;		//定义一个名为SqList的顺序表

//结构体数组数据输入
void Input(Book& e)
{
	scanf("%s%s%f",
		e.bookNum, 15,
		e.bookName, 40,
		&e.bookPrice
	);
}

//结构体数组数据输出
void Output(Book e)
{
	printf("%s %s %.2f\n",
		e.bookNum,
		e.bookName,
		e.bookPrice
	);
}

//顺序表的初始化
Status InitList(SqList& L)
{
	L.base = new Book[LMAXSIZE];	//为顺序链表申请长为LMAXSIZE的存储空间
	if (!L.base) exit(OVERFLOW);

	L.length = 0;		//空表长度为零
	return OK;
}

//线性表的删除
Status ListDelete(SqList& L, int i)
{
	int j;
	if (i<1 || i>L.length)  return ERROR;
	for (j = i - 1; j < L.length; j++)
	{
		L.base[j] = L.base[j + 1];
	}
	L.length--;
	return OK;
}


//顺序表的遍历
Status ListTraverse(SqList L)
{
	if (!L.length) return ERROR;
	for (int i = 0; i < L.length; i++)
	{
		Output(L.base[i]);
	}
	return OK;
}

int main()
{
	Book e;		//book类型变量存储书籍信息
	SqList L;
	int location;
	InitList(L);
	scanf("%d", &L.length);		//读入的长度直接修改L.length

	for (int i = 0; i < L.length; i++)
	{
		Input(e);
		L.base[i] = e;
	}

	scanf("%d", &location);	//读入结点位置
	if (ListDelete(L, location))	//输入插入结点
	{
		ListTraverse(L);
	}
	else
	{
		printf("Sorry，the position to be deleted is invalid!\n");
	}
	return 0;
}