#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1     //�ڴ����
#include<stdio.h>
#include<stdlib.h>
typedef int Status;
typedef struct DuLNode
{
    int date;   //���������
    struct DuLNode* prior;        //ָ��ֱ��ǰ��
    struct DuLNode* next;         //ָ��ֱ�Ӻ��
}DuLNode, * DuLinkList;

//�����������
Status ListTraverse(DuLinkList L)
{
    DuLinkList p = L->next;  //���λ��ָ��
    if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
    while (p->next)
    {
        printf("%d ", p->date);
        p = p->next;		//ָ�����
    }
    printf("%d\n", p->date);		//�������һλ�Ŀո�
    return OK;
}

//��������:����һ��˫��������巨��
Status CreateList_DuL(DuLinkList& L, int n)
{
    DuLinkList p, s;    //���λ��ָ�룬sΪ��������ָ�룬���Ǹ�ժ�½��ָ��

    L = new DuLNode;              //����˫���������ʼ��
    if (!L) exit(OVERFLOW);
    L->next = NULL; L->prior = L;
    L->date = n;

    p = L;

    for (int i = 0; i < n; i++)
    {
        s = new DuLNode;
        if (!s) exit(OVERFLOW);
        scanf_s("%d", &s->date);

        s->next = NULL;     //��巨ʼ����ĩβԪ�أ�ֱ�Ӻ�̵�ַ��Ϊ�գ�
        p->next = s;
        s->prior = p;
        p = s;
    }
    return OK;
}

//�������ܣ������ض�λ�õĽ�㣺p��p��ֱ��ǰ������λ��
Status SwapLNode(DuLinkList& L, DuLinkList p)
{
    DuLinkList pre;
    if (p == L->next) return ERROR;      //���pָ����Ԫ��㣬�������
    pre = p->prior;     //preʼ��Ϊ���λ��ָ���ֱ��ǰ��

    if (!p->next)    //��pָ������ĩβʱ��������
    {
        pre->next = NULL;
        p->next = pre;
        p->prior = pre->prior;
        pre->prior->next = p;
        pre->prior = p;
    }
    else
    {
        pre->next = p->next;    //preָ��pֱ�Ӻ��
        p->next->prior = pre;
        pre->prior->next = p;   //pָ��preֱ��ǰ��
        p->next = pre->prior;
        p->next = pre;          //����pre��p
        pre->prior = p;
    }

    return OK;
}


//�������ܣ�˫������Ĳ��ң�
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
        t = LocationDuList(L, loc);       //�Ȼ�ȡҪ��������ַ�������õ�ַ���н���
        SwapLNode(L, t);                //�������
        ListTraverse(L);                //����˫������
        scanf_s("%d", &n);
    } while (n != 0);

    return 0;
}



