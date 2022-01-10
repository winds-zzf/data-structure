#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct LNode
{
	int  date;			//结点数据域
	struct LNode* next;	//结点指针域
}LNode, * LinkList;

//线性链表初始化
Status InitList(LinkList L)
{
	L = new LNode;
	if (!L) exit(LOVERFLOW);
	L->next = NULL;
	return OK;
}

void CreateList_U(LinkList& L, int n)
{
	LinkList s, pre, q;         //s用于寄存新建结点地址，pre和q配合使用锁定插入位置

	L = new LNode;              //创建头结点；
	if (!L) exit(LOVERFLOW);
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		s = new LNode;          //新建数据结点
		if (!s) exit(LOVERFLOW);
		scanf_s("%d", &s->date);
		pre = L;                //初始化pre和q，分别指向头指针和首元结点
		q = L->next;

		while (q && q->date < s->date)
		{
			pre = q;
			q = q->next;
		}

		if (q && q->date == s->date)      //如果现重复元素，直接释放新建结点内存
		{
			delete s;
		}
		else
		{
			s->next = q;  //退出循环时，s->date正好小于q的而大于pre的
			pre->next = s;
		}
	}
}

//线性链表遍历
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //结点位置指针
	if (!L->next) return ERROR;		//遍历要判断链表是否为空
	while (p)
	{
		printf("%d ", p->date);
		p = p->next;		//指针后移
	}
	printf("\n");
	return OK;
}

//函数功能：对两个有序链表进行无重复合并
void MergeList(LinkList& LA, LinkList& LB)
{
	LinkList pa, pb, pc, pt;        //pa为链表LA的结点位置指针，pb为链表LB的结点位置指针，pc始终为新表的尾结点指针, pt（pointer temp）用于寄存待删除结点地址
	pa = LA->next; pb = LB->next;      //初始时分别指向LA， LB首元结点
	pc = LA;                //首元结点位置也要插入

	while (pa && pb)
	{
		if (pa->date < pb->date)
		{
			pc->next = pa;      //链接到较小结点
			pc = pa;            //锁定新结点
			pa = pa->next;      //移动结点位置指针
		}
		else if (pa->date > pb->date)
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
		else                //节点重复
		{
			pc->next = pa;  pc = pa;  pa = pa->next;     //以LA为母链，重复向LA靠拢

			pt = pb;  pb = pb->next; delete pt;     //删除流程：寄存->移动->删除
		}
	}
	pc->next = pa ? pa : pb;
	delete LB;      //删除LB的头结点
}

//线性链表销毁
Status DestoryList(LinkList& L)
{
	LinkList p;			//临时结点
	while (L)
	{
		p = L; L = L->next; delete p;		//寄存， 移动， 删除
	}
	return  OK;
}

int main()
{
	LinkList A, B;
	int n_A, n_B;
	scanf_s("%d%d", &n_A, &n_B);		//读入A， B的长度
	do
	{
		CreateList_U(A, n_A);			//初始化A、B链表
		CreateList_U(B, n_B); 
		MergeList(A, B);
		ListTraverse(A);
		DestoryList(A);					//A再次使用前要销毁
		scanf_s("%d%d", &n_A, &n_B);	//读入A， B的长度
	} while (n_A!=0||n_B!=0); 

	return 0;
}