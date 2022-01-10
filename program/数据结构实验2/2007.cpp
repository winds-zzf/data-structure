#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct QNode
{
	int date;
	struct QNode* next;		//���������
}QNode, * LinkQueue;			//������н��

//�������ܣ���ʼ��ѭ�����ӣ�����ͷ��㣬�Լ�βָ�룩
Status InitQueue(LinkQueue& Q)
{
	Q = new QNode;
	if (!Q) exit(OVERFLOW);
	Q->next = Q;			//ѭ�����г�ʼʱָ���Լ�
	return OK;
}

//�������ܣ�ѭ���������
Status EnQueue(LinkQueue &Q, int e)
{
	LinkQueue pt;

	pt = new QNode;
	if (!Q) exit(OVERFLOW);
	pt->date = e;

	pt->next = Q->next;
	Q->next = pt;		//Ҫ����ǰ�������֣�Ȼ�����ƶ�Q
	Q = pt;

	return OK;
}

//�������ܣ�ѭ�����ӳ���
Status DeQueue(LinkQueue &Q, int &e)
{
	LinkQueue pt;
	if (Q->next == Q) return ERROR;				//����Ϊ��
	pt = Q->next->next; 
	if (pt != Q)		Q->next->next = pt->next;
	else
	{
		Q = Q->next;
		Q->next = Q;
	}
	e = pt->date;		//��ֵ
	return OK;
}

//�������ܣ��ж϶����Ƿ�Ϊ��
Status QueueEmpty(LinkQueue Q)
{
	return Q->next == Q ? TRUE : FALSE;
}

//���ѭ������
Status ClearQueue(LinkQueue &Q)
{
	LinkQueue pt;

	while (Q->next != Q)
	{
		pt = Q->next->next;		//�Ĵ��ƶ�ɾ��
		if (pt != Q)		Q->next->next = pt->next;
		else
		{
			Q = Q->next;
			Q->next = Q;
		}
		delete pt;
	}

	return OK;
}


int main()
{
	LinkQueue Q;
	InitQueue(Q);
	int m, n, e;

	scanf("%d%d", &m, &n);
	while (m!=0 || n!=0)
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &e);
			EnQueue(Q, e);		//��ȡ�����
		}
		for (int i = 0; i < n; i++)
		{
			DeQueue(Q, e);
			printf("%d ", e);
		}
		printf("%d\n", !QueueEmpty(Q));
		ClearQueue(Q);		//�ٴ�ʹ��ǰҪ������ղ���
		scanf("%d%d", &m, &n);
	}

	return 0;
}
