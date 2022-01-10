#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>

//二叉树的链式存储结构
typedef struct BiTNode
{
	int data;								//二叉排序树数据域
	struct BiTNode* lchild, * rchild;		//二叉排序树左、右子树
}BSTNode, *BSTree;							//创建二叉排序树

//函数功能：先序遍历创建二叉树
void CreateBiTree(BSTree& T)
{
	char ch;
	ch = getchar();
	if (ch == '#') T = NULL;			//创建空树
	else
	{
		T = new BiTNode;
		if (!T) exit(OVERFLOW);
		T->data = ch;

		CreateBiTree(T->lchild);			//创建左子树
		CreateBiTree(T->rchild);			//创建右子树
	}
}

//函数功能：计算二叉树深度
int BSTDepth(BSTree T)
{
	int m, n;
	if (!T) return 0;			//空树深度为零
	else
	{
		m = BSTDepth(T->lchild);	//计算当前根子树左子树的深度
		n = BSTDepth(T->rchild);	//计算当前根子树右子树的深度
		return m > n ? m + 1 : n + 1;	//返回深度较大的子树深度值，并加上当前树根算一层
	}
}


int main()
{
	BSTree T;

	CreateBiTree(T);
	while (T)
	{
		printf("%d\n", BSTDepth(T));
		
		T = NULL;		//将T初始化为空树
		getchar();		//读取缓冲区的回车符
		CreateBiTree(T);
	}

	return 0;
}