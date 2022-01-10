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
    if (L->next == L) return ERROR;		//遍历要判断链表是否为空（头结点指向自己L->next == L）
    while (p->next != L)
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
    L->next = L; L->prior = L;
    L->date = n;

    p = L;

    for (int i = 0; i < n; i++)
    {
        s = new DuLNode;        //申请并初始化新结点
        if (!s) exit(OVERFLOW);
        scanf_s("%d", &s->date);

        L->prior = s;       //先连接头和尾，再链接内部连线
        s->next = L;     //后插法始终是末尾元素，直接后继地址域为空；
        p->next = s;
        s->prior = p;
        p = s;
    }
    return OK;
}

//基于双向链表的双向冒泡排序
void Bubble_Sort_Dul(DuLinkList L)
{
    DuLinkList head, rear;      //头尾两个标记指针，用于标记冒泡终止条件,rear后面，head前面均为已确定的结点
    DuLinkList p;               //工作指针，表示当前正在处理的结点位置
    int temp;                   //Swap()临时变量

    head = L->next;             //初始化head指向首元结点，rear指向尾结点
    rear = L->prior;
    p = head;                   //按照先正序后逆序的顺序交替冒泡
    while (head != rear)        //当头尾结点相遇时，指针位置两侧结点全部已确定，则中间结点自然必然确定，排序结束
    {
        while (p != rear)       //
        {

            if (p->date > p->next->date)      //逆序：左大于右
            {
                temp = p->date; p->date = p->next->date; p->next->date = temp;      //交换相邻逆序结点
            }
            p = p->next;        //指针后移
        }
        p = rear = rear->prior; //
        if (head == rear) break;
        while (p != head)       //
        {
            if (p->prior->date > p->date)     //逆序：左大于右
            {
                temp = p->date; p->date = p->prior->date; p->prior->date = temp;      //交换相邻逆序结点
            }
            p = p->prior;       //指针前移
        }
        p = head = head->next;  //
    }
}

int main()
{
    DuLinkList L, t;
    int n, loc;

    scanf_s("%d", &n);
    while (n)
    {
        CreateList_DuL(L, n);

        Bubble_Sort_Dul(L);

        ListTraverse(L);                //遍历双向链表
        scanf_s("%d", &n);
    }

    return 0;
}



