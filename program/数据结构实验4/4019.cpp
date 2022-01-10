#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>

//����������ʽ�洢�ṹ
typedef struct BiTNode
{
	int data;								//����������������
	struct BiTNode* lchild, * rchild;		//������������������
}BSTNode, *BSTree;							//��������������

//�������ܣ������������������
void CreateBiTree(BSTree& T)
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

//�������ܣ�������������
int BSTDepth(BSTree T)
{
	int m, n;
	if (!T) return 0;			//�������Ϊ��
	else
	{
		m = BSTDepth(T->lchild);	//���㵱ǰ�����������������
		n = BSTDepth(T->rchild);	//���㵱ǰ�����������������
		return m > n ? m + 1 : n + 1;	//������Ƚϴ���������ֵ�������ϵ�ǰ������һ��
	}
}


int main()
{
	BSTree T;

	CreateBiTree(T);
	while (T)
	{
		printf("%d\n", BSTDepth(T));
		
		T = NULL;		//��T��ʼ��Ϊ����
		getchar();		//��ȡ�������Ļس���
		CreateBiTree(T);
	}

	return 0;
}