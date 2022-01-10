#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*------------------------------------------�������������������----------------------------------------------*/
//Huffman�����
typedef struct
{
	int weight;					//���Ȩ��
	int parent, lchild, rchild;	//˫�׽�㣬���Һ���
}HTNode, * HuffmanTree;			//����huffmanTree�Ľ��ṹ

typedef char** HuffmanCode;		//��̬��������洢�����������ָ���������ַ

typedef struct
{
	char letter;	//�������ĸ
	int rate;		//��ĸƵ����ΪȨֵ��������
	char* code;		//��ĸ��Ӧ�ı���
}LCode, * LetterCode;		//����һ��LetterCode���ʹ洢һ���ַ������ı�����Ϣ

//�������ܣ�ͳ�Ƹ��ַ����ֵ�Ƶ��(p%)
int FreqCollect(LetterCode& LC, char srcCode[])
{
	int length = 0;		//��ʼ����Ϊ��,ʼ��ָʾ��ǰ����
	LCode LCtemp[90];		//����ͳ��90�ֲ�ͬ���ַ�����
	int j = 0;

	for (int i = 0; i < 90; i++)		//��ʼ��LC��
	{
		LCtemp[i].rate = 1; LCtemp[i].code = NULL;		//����һ��ʹ��������ʱ������Ҳ����һ�������ֻҪʹ�ã���ʼֵ��Ϊ1
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
			LCtemp[++length].letter = srcCode[j];		//���ȼ�һ������������ĸ
		}
		j++;
	}

	LC = new LCode[length + 1];		//������±�1��ʼ�洢
	if (!LC) exit(OVERFLOW);

	for (int i = 1; i <= length; i++)
	{
		LC[i] = LCtemp[i];
	}

	return length;	//lengthʼ��ָʾ��ĸ��ǰ����
}

//��Huffman������ѡȨ����С����������±���ҷ�Χ:1-up��s0Ϊ��Сֵ��s1Ϊ����Сֵ��Ҫ��up��һ���ɴ�����(Ҫ��������Ȩֵȫ��һ�������)
void Select(HuffmanTree HT, int up, int& s0, int& s1)
{
	int min1 = 10000, min2 = 10000;		//����Сֵ�����ֵ		

	for (int i = 1; i <= up; i++)
	{
		if (HT[i].parent == 0 && HT[i].weight < min1)		//˫�׽��Ϊ��Ĳ���û���ù��Ŀ����õĽ��
		{
			min1 = HT[i].weight;
			s0 = i;		//s0�Ĵ��µ���Сֵ�±꣬s1�Ĵ���һ����Сֵ�±�
		}
	}
	for (int i = 1; i <= up; i++)
	{//ȥ����Сֵ֮���ٴ�����Сֵ�����ü�Ϊ����Сֵ
		if (i != s0 && HT[i].parent == 0 && HT[i].weight < min2)		//����һ��Լ��������s0��s0�����±��Ͻ��ظ�
		{
			min2 = HT[i].weight;
			s1 = i;		//s0�Ĵ��µ���Сֵ�±꣬s1�Ĵ���һ����Сֵ�±�
		}
	}
}

//����Ҷ�ӽ��������Huffman��HT�����ý������洢��ʽ
void CreateHuffmanTree(HuffmanTree& HT, LetterCode LC, int n)
{
	int s0, s1;
	int m = 2 * n - 1;				//һ��HT�����н����m = 2 * n -1��
	if (n < 1) return;			//�������������ʱ���б�Ҫ����Huffman��

	HT = new HTNode[m + 1];		//�洢������m����㣬��Ž�����ã�������m+1��
	if (!HT) exit(OVERFLOW);

	for (int i = 1; i <= m; i++)		//��ʼ��HT����
	{
		HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
	}
	for (int j = 1; j <= m; j++)		//����n��Ҷ�ӽ��Ȩֵ
	{
		HT[j].weight = LC[j].rate;		//��ÿ���ַ���Ƶ����ΪȨֵ
	}
	/*-------Huffman����ʼ����������ʼ����Huffman��--------*/
	for (int i = n + 1; i <= m; i++)
	{
		Select(HT, i - 1, s0, s1);		//��i���±�λ���ǵ�ǰ�������Ľ�㣬��˲��ҵ�i-1λ�ü���
		HT[s0].parent = HT[s1].parent = i;		//ȷ��iΪs0��s1��˫��
		HT[i].lchild = s0;	HT[i].rchild = s1;	//ȷ��s0��s1�ֱ���i�����Һ���
		HT[i].weight = HT[s0].weight + HT[s1].weight;		//ȷ��˫�׵�Ȩֵ
	}
}

//�������ܣ����ݴ�����HuffmanTree:HT������HuffmanCode
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode& HC, int n)
{
	char* cd;						//cd���ڼĴ���ʱ�ַ���������
	cd = new char[n];				//n��Ҷ�ӽ���Huffman���벻�ᳬ��nλ
	cd[n - 1] = '\0';					//cd[]�Ǵ��±��㿪ʼ��ģ���βΪ�̶�������'\0'

	HC = new char* [n + 1];			//ָ������HC������Ԫ��Ϊ�ַ���ָ��char*,HC��ָ��ָ���ָ��char**
	if (!HC) exit(OVERFLOW);		//ָ�������±��1��ʼ

	for (int i = 1; i <= n; i++)
	{
		int start, c, f;		//startΪ��ʱ����������±꣬cΪ��ǰ���(current),fΪ��ǰ����˫�׽��(father)
		start = n - 1, c = i; f = HT[i].parent;			//startָ��'\0',cָ��ǰ����ʼֵΪ��iƬҶ�ӣ�fΪi��˫��

		while (f != 0)			//ֻ�и��ڵ��˫�׽���±�Ϊ��
		{
			start--;			//��ʼʱstartָ������������Ӧ���ȼ�һ���ȿճ���λ�ã��ٸ��ƣ�
			if (c == HT[f].lchild) cd[start] = '0';		//��ǰ���current��Ϊ˫�׽��father�����ӣ�ֵΪ��
			else cd[start] = '1';
			c = f; f = HT[f].parent;		//˳������
		}

		HC[i] = new char[n - start];		//Ϊ��i�����붯̬�����ڴ�ռ䣬ĩ-��+1=(n-1)-start+1=n-start
		strcpy(HC[i], cd + start);			//�������±�Ϊstart��Ԫ�صĵ�ַΪ ����ַ+ƫ����
	}
	delete[]  cd;		//�ͷŶ�̬������ڴ�ռ�cd
}

//��ȡ��ĸ�Ķ�Ӧ���,nΪ�ַ�������
int locateLetter(LetterCode LC, char ch, int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (LC[i].letter == ch) return i;
	}
	return 0;	//�˳�ѭ��˵���Ҳ���������һ��0
}

//����Huffman�������
Status HuffmanEncoder(HuffmanCode HC, LetterCode LC, int n, char* dstCode, char* srcCode)
{
	int loc;
	dstCode[0] = '\0';		//���Ŀ��������ԭ���洢���ַ�
	for (int j = 0; srcCode[j] != '\0'; j++)
	{
		loc = locateLetter(LC, srcCode[j], n);		//������ĸ��ȡ����ĸ���±�
		strcat(dstCode, HC[loc]);				//�����±��ȡ��ĸ�Ĺ��������룬������dstCode�ĺ���
	}
	return OK;
}

//����Huffman��������
Status HuffmanDecoder(HuffmanTree HT, LetterCode LC, int n, char* dstCode, char* srcCode)
{
	int c, root, start = 0;		//j����ָ��dstCode����һλ�ַ��� cΪ��ǰ����HT��㣬 rootΪ���ĸ��ڵ�
	c = root = 2 * n - 1;

	for (int j = 0; dstCode[j] != '\0'; j++)		//һֱ������������һ���ַ�
	{
		if (dstCode[j] == '0')  c = HT[c].lchild;		//����Ϊ'0'����������
		else c = HT[c].rchild;							//����Ϊ'1'�������Һ���

		if (HT[c].lchild == 0 && HT[c].rchild == 0)		//���Ӻ��Һ���Ϊ�㣬ΪҶ�ӽ��
		{
			srcCode[start++] = LC[c].letter;		//�ҵ�Ҷ�ӽ��󣬽������
			c = root;								//������ɺ���c�ص�����㣬������һ����ĸ�Ľ���
		}
	}
	srcCode[start] = '\0';
	return OK;
}

int main()
{
	LetterCode LC;		//����һ��LetterCode���洢�ַ������ƣ�Ƶ�ȣ�������Ϣ
	HuffmanCode HC;		//Huffman����HC�����洢�����Ĺ���������
	HuffmanTree HT;		//Huffman��HT���洢����Ĺ�������
	int n, i;				//�洢Huffman����Ҷ�ӽ����
	char srcCode[100];
	char dstCode[500];

	scanf("%s", srcCode);				//������������ַ�����gets()�����뻺�����ж���س�����������������scanf()����ȡ�س��������������뻺����
	while (srcCode[0] != '0')
	{
		n = FreqCollect(LC, srcCode);		//����������ַ�����ͳ����ĸƵ�ȣ���¼��ĸ����
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

		CreateHuffmanCode(HT, HC, n);				//���Թ��������뺯��
		for (int i = 1; i < n; i++)
		{
			printf("%c:%s ", LC[i].letter, HC[i]);
		}
		printf("%c:%s\n", LC[i].letter, HC[i]);


		HuffmanEncoder(HC, LC, n, dstCode, srcCode);
		printf("%s\n", dstCode);		//���Ŀ�����

		HuffmanDecoder(HT, LC, n, dstCode, srcCode);
		printf("%s\n", srcCode);			//����ִ�й���������ѹ������
		getchar();
		scanf("%s", srcCode);				//�ٴζ�����������ַ�
	}

	return 0;
}