#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;
typedef struct
{
	char ch;	//�洢�ַ�
	int num;	//�洢�ַ����ִ���
}Symbol;			//����Symbol���ͽṹ������洢�鼮��Ϣ
typedef struct LNode
{
	Symbol date;			//���������
	struct LNode* next;	//���ָ����
}LNode, * LinkList;
//���������ʼ��
Status InitList(LinkList& L)
{
	L = new LNode;		//�����½ڵ���Ϊͷ���
	if (!L) exit(LOVERFLOW);

	L->next = NULL;	//�ձ�ָ����Ϊ��
	return OK;
}

//������������
Status DestoryList(LinkList& L)
{
	LinkList p;			//��ʱ���
	while (L)
	{
		p = L; L = L->next; delete p;		//�Ĵ棬 �ƶ��� ɾ��
	}
	return  OK;
}

//������������
Status CreateList_U(LinkList& L)
{
	LinkList pre, q, t;  //��λָ�룬 ��ʱָ��
	Symbol e;		//�洢�������

	L = new LNode; if (!L) exit(LOVERFLOW); L->next = NULL;		//����һ���ձ�

	scanf(" %c", &e.ch, 1);
	if (e.ch == '0') return ERROR;		//����'0'ʱֱ�ӷ���ERROR

	while(e.ch != '\n')	//��������ʱ�˳�
	{
		pre = L; q = L->next;		//��ÿһ���������ǰ����ʼ��λ��ָ��

		e.num = 1;		//�´�����Ԫ�ؼ���Ϊ1
		while (q && q->date.ch < e.ch)
		{
			pre = q; q = q->next;		//λ��ָ�����
		}
		if (q && q->date.ch == e.ch)
		{
			q->date.num++;		//�������ظ��ַ�ʱ��������һ�������ݲ�����
		}
		else
		{
			t = new LNode; if (!t) exit(LOVERFLOW); t->date = e;	//�����½�㲢��ʼ����
			pre->next = t; t->next = q;		//�����½��
		}
		e.ch = getchar();		//��ȡ��һ���ַ�
	}
	return OK;
}

//�����������
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //���λ��ָ��
	if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
	while (p)
	{
		printf("%c:%d\n", p->date.ch, p->date.num);
		p = p->next;		//ָ�����
	}
	return OK;
}

//�������ܣ����������ݽ�����������
int main()
{
	LinkList L;

	while (CreateList_U(L))
	{
		ListTraverse(L);
		DestoryList(L);		//�����ֱ�����٣� ��һ�����½���
	}
	return 0;
}