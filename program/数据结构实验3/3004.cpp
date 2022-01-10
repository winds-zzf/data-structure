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

//�������ܣ���������˫�����
void PreOrderTraverse_Du(BiTree T)
{
	if (T)
	{
		printf("%c", T->data);			//��һ����������η��ʸ����
		PreOrderTraverse_Du(T->lchild);		//˫�����������
		printf("%c", T->data);			//�ڶ���������ٴη��ʸ����
		PreOrderTraverse_Du(T->rchild);		//˫�����������
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
		PreOrderTraverse_Du(T);		//˫�����������
		getchar();
		putchar('\n');
		CreateBiTree(T);		//�����������������
	}

	return 0;
}
