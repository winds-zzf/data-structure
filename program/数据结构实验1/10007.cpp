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

//比较两个结构体是否相同
Status BookCmp(Book elem_1, Book elem_2)
{
	if (!strcmp(elem_1.bookNum, elem_2.bookNum))
	{
		if (!strcmp(elem_1.bookName, elem_2.bookName))
		{
			if (fabs((double)elem_1.bookPrice - (double)elem_2.bookPrice) < 0.0001)
				return OK;
		}
	}
	return ERROR;
}
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
//顺序表的插入:插入在指定位置，序号（非下表）
Status InsertElem(SqList& L, int i, Book e)
{
	if (i<1 || i>L.length + 1) return ERROR;
	if (L.length == LMAXSIZE) return ERROR;

	for (int j = L.length - 1; j >= i - 1; j--)
	{
		L.base[j + 1] = L.base[j];
	}
	L.base[i - 1] = e;		//第i个位置插入，下标为i-1
	L.length++;
	return OK;
}

//顺序表的取值（i为序号，下标加一）
Status GetElem(SqList L, int i, Book& e)
{
	if (i < 1 || i>L.length)  return ERROR;  //所给序号超出范围1~L.length
	e = L.base[i - 1];			//第i个元素序号为i-1
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
	int times, location;
	InitList(L);
	scanf("%d", &L.length);		//读入的长度直接修改L.length

	for (int i = 0; i < L.length; i++)
	{
		Input(e);
		L.base[i] = e;
	}
	scanf("%d", &times);		//读取查找次数
	for (int i = 0; i < times; i++)
	{
		scanf("%d", &location);		//读取喜爱的书名
		if (GetElem(L, location, e))	Output(e);				//进行相应的查找
		else printf("Sorry，the book on the best position doesn't exist!\n");
	}
	return 0;
}