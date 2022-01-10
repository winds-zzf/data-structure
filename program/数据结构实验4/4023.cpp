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
    if (L->next == L) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ�գ�ͷ���ָ���Լ�L->next == L��
    while (p->next != L)
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
    L->next = L; L->prior = L;
    L->date = n;

    p = L;

    for (int i = 0; i < n; i++)
    {
        s = new DuLNode;        //���벢��ʼ���½��
        if (!s) exit(OVERFLOW);
        scanf_s("%d", &s->date);

        L->prior = s;       //������ͷ��β���������ڲ�����
        s->next = L;     //��巨ʼ����ĩβԪ�أ�ֱ�Ӻ�̵�ַ��Ϊ�գ�
        p->next = s;
        s->prior = p;
        p = s;
    }
    return OK;
}

//����˫�������˫��ð������
void Bubble_Sort_Dul(DuLinkList L)
{
    DuLinkList head, rear;      //ͷβ�������ָ�룬���ڱ��ð����ֹ����,rear���棬headǰ���Ϊ��ȷ���Ľ��
    DuLinkList p;               //����ָ�룬��ʾ��ǰ���ڴ���Ľ��λ��
    int temp;                   //Swap()��ʱ����

    head = L->next;             //��ʼ��headָ����Ԫ��㣬rearָ��β���
    rear = L->prior;
    p = head;                   //����������������˳����ð��
    while (head != rear)        //��ͷβ�������ʱ��ָ��λ��������ȫ����ȷ�������м�����Ȼ��Ȼȷ�����������
    {
        while (p != rear)       //
        {

            if (p->date > p->next->date)      //�����������
            {
                temp = p->date; p->date = p->next->date; p->next->date = temp;      //��������������
            }
            p = p->next;        //ָ�����
        }
        p = rear = rear->prior; //
        if (head == rear) break;
        while (p != head)       //
        {
            if (p->prior->date > p->date)     //�����������
            {
                temp = p->date; p->date = p->prior->date; p->prior->date = temp;      //��������������
            }
            p = p->prior;       //ָ��ǰ��
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

        ListTraverse(L);                //����˫������
        scanf_s("%d", &n);
    }

    return 0;
}



