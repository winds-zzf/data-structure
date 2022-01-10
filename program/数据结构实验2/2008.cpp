#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define QMAXSIZE 100
#include<stdio.h>
#include<stdlib.h>
typedef int Status;

typedef struct
{
	int* base;			//ѭ�����л���ַ
	int front, rear;	//����ͷָ�룬βָ��
	int tag;			//��Ƕ��еĿջ�����
}SqQueue;

//�������ܣ���ʼ��ѭ������
Status InitQueue(SqQueue& Q)
{
	Q.base = new int[QMAXSIZE];
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;			//ͷβָ���ʼ��ָ��������Ԫ��
	Q.tag = 0;	//tagΪ���ʾΪ��˳���
	return OK;
}

//�������ܣ�ѭ���������
Status EnQueue(SqQueue& Q, int e)
{
	if (Q.tag) return ERROR;		//ջ��tagΪ1

	if ((Q.rear + 1) % QMAXSIZE == Q.front) Q.tag = 1;		//������ǰ����һ��λ�ã��������ӣ�������Ӽ���
	Q.base[Q.rear] = e;		//��βָ��ָ���βԪ����һλ
	Q.rear = (Q.rear + 1) % QMAXSIZE;

	return OK;
}

//�������ܣ�ѭ�����г���
Status DeQueue(SqQueue& Q, int& e)
{
	if (Q.tag == 0) return ERROR;

	if ((Q.front + 1) % QMAXSIZE == Q.rear)		Q.tag = 0;//ͷָ�����һλ������βָ���غϣ�˵��ֻʣһ��Ԫ�أ�ɾ������
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % QMAXSIZE;
	return OK;
}
//�������ܣ��ж϶����Ƿ�Ϊ��
Status QueueEmpty(SqQueue Q)
{
	return !Q.tag;
}

//�������ܣ�����ѭ������
Status TraverseQueue(SqQueue Q)
{
	int p;

	p = Q.front;	//��ʼʱָ��ͷָ��λ��
	while ((p + 1) % QMAXSIZE != Q.rear)
	{
		printf("%d ", Q.base[p]);
		p = (p + 1) % QMAXSIZE;		//��ѭ��������ָ��λ��
	}
	printf("%d\n", Q.base[p]);
	return OK;
}

//���ѭ������
Status ClearQueue(SqQueue& Q)
{
	Q.tag = 0;				//�����Ϊ��
	Q.front = Q.rear = 0;	//�ָ�ͷβָ��
	return OK;
}

int main()
{
	int m, e;
	SqQueue Q;
	InitQueue(Q);

	scanf("%d", &m);
	while (m)
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &e);
			EnQueue(Q, e);		//���벢��ջ
		}
		TraverseQueue(Q);
		ClearQueue(Q);		//�ٴ�ʹ��ǰ��ն���
		scanf("%d", &m);
	}

	return 0;
}
