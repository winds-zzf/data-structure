#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1

//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	int data;								//������������
	struct BiTNode* lchild, * rchild;		//��������������
}BiTNode, * BiTree;							//�����������������BiTNode���Ͷ�����BiTNode

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

//�������ܣ��������������
void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);	//����������
		printf("%c", T->data);			//���ʸ����
		InOrderTraverse(T->rchild);	//����������
	}
}

//�������ܣ��������������
void PreOrderTraverse(BiTree T)
{
	if (T)
	{
		printf("%c", T->data);			//���ʸ����
		PreOrderTraverse(T->lchild);	//����������
		PreOrderTraverse(T->rchild);	//����������
	}
}

//�������ܣ��������������
void PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);	//����������
		PostOrderTraverse(T->rchild);	//����������
		printf("%c", T->data);			//���ʸ����
	}
}

int main()
{
	BiTree  T;

	CreateBiTree(T);		//�����������������
	while (T)
	{
		PreOrderTraverse(T);		//�������
		printf("\n");
		InOrderTraverse(T);	//�������
		printf("\n");
		PostOrderTraverse(T);	//�������
		printf("\n");

		getchar();
		CreateBiTree(T);		//�����������������
	}

	return 0;
}
