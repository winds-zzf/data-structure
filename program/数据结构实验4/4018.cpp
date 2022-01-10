#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>
int outdata[50];			//ȫ������
int countdata[50];
int pt = -1;

//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	int data;								//����������������
	int count;								//�ظ��������
	struct BiTNode* lchild, * rchild;		//������������������
}BSTNode, * BSTree;							//��������������

//�����������Ĳ���
BSTree SearchBST(BSTree T, int key)
{
	if (!T) return T;			//TΪ��˵���Ҳ����ˣ�һֱ����T==NULL
	else if (key == T->data)	return T;		//���˵���ҵ������ؽ���ַT
	else if (key < T->data) return SearchBST(T->lchild, key);		//keyƫС��������������
	else return SearchBST(T->rchild, key);			//keyƫ��������������
}

//�����������Ĳ���
void InsertBST(BSTree& T, int key)
{
	//����������в����ڸýڵ㣬��ô�������ҵ���λ��
	if (!T)			//����Ϊ�գ�˵���ҵ�����λ��
	{
		T = new BSTNode;
		if (!T) exit(OVERFLOW);
		T->data = key;
		T->count = 0;
		T->lchild = T->rchild = NULL;		//�²�����һ����Ҷ�ӽڵ㣬ָ����Ϊ��
	}
	else if (key < T->data)  InsertBST(T->lchild, key);
	else if (key > T->data)  InsertBST(T->rchild, key);
}

//�������ܣ���������������
void CreateBST(BSTree& T)
{
	int e, num;
	T = NULL;				//�������������ʼ��Ϊ������
	scanf_s("%d", &num);	//�������num

	for (int i = 0; i < num; i++)
	{
		scanf_s("%d", &e);
		InsertBST(T, e);	//���½������ʵ�λ��
	}
}

//�������������ķǹ��㷨
void Search_InsertBST_N(BSTree &T, int key)
{
	BSTree p;
	p = T;
	while (p)
	{
		if (key == p->data) break;
		else if (key < p->data) p = p->lchild;
		else p = p->rchild;
	}

	if (p)	p->count++;	//�ҵ�,����ֵ��1
	else				//δ�ҵ���������
	{
		InsertBST(T, key);
	}
}


//����������������ض�����
void InOrderTraverse(BSTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		outdata[++pt] = T->data;
		countdata[pt] = T->count;
		InOrderTraverse(T->rchild);
	}
}

int main()
{
	BSTree T;
	int key;

	CreateBST(T);
	while (T)
	{
		pt = -1;
		scanf_s("%d", &key);

		Search_InsertBST_N(T, key);
		InOrderTraverse(T);				

		for (int i = 0; i < pt; i++)
			printf("%d ", outdata[i]);
		printf("%d\n", outdata[pt]);

		for (int i = 0; i < pt; i++)
			printf("%d ", countdata[i]);
		printf("%d\n", countdata[pt]);

		CreateBST(T);
	}

	return 0;
}