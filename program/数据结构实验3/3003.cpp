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

//�������ܣ����������Һ��ӵĽ���
void SwapLR(BiTree T)
{
	BiTree temp;		//��ʱָ�룬�ô�������ַ
	if (T)
	{
		SwapLR(T->lchild);		//�������������
		SwapLR(T->rchild);		//�������������
		temp = T->lchild;	T->lchild = T->rchild;	T->rchild = temp;		//��������������������
	}
}

//�������ܣ��������������
void PreOrderTraverse(BiTree T)
{
	if (T)
	{
		printf("%c", T->data);		//���ʸ����
		PreOrderTraverse(T->lchild);	//����������
		PreOrderTraverse(T->rchild);	//����������
	}
}

int main()
{
	BiTree  T;

	CreateBiTree(T);		//�����������������
	while (T)
	{
		SwapLR(T);				//�������������Һ���
		PreOrderTraverse(T);		//�������������
		getchar();
		putchar('\n');
		CreateBiTree(T);		//�����������������
	}

	return 0;
}
