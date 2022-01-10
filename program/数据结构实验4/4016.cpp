#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>
int last = 0, flag = 1;

//二叉树的链式存储结构
typedef struct BiTNode
{
	char data;								//二叉树数据域
	struct BiTNode* lchild, * rchild;		//二叉树左、右子树
}BiTNode, * BiTree;							//创建二叉树结点类型BiTNode，和二叉树BiTNode

//函数功能：先序遍历创建二叉树
void CreateBiTree(BiTree& T)
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

//函数功能：判断二叉树是否为排序二叉树
int JudgeSortBiT(BiTree T)
{
	if (T)
	{	//注意这里如果不把前两个条件写在一块的话要用两个并列的if语句
		if (T->lchild && T->lchild->data > T->data)  return 0;		//找到不满足条件结点直接返回0
		if (T->rchild && T->rchild->data < T->data)  return 0;
		if (JudgeSortBiT(T->lchild) && JudgeSortBiT(T->rchild)) return 1;
		return 0;
	}
}
int Is_BSTree(BiTree T)//判断二叉树T是否二叉排序树,是则返回1,否则返回0
{
	if (T->lchild && flag) Is_BSTree(T->lchild);
	if (T->data < last) flag = 0; //与其中序前驱相比较
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

		getchar();				//处理末尾的回车符
		CreateBiTree(T);
	}

	return 0;
}