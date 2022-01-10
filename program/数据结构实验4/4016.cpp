#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>
int last = 0, flag = 1;

//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	char data;								//������������
	struct BiTNode* lchild, * rchild;		//��������������
}BiTNode, * BiTree;							//�����������������BiTNode���Ͷ�����BiTNode

//�������ܣ������������������
void CreateBiTree(BiTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '#') T = NULL;			//��������
	else
	{
		T = new BiTNode;
		if (!T) exit(OVERFLOW);
		T->data = ch;

		CreateBiTree(T->lchild);			//����������
		CreateBiTree(T->rchild);			//����������
	}
}

//�������ܣ��ж϶������Ƿ�Ϊ���������
int JudgeSortBiT(BiTree T)
{
	if (T)
	{	//ע�������������ǰ��������д��һ��Ļ�Ҫ���������е�if���
		if (T->lchild && T->lchild->data > T->data)  return 0;		//�ҵ��������������ֱ�ӷ���0
		if (T->rchild && T->rchild->data < T->data)  return 0;
		if (JudgeSortBiT(T->lchild) && JudgeSortBiT(T->rchild)) return 1;
		return 0;
	}
}
int Is_BSTree(BiTree T)//�ж϶�����T�Ƿ����������,���򷵻�1,���򷵻�0
{
	if (T->lchild && flag) Is_BSTree(T->lchild);
	if (T->data < last) flag = 0; //��������ǰ����Ƚ�
	last = T->data;
	if (T->rchild && flag) Is_BSTree(T->rchild);
	return flag;
}

int main()
{
	BiTree T;		

	CreateBiTree(T);
	while (T)
	{
		if (Is_BSTree(T)) printf("YES\n");
		else printf("NO\n");

		getchar();				//����ĩβ�Ļس���
		CreateBiTree(T);
	}

	return 0;
}