#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*------------------------------------------哈夫曼树与哈夫曼编码----------------------------------------------*/
//Huffman树结点
typedef struct
{
	int weight;					//结点权重
	int parent, lchild, rchild;	//双亲结点，左右孩子
}HTNode, * HuffmanTree;			//定义huffmanTree的结点结构

typedef char** HuffmanCode;		//动态分配数组存储哈夫曼编码表，指针数组基地址

typedef struct
{
	char letter;	//编码的字母
	int rate;		//字母频度作为权值（整数）
	char* code;		//字母对应的编码
}LCode, * LetterCode;		//定义一个LetterCode类型存储一个字符及它的编码信息

//函数功能：统计各字符出现的频率(p%)
int FreqCollect(LetterCode& LC, char srcCode[])
{
	int length = 0;		//初始表长度为零,始终指示当前长度
	LCode LCtemp[90];		//至多统计90种不同的字符类型
	int j = 0;

	for (int i = 0; i < 90; i++)		//初始化LC表
	{
		LCtemp[i].rate = 1; LCtemp[i].code = NULL;		//当第一次使用这个结点时，自身也算做一个，因此只要使用，初始值就为1
	}

	while (srcCode[j] != '\0')
	{
		int i;
		for (i = 1; i <= length; i++)
		{
			if (srcCode[j] == LCtemp[i].letter)
			{
				++LCtemp[i].rate;
				break;
			}
		}
		if (i > length)
		{
			LCtemp[++length].letter = srcCode[j];		//长度加一，并存入新字母
		}
		j++;
	}

	LC = new LCode[length + 1];		//数组从下标1开始存储
	if (!LC) exit(OVERFLOW);

	for (int i = 1; i <= length; i++)
	{
		LC[i] = LCtemp[i];
	}

	return length;	//length始终指示字母表当前长度
}

//从Huffman树中挑选权重最小的两个结点下标查找范围:1-up，s0为最小值，s1为次最小值，要求up是一个可达上限(要考虑输入权值全部一样的情况)
void Select(HuffmanTree HT, int up, int& s0, int& s1)
{
	int min1 = 10000, min2 = 10000;		//给最小值赋最大值		

	for (int i = 1; i <= up; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < min1)		//双亲结点为零的才是没有用过的可以用的结点
		{
			min1 = HT[i].weight;
			s0 = i;		//s0寄存新的最小值下标，s1寄存上一个最小值下标
		}
	}
	for (int i = 1; i <= up; i++)
	{//去除最小值之后再次找最小值，所得即为次最小值
		if (i != s0 && HT[i].parent == 0 && HT[i].weight < min2)		//多了一条约束条件：s0，s0两个下标严禁重复
		{
			min2 = HT[i].weight;
			s1 = i;		//s0寄存新的最小值下标，s1寄存上一个最小值下标
		}
	}
}

//根据叶子结点数创建Huffman树HT，采用结点数组存储形式
void CreateHuffmanTree(HuffmanTree& HT, LetterCode LC, int n)
{
	int s0, s1;
	int m = 2 * n - 1;				//一棵HT的所有结点数m = 2 * n -1；
	if (n < 1) return;			//不少于两个结点时才有必要建立Huffman树

	HT = new HTNode[m + 1];		//存储整个树m个结点，零号结点弃用，故申请m+1个
	if (!HT) exit(OVERFLOW);

	for (int i = 1; i <= m; i++)		//初始化HT数组
	{
		HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
	}
	for (int j = 1; j <= m; j++)		//输入n个叶子结点权值
	{
		HT[j].weight = LC[j].rate;		//用每个字符的频度作为权值
	}
	/*-------Huffman树初始化结束，开始创建Huffman树--------*/
	for (int i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1, s0, s1);		//第i个下标位置是当前待创建的结点，因此查找的i-1位置即可
		HT[s0].parent = HT[s1].parent = i;		//确定i为s0，s1的双亲
		HT[i].lchild = s0;	HT[i].rchild = s1;	//确定s0，s1分别是i的左右孩子
		HT[i].weight = HT[s0].weight + HT[s1].weight;		//确定双亲的权值
	}
}

//函数功能：根据创建的HuffmanTree:HT，构建HuffmanCode
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n)
{
	char* cd;						//cd用于寄存临时字符编码数组
	cd = new char[n];				//n个叶子结点的Huffman编码不会超过n位
	cd[n - 1] = '\0';					//cd[]是从下标零开始存的，结尾为固定结束符'\0'

	HC = new char* [n + 1];			//指针数组HC，数据元素为字符型指针char*,HC是指向指针的指针char**
	if (!HC) exit(OVERFLOW);		//指针数组下标从1开始

	for (int i = 1; i <= n; i++)
	{
		int start, c, f;		//start为临时编码数组的下标，c为当前结点(current),f为当前结点的双亲结点(father)
		start = n - 1, c = i; f = HT[i].parent;			//start指向'\0',c指向当前结点初始值为第i片叶子，f为i的双亲

		while (f != 0)			//只有根节点的双亲结点下标为零
		{
			start--;			//初始时start指向结束符，因此应该先减一（先空出来位置，再复制）
			if (c == HT[f].lchild) cd[start] = '0';		//当前结点current若为双亲结点father的左孩子，值为零
			else cd[start] = '1';
			c = f; f = HT[f].parent;		//顺藤摸瓜
		}

		HC[i] = new char[n - start];		//为第i个编码动态申请内存空间，末-初+1=(n-1)-start+1=n-start
		strcpy(HC[i], cd + start);			//数组中下标为start的元素的地址为 基地址+偏移量
	}
	delete[]  cd;		//释放动态申请的内存空间cd
}

//获取字母的对应序号,n为字符种类数
int locateLetter(LetterCode LC, char ch, int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (LC[i].letter == ch) return i;
	}
	return 0;	//退出循环说明找不到，返回一个0
}

//进行Huffman编码过程
Status HuffmanEncoder(HuffmanCode HC, LetterCode LC, int n, char* dstCode, char* srcCode)
{
	int loc;
	dstCode[0] = '\0';		//清空目标数组内原来存储的字符
	for (int j = 0; srcCode[j] != '\0'; j++)
	{
		loc = locateLetter(LC, srcCode[j], n);		//根据字母获取该字母的下标
		strcat(dstCode, HC[loc]);				//根据下标获取字母的哈夫曼编码，连接在dstCode的后面
	}
	return OK;
}

//进行Huffman编码译码
Status HuffmanDecoder(HuffmanTree HT, LetterCode LC, int n, char* dstCode, char* srcCode)
{
	int c, root, start = 0;		//j用于指向dstCode的下一位字符， c为当前所在HT结点， root为树的根节点
	c = root = 2 * n - 1;

	for (int j = 0; dstCode[j] != '\0'; j++)		//一直处理到编码的最后一个字符
	{
		if (dstCode[j] == '0')  c = HT[c].lchild;		//编码为'0'，访问左孩子
		else c = HT[c].rchild;							//编码为'1'，访问右孩子

		if (HT[c].lchild == 0 && HT[c].rchild == 0)		//左孩子和右孩子为零，为叶子结点
		{
			srcCode[start++] = LC[c].letter;		//找到叶子结点后，解码完成
			c = root;								//解码完成后让c回到根结点，进行下一个字母的解码
		}
	}
	srcCode[start] = '\0';
	return OK;
}

int main()
{
	LetterCode LC;		//定义一个LetterCode来存储字符的名称，频度，编码信息
	HuffmanCode HC;		//Huffman编码HC，来存储构建的哈夫曼编码
	HuffmanTree HT;		//Huffman树HT，存储构造的哈夫曼树
	int n, i;				//存储Huffman树的叶子结点数
	char srcCode[100];
	char dstCode[500];

	scanf("%s", srcCode);				//读入待分析的字符串，gets()从输入缓冲区中读入回车符，并舍弃，但是scanf()不读取回车符，仍留在输入缓冲区
	while (srcCode[0] != '0')
	{
		n = FreqCollect(LC, srcCode);		//保存输入的字符，并统计字母频度，记录字母数量
		for (i = 1; i < n; i++)
		{
			printf("%c:%d ", LC[i].letter, LC[i].rate);
		}
		printf("%c:%d\n", LC[i].letter, LC[i].rate);

		CreateHuffmanTree(HT, LC, n);
		for (int i = 1; i <= 2 * n - 1; i++)
		{
			printf("%d %d %d %d %d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
		}

		CreateHuffmanCode(HT, HC, n);				//测试哈夫曼编码函数
		for (int i = 1; i < n; i++)
		{
			printf("%c:%s ", LC[i].letter, HC[i]);
		}
		printf("%c:%s\n", LC[i].letter, HC[i]);


		HuffmanEncoder(HC, LC, n, dstCode, srcCode);
		printf("%s\n", dstCode);		//输出目标编码

		HuffmanDecoder(HT, LC, n, dstCode, srcCode);
		printf("%s\n", srcCode);			//测试执行哈夫曼编码压缩过程
		getchar();
		scanf("%s", srcCode);				//再次读入待分析的字符
	}

	return 0;
}