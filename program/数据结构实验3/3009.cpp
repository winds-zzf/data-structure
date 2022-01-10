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

//函数功能：计算二叉树各度结点数目degree[2]下标0,1,2分别对应0度1度2度结点（要求：数量初始为零）
void CountNode(BiTree T, int* degree)
{
	if (T)
	{	//判断根结点度数
		if (!T->lchild && !T->rchild)		degree[0]++;	//左右子树均为空树：度为0
		else if (T->lchild && T->rchild)	degree[2]++;	//左右子树均非空树：度为2
		else								degree[1]++;	//有且仅有一个子树为空树：度为1
		//判断左右子树度数
		CountNode(T->lchild, degree);	//对左子树求各度结点数
		CountNode(T->rchild, degree);	//对右子树求各度结点数
	}
}

int main()
{
	BiTree  T;
	int degree[3];			//申请长度为三的数组分别存储各度结点
	CreateBiTree(T);		//先序遍历创建二叉树
	while (T)
	{
		for (int i = 0; i <= 2; i++)	//初始化degree[]数组
		{
			degree[i] = 0;
		}
		CountNode(T, degree);			//统计各度结点

		printf("%d ", degree[0]);		//1度结点数
		printf("%d ", degree[1]);		//2度结点数
		printf("%d\n", degree[2]);		//3度结点数

		getchar();
		CreateBiTree(T);		//先序遍历创建二叉树
	}

	return 0;
}
