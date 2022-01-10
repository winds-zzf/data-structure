#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define QMAXSIZE 120
typedef int Status;

//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	int data;								//������������
	struct BiTNode* lchild, * rchild;		//��������������
}BiTNode, * BiTree;							//�����������������BiTNode���Ͷ�����BiTNode

typedef struct
{
	BiTree* base;		//�ṹ���������ַ
	int front;		//ͷָ��
	int rear;		//βָ��
}SqQueue;			//˳��ջ

//��ʼ�����У�����һ����˳���
Status InitQueue(SqQueue& Q)
{
	Q.base = new BiTree[QMAXSIZE];	//����һ������ΪMAXSize��˳����У����洢���Ļ���ַ
	if (!Q.base) exit(OVERFLOW);	//�ڴ�����ʧ�ܣ��˳�����
	Q.front = Q.rear = 0;  //�ն���ͷβָ�붼Ϊ�㣬�������ν��ָ��ȫ�������±�ֻ������ͬ�±�ָ���ض�����Ԫ�ذ���
	return OK;		//�ɹ� ����
}

// ��ȡ˳��Ӷ�ͷԪ��
BiTree GetFront(SqQueue Q)
{
	if (Q.rear != Q.front) 		//���˳��Բ�Ϊ�գ�ֱ�Ӷ�ȡ��ͷԪ��
		return Q.base[Q.front];		//ͷָ��ֱ��ָ���ͷԪ�أ�βָ��ָ���βԪ�صĺ�һλ��������ֱ�Ӷ�ȡ�����
}

// ˳������
Status EnQueue(SqQueue& Q, BiTree e)
{
	if (Q.front == (Q.rear + 1) % QMAXSIZE) return ERROR;//�������ָ����ƶ�Ҫ����ģ���㣬��Ϊ��������ģ��
	Q.base[Q.rear] = e;									//�ṹ���������ֱ�ӽ��и�ֵ
	Q.rear = (Q.rear + 1) % QMAXSIZE;					//���ڴ���ģ������ÿ��һ����Ҫȡ�࣬���Ҫ��������ȡ�����㣬���ɺϲ�
	return OK;
}

// ˳��ӳ���
Status DeQueue(SqQueue& Q, BiTree& e)
{
	if (Q.front == Q.rear) return ERROR;		//����ѭ�����в���Ϊ�գ�
	e = Q.base[Q.front];					//ȡ�ṹ�������ͷԪ�أ�����
	Q.front = (Q.front + 1) % QMAXSIZE;		//ѭ�������ǵ����������ͷβָ��ֻ������ƶ����������Ǿ���ģ�����㣬ֻҪ���Ӿ�Ҫȡ��
	return OK;
}

// �ж�˳������Ƿ�Ϊ�ն�
Status QueueEmpty(SqQueue Q)
{
	return Q.front == Q.rear ? 1 : 0;  //ע��ѭ�����ж��������������ģ�ֻҪͷβָ���غϾ�˵���ǿն�
}


//�������ܣ������������������
void CreateBiTree(BiTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '0') T = NULL;			//��������
	else
	{
		T = new BiTNode;
		if (!T) exit(OVERFLOW);
		T->data = ch;

		CreateBiTree(T->lchild);			//����������
		CreateBiTree(T->rchild);			//����������
	}
}

//�������ܣ�������������
int BiTWidth(BiTree T)
{
	int counter, max = 0;	//���ֵ��ʼ��Ϊ��
	BiTree q, w;
	SqQueue QT;		//�洢����������ָ��
	InitQueue(QT);

	//��ʼ�������������
	EnQueue(QT, T);		//����ָ�����ͷ
	EnQueue(QT, NULL);	//��ָ����ջ��Ϊ�н�����

	//��ʼ����
	while (!QueueEmpty(QT) && GetFront(QT) != NULL)	//�ӷǿ�˵��δ������
	{
		counter = 0;	//��ʼ����������Ϊ��
		while (GetFront(QT) != NULL)		//��ͷ�ǿգ����ӣ���Ԫ�����
		{

			DeQueue(QT, q); counter++;		//˫�׽������һ
			if (q->lchild)		EnQueue(QT, q->lchild);		//
			if (q->rchild)		EnQueue(QT, q->rchild);		//
		}
		DeQueue(QT, q);		//��������ջ
		EnQueue(QT, NULL);		//��һ����������ӽ�����NULL
		if (max < counter)	max = counter;		//max����ˢ��Ϊ���ֵ
	}
	return max;
}

int main()
{
	BiTree  T;

	CreateBiTree(T);		//�����������������
	while (T)
	{
		printf("%d\n", BiTWidth(T));
		getchar();
		CreateBiTree(T);		//�����������������
	}

	return 0;
}
