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
}SqQueue;

//��ʼ�����У�����һ����˳���
Status InitQueue(SqQueue& Q)
{
	Q.base = new int[QMAXSIZE];	//����һ������ΪMAXSize��˳����У����洢���Ļ���ַ
	if (!Q.base) exit(OVERFLOW);	//�ڴ�����ʧ�ܣ��˳�����
	Q.front = Q.rear = QMAXSIZE - 1;  //�ն���ͷβָ�붼Ϊ�㣬�������ν��ָ��ȫ�������±�ֻ������ͬ�±�ָ���ض�����Ԫ�ذ���
	return OK;		//�ɹ� ����
}

//���һ���Ѵ���˳���
Status ClearQueue(SqQueue& Q)
{
	Q.front = Q.rear = QMAXSIZE - 1;	//���ֻ������ͷβָ��Ϊ��ʼ״̬��ע��������ѭ�����У�������ձ���ȫ����ʼ��Ϊ��
	return OK;
}

// ˳������
Status EnQueue(SqQueue& Q, int e)
{
	if (Q.rear == (Q.front - 1 + QMAXSIZE) % QMAXSIZE) return ERROR;//�������ָ����ƶ�Ҫ����ģ���㣬��Ϊ��������ģ��
	Q.base[Q.front] = e;									//�ṹ���������ֱ�ӽ��и�ֵ
	Q.front = (Q.front - 1 + QMAXSIZE) % QMAXSIZE;					//���ڴ���ģ������ÿ��һ����Ҫȡ�࣬���Ҫ��������ȡ�����㣬���ɺϲ�
	return OK;
}

// ˳��ӳ���
Status DeQueue(SqQueue& Q, int& e)
{
	if (Q.front == Q.rear) return ERROR;		//����ѭ�����в���Ϊ�գ�
	e = Q.base[Q.rear];					//ȡ�ṹ�������ͷԪ�أ�����
	Q.rear = (Q.rear - 1 + QMAXSIZE) % QMAXSIZE;		//ѭ�������ǵ����������ͷβָ��ֻ������ƶ����������Ǿ���ģ�����㣬ֻҪ���Ӿ�Ҫȡ��
	return OK;
}

// �����Ѿ����ڵ�˳���
Status QueueTraverse(SqQueue Q)
{
	int p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.rear;		//��˳���β��ʼ���ӱ���
	while ((p - 1 + QMAXSIZE) % QMAXSIZE != Q.front)
	{
		printf("%d ", Q.base[p]);
		p = (p - 1 + QMAXSIZE) % QMAXSIZE;
	}
	printf("%d\n", Q.base[p]);

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
		QueueTraverse(Q);
		ClearQueue(Q);		//�ٴ�ʹ��ǰ��ն���
		scanf("%d", &m);
	}

	return 0;
}
