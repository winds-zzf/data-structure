#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1

//二叉树的链式存储结构
typedef struct BiTNode
{
	int data;								//二叉树数据域
	struct BiTNode* lchild, * rchild;		//二叉树左、右子树
}BiTNode, * BiTree;							//创建二叉树结点类型BiTNode，和二叉树BiTNode

//函数功能：先序遍历创建二叉树
void CreateBiTree(BiTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '0') T = NULL;			//创建空树
	else
	{
		T = new BiTNode;
		if (!T) exit(OVERFLOW);
		T->data = ch;

		CreateBiTree(T->lchild);			//创建左子树
		CreateBiTree(T->rchild);			//创建右子树
	}
}

//函数功能：二叉树左右孩子的交换
void SwapLR(BiTree T)
{
	BiTree temp;		//临时指针，昝存树结点地址
	if (T)
	{
		SwapLR(T->lchild);		//交换左子树结点
		SwapLR(T->rchild);		//交换右子树结点
		temp = T->lchild;	T->lchild = T->rchild;	T->rchild = temp;		//交换根子树的左右子树
	}
}

//函数功能：先序遍历二叉树
void PreOrderTraverse(BiTree T)
{
	if (T)
	{
		printf("%c", T->data);		//访问根结点
		PreOrderTraverse(T->lchild);	//遍历左子树
		PreOrderTraverse(T->rchild);	//遍历右子树
	}
}

int main()
{
	BiTree  T;

	CreateBiTree(T);		//先序遍历创建二叉树
	while (T)
	{
		SwapLR(T);				//交换二叉树左右孩子
		PreOrderTraverse(T);		//先序遍历二叉树
		getchar();
		putchar('\n');
		CreateBiTree(T);		//先序遍历创建二叉树
	}

	return 0;
}
