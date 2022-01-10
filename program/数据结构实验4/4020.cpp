#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define MAXNUM 13			//hash��Ĺ̶�����

typedef struct HashNode
{
	int key;						//
	struct HashNode* next;	
}HashNode;				//��ϣ����->����ַ�����

typedef struct
{
	HashNode** R;		//hash�����ַ
	int length;			//hash��ĳ���
}HTable;

//����ͷ���ĵ�������������
void SortList(HashNode *L)
{
	HashNode* p, *q, *t;
	int temp;
	if (L && L->next)		//�����������Ͻ�㣬���б�Ҫ����
	{
		p = L; 
		while (p->next)		//�����ѡ������
		{
			q = p->next;	//q��ʼΪp��ֱ�Ӻ��
			t = p;
			while (q)
			{
				if (q->key < t->key)  t = q; 
				q = q->next;
			}

			if (t != p) 
			{ 
				temp = t->key;
				t->key = p->key;
				p->key = temp;
			}					//����t��p

			p = p->next;		//���pָ�����
		}
	}
}

//�������ܣ�����hash��
void CreateHTable(HTable &HT)
{
	int key, loc;
	HashNode* p;

	scanf_s("%d", &HT.length);					//�������ݸ���
	for (int i = 0; i < MAXNUM; i++)			//��ʼ��ָ����
		HT.R[i] = NULL;

	for (int i = 0; i < HT.length; i++)
	{
		scanf_s("%d", &key);
		loc = key % MAXNUM;
		
		//�����½��
		p = new HashNode;
		if (!p) exit(OVERFLOW);
		p->key = key;
		p->next = HT.R[loc]; HT.R[loc] = p;		//ǰ�巨

		//����ͷ���ĵ�������������
		SortList(p);
	}
}

//�������ܣ���ϣ��ֵ����
void InsertHTable(HTable &HT, int key)
{
	int loc;
	HashNode* p;

	loc = key % 13;
	p = new HashNode;
	if (!p) exit(OVERFLOW);
	p->key = key;
	p->next = HT.R[loc]; HT.R[loc] = p;		//ǰ�巨

	SortList(p);
}

//�������ܣ������ϣ��
void OutHTable(HTable HT)
{
	HashNode* p;
	for (int i = 0; i < 13; i++)
	{
		printf("%d", i);
		p = HT.R[i];
		while (p)
		{
			printf(" %d", p->key);
			p = p->next;
		}
		printf("\n");
	}
}

//�������ܣ���������ַ���Ĺ�ϣ��
void DestortyHTable(void)
{
	;
}

int main()
{
	HTable HT;
	int key;
	HT.R = new HashNode*[MAXNUM];			//HTΪ���ָ������

	CreateHTable(HT);						//����,����ʱ�Ѿ��������ݸ�����
	while (HT.length)
	{
		scanf_s("%d", &key);
		InsertHTable(HT, key);					//����
		OutHTable(HT);							//������
		CreateHTable(HT);						//����
	}
	
	return 0;
}