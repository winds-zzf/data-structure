#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define SMAXSIZE 200		//顺序栈存储空间的初始容量
typedef int Status;

//二叉树的链式存储结构
typedef struct BiTNode
{
	int data;								//二叉树数据域
	struct BiTNode* lchild, * rchild;		//二叉树左、右子树
}BiTNode, * BiTree;							//创建二叉树结点类型BiTNode，和二叉树BiTNode

typedef struct
{
	BiTree* base;			//栈底指针，始终指向栈底元素
	BiTree* top;			//栈顶指针，始终指向栈顶元素
	int stacksize;		//栈可用最大容量，顺序栈要有容量上限
}SqStack;				//构造一个顺序栈

//初始化，构造一个空顺序栈
Status InitStack(SqStack& S)
{
	S.base = new BiTree[SMAXSIZE];		//栈底指针指向数组首地址
	if (!S.base) exit(OVERFLOW);	//申请存储空间失败

	S.top = S.base;					//栈顶指针与栈底指针重合表示空顺序栈
	S.stacksize = SMAXSIZE;			//栈可用最大容量为MAXSIZE

	return OK;
}

//清空一个已存在的顺序栈
Status ClearStack(SqStack& S)		//SqStack 类型的顺序栈S中记录了栈顶，栈底指针以及顺序栈最大容量
{
	S.base = S.top;					//栈底指针与栈顶指针重合表示空栈
	return OK;						//清空只是让栈回到初始化状态，不改变栈可用最大容量
}

//将新元素压入顺序栈栈顶
Status Push(SqStack& S, BiTree e)
{
	if (S.top - S.base == S.stacksize) return ERROR;	//如果栈顶指针与栈底指针差为最大空间，说明已经栈满
	*(S.top++) = e;										//先将新元素压入栈顶指针指向的空位置，随后栈顶指针后移
	return OK;
}

//从顺序栈栈顶弹出栈顶元素
Status Pop(SqStack& S, BiTree& e)
{
	if (S.base == S.top) return ERROR;		//空栈不能进行弹出操作
	e = *(--S.top);							//先将栈顶指针后移指向栈顶元素，再解引用
	return OK;
}

//判断一个顺序栈长度
int  StackLength(SqStack S)
{
	return S.top - S.base;				//栈顶指针-栈底指针=偏移量+1=元素数
}

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

//函数功能：计算二叉树深度
int BiTDepth(BiTree T)
{
	int m, n;
	if (!T) return 0;			//空树深度为零
	else
	{
		m = BiTDepth(T->lchild);	//计算当前根子树左子树的深度
		n = BiTDepth(T->rchild);	//计算当前根子树右子树的深度
		return m > n ? m + 1 : n + 1;	//返回深度较大的子树深度值，并加上当前树根算一层
	}
}

//遍历顺序栈
Status StackTraverse_Reversed(SqStack S)				//遍历仅是读取浏览一遍，而不出站或入栈
{
	BiTree* p = S.base;								//Book类型结构体数组元素位置指针；初始时指向实际栈顶指针位置
	if (S.base == S.top) return ERROR;		//遍历要保证栈非空
	while (p != S.top)
	{
		printf("%c", (*p++)->data);			//输出结构体数组指定元素。位置指针指向下一位，由于是结构体数组，因此减1直接指向了其直接前驱
	}
	printf("\n");
	return OK;
}

//求解二叉树第一条最长路径：方向:根->叶子
void LongestPath(BiTree T, SqStack& ST, int& n)
{
	BiTree waste;
	if (T)
	{
		Push(ST, T);		//根结点不为空，入栈
		if (!T->lchild && !T->rchild)
		{
			if (StackLength(ST) == n)
			{
				StackTraverse_Reversed(ST);		//如果是最长叶子结点，逆序遍历栈空间
				n++;		//当执行过一次遍历后n加一，此后条件StackLength(ST) == n 便永假
			}
		}
		else
		{
			LongestPath(T->lchild, ST, n);
			LongestPath(T->rchild, ST, n);
		}
		Pop(ST, waste);				//遍历完后要退出栈顶元素1:叶子结点遍历完后退出，2：左右子树遍历完后退出
	}
}

int main()
{
	int n;		//树的最长路径
	BiTree  T;
	SqStack ST;
	InitStack(ST);

	CreateBiTree(T);		//先序遍历创建二叉树
	while (T)
	{
		n = BiTDepth(T);		//获取树的最长路径
		printf("%d\n", n);
		LongestPath(T, ST, n);	//查找最长叶子结点路径
		ClearStack(ST);			//下次使用前清空栈
		getchar();
		CreateBiTree(T);		//先序遍历创建二叉树
	}

	return 0;
}
