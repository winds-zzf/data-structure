#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1     //内存溢出
#include<stdio.h>
#include<stdlib.h>
typedef int Status;
typedef struct DuLNode
{
    int date;   //结点数据域
    struct DuLNode* prior;        //指向直接前驱
    struct DuLNode* next;         //指向直接后继
}DuLNode, * DuLinkList;

//线性链表遍历
Status ListTraverse(DuLinkList L)
{
    DuLinkList p = L->next;  //结点位置指针
    if (!L->next) return ERROR;		//遍历要判断链表是否为空
    while (p->next)
    {
        printf("%d ", p->date);
        p = p->next;		//指针后移
    }
    printf("%d\n", p->date);		//处理最后一位的空格
    return OK;
}

//函数功能:创建一个双向链表（后插法）
Status CreateList_DuL(DuLinkList& L, int n)
{
    DuLinkList p, s;    //结点位置指针，s为新申请结点指针，或是刚摘下结点指针

    L = new DuLNode;              //创建双向空链表并初始化
    if (!L) exit(OVERFLOW);
    L->next = NULL; L->prior = L;
    L->date = n;

    p = L;

    for (int i = 0; i < n; i++)
    {
        s = new DuLNode;
        if (!s) exit(OVERFLOW);
        scanf_s("%d", &s->date);

        s->next = NULL;     //后插法始终是末尾元素，直接后继地址域为空；
        p->next = s;
        s->prior = p;
        p = s;
    }
    return OK;
}

//函数功能：交换特定位置的结点：p与p的直接前驱结点的位置
Status SwapLNode(DuLinkList& L, DuLinkList p)
{
    DuLinkList pre;
    if (p == L->next) return ERROR;      //如果p指向首元结点，则出错返回
    pre = p->prior;     //pre始终为结点位置指针的直接前驱

    if (!p->next)    //当p指向链表末尾时单独处理
    {
        pre->next = NULL;
        p->next = pre;
        p->prior = pre->prior;
        pre->prior->next = p;
        pre->prior = p;
    }
    else
    {
        pre->next = p->next;    //pre指向p直接后继
        p->next->prior = pre;
        pre->prior->next = p;   //p指向pre直接前驱
        p->next = pre->prior;
        p->next = pre;          //链接pre与p
        pre->prior = p;
    }

    return OK;
}


//函数功能：双向链表的查找：
DuLinkList LocationDuList(DuLinkList L, int i)
{
    DuLinkList p;
    p = L->next; int j = 1;

    while (p && j < i)
    {
        p = p->next;
        j++;
    }

    if (!p || j > i) return NULL;

    return p;
}

int main()
{
    DuLinkList L, t;
    int n, loc;

    scanf_s("%d", &n);
    do
    {
        CreateList_DuL(L, n);
        scanf_s("%d", &loc);
        t = LocationDuList(L, loc);       //先获取要交换结点地址，在利用地址进行交换
        SwapLNode(L, t);                //交换结点
        ListTraverse(L);                //遍历双向链表
        scanf_s("%d", &n);
    } while (n != 0);

    return 0;
}



