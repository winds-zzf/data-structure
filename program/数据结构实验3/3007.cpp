#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define SMAXSIZE 200		//˳��ջ�洢�ռ�ĳ�ʼ����
typedef int Status;

//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	int data;								//������������
	struct BiTNode* lchild, * rchild;		//��������������
}BiTNode, * BiTree;							//�����������������BiTNode���Ͷ�����BiTNode

typedef struct
{
	BiTree* base;			//ջ��ָ�룬ʼ��ָ��ջ��Ԫ��
	BiTree* top;			//ջ��ָ�룬ʼ��ָ��ջ��Ԫ��
	int stacksize;		//ջ�������������˳��ջҪ����������
}SqStack;				//����һ��˳��ջ

//��ʼ��������һ����˳��ջ
Status InitStack(SqStack& S)
{
	S.base = new BiTree[SMAXSIZE];		//ջ��ָ��ָ�������׵�ַ
	if (!S.base) exit(OVERFLOW);	//����洢�ռ�ʧ��

	S.top = S.base;					//ջ��ָ����ջ��ָ���غϱ�ʾ��˳��ջ
	S.stacksize = SMAXSIZE;			//ջ�����������ΪMAXSIZE

	return OK;
}

//���һ���Ѵ��ڵ�˳��ջ
Status ClearStack(SqStack& S)		//SqStack ���͵�˳��ջS�м�¼��ջ����ջ��ָ���Լ�˳��ջ�������
{
	S.base = S.top;					//ջ��ָ����ջ��ָ���غϱ�ʾ��ջ
	return OK;						//���ֻ����ջ�ص���ʼ��״̬�����ı�ջ�����������
}

//����Ԫ��ѹ��˳��ջջ��
Status Push(SqStack& S, BiTree e)
{
	if (S.top - S.base == S.stacksize) return ERROR;	//���ջ��ָ����ջ��ָ���Ϊ���ռ䣬˵���Ѿ�ջ��
	*(S.top++) = e;										//�Ƚ���Ԫ��ѹ��ջ��ָ��ָ��Ŀ�λ�ã����ջ��ָ�����
	return OK;
}

//��˳��ջջ������ջ��Ԫ��
Status Pop(SqStack& S, BiTree& e)
{
	if (S.base == S.top) return ERROR;		//��ջ���ܽ��е�������
	e = *(--S.top);							//�Ƚ�ջ��ָ�����ָ��ջ��Ԫ�أ��ٽ�����
	return OK;
}

//����˳��ջ
Status StackTraverse(SqStack S)				//�������Ƕ�ȡ���һ�飬������վ����ջ
{
	BiTree* p = S.top;								//Book���ͽṹ������Ԫ��λ��ָ�룻��ʼʱָ��ʵ��ջ��ָ��λ��
	if (S.base == S.top) return ERROR;		//����Ҫ��֤ջ�ǿ�
	while (p != S.base)
	{
		printf("%c", (*--p)->data);			//����ṹ������ָ��Ԫ�ء�λ��ָ��ָ����һλ�������ǽṹ�����飬��˼�1ֱ��ָ������ֱ��ǰ��
	}
	printf("\n");				//��β�������
	return OK;
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

//�������ܣ�������Ҷ�ӽ��->�����·�����
void LeafPath(BiTree T, SqStack& ST)
{
	BiTree waste;
	if (T)
	{
		Push(ST, T);		//����㲻Ϊ�գ���ջ
		if (!T->lchild && !T->rchild)		StackTraverse(ST);		//�����Ҷ�ӽ�㣬�������ջ�ռ�
		else
		{
			LeafPath(T->lchild, ST);
			LeafPath(T->rchild, ST);
		}
		Pop(ST, waste);				//�������Ҫ�˳�ջ��Ԫ��1:Ҷ�ӽ���������˳���2������������������˳�
	}
}

int main()
{
	BiTree  T;
	SqStack ST;
	InitStack(ST);

	CreateBiTree(T);		//�����������������
	while (T)
	{
		LeafPath(T, ST);		//����Ҷ�ӽ��·��
		getchar();
		CreateBiTree(T);		//�����������������
	}

	return 0;
}
