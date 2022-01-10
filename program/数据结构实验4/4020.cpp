#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define MAXNUM 13			//hash表的固定长度

typedef struct HashNode
{
	int key;						//
	struct HashNode* next;	
}HashNode;				//哈希查找->链地址法结点

typedef struct
{
	HashNode** R;		//hash表基地址
	int length;			//hash表的长度
}HTable;

//对无头结点的单链表升序排序
void SortList(HashNode *L)
{
	HashNode* p, *q, *t;
	int temp;
	if (L && L->next)		//存在两个以上结点，才有必要排序
	{
		p = L; 
		while (p->next)		//链表的选择法排序
		{
			q = p->next;	//q初始为p的直接后继
			t = p;
			while (q)
			{
				if (q->key < t->key)  t = q; 
				q = q->next;
			}

			if (t != p) 
			{ 
				temp = t->key;
				t->key = p->key;
				p->key = temp;
			}					//交换t与p

			p = p->next;		//最后p指针后移
		}
	}
}

//函数功能：创建hash表
void CreateHTable(HTable &HT)
{
	int key, loc;
	HashNode* p;

	scanf_s("%d", &HT.length);					//输入数据个数
	for (int i = 0; i < MAXNUM; i++)			//初始化指针域
		HT.R[i] = NULL;

	for (int i = 0; i < HT.length; i++)
	{
		scanf_s("%d", &key);
		loc = key % MAXNUM;
		
		//插入新结点
		p = new HashNode;
		if (!p) exit(OVERFLOW);
		p->key = key;
		p->next = HT.R[loc]; HT.R[loc] = p;		//前插法

		//对无头结点的单链表升序排序
		SortList(p);
	}
}

//函数功能：哈希表值插入
void InsertHTable(HTable &HT, int key)
{
	int loc;
	HashNode* p;

	loc = key % 13;
	p = new HashNode;
	if (!p) exit(OVERFLOW);
	p->key = key;
	p->next = HT.R[loc]; HT.R[loc] = p;		//前插法

	SortList(p);
}

//函数功能：输出哈希表
void OutHTable(HTable HT)
{
	HashNode* p;
	for (int i = 0; i < 13; i++)
	{
		printf("%d", i);
		p = HT.R[i];
		while (p)
		{
			printf(" %d", p->key);
			p = p->next;
		}
		printf("\n");
	}
}

//函数功能：销毁链地址法的哈希表
void DestortyHTable(void)
{
	;
}

int main()
{
	HTable HT;
	int key;
	HT.R = new HashNode*[MAXNUM];			//HT为结点指针数组

	CreateHTable(HT);						//创建,创建时已经读入数据个数了
	while (HT.length)
	{
		scanf_s("%d", &key);
		InsertHTable(HT, key);					//插入
		OutHTable(HT);							//输出结果
		CreateHTable(HT);						//创建
	}
	
	return 0;
}