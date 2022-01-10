#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LOVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cmath>
typedef int Status;
typedef struct
{
	char bookNum[15];	//���
	char bookName[40];	//����
	float bookPrice;	//�鼮�۸�
}Book;			//����Book���ͽṹ������洢�鼮��Ϣ
typedef struct LNode
{
	Book date;			//���������
	struct LNode* next;	//���ָ����
}LNode, * LinkList;

//�ṹ����������
void Input(Book& e)
{
	scanf("%s%s%f",
		e.bookNum, 15,
		e.bookName, 40,
		&e.bookPrice
	);
}

//�ṹ�������������
void Output(Book e)
{
	printf("%s %s %.2f\n",
		e.bookNum,
		e.bookName,
		e.bookPrice
	);
}
//�Ƚ������ṹ���Ƿ���ͬ
Status BookCmp(Book elem_1, Book elem_2)
{
	if (!strcmp(elem_1.bookNum, elem_2.bookNum))
	{
		if (!strcmp(elem_1.bookName, elem_2.bookName))
		{
			if (fabs((double)elem_1.bookPrice - (double)elem_2.bookPrice) < 0.0001)
				return OK;
		}
	}
	return ERROR;
}//���������ʼ��
Status InitList(LinkList& L)
{
	L = new LNode;		//�����½ڵ���Ϊͷ���
	if (!L) exit(LOVERFLOW);

	L->next = NULL;	//�ձ�ָ����Ϊ��
	return OK;
}
//�����������
Status ListTraverse(LinkList L)
{
	LinkList p = L->next;  //���λ��ָ��
	if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
	while (p)
	{
		Output(p->date);
		p = p->next;		//ָ�����
	}
	return OK;
}

Status CreateList_R(LinkList& L)
{
	LinkList p, t;		//βָ��p, ��ʱ���ָ��r���Ĵ������ɽ���ַ
	Book e, m = {"0", "0", 0.0};

	L = new LNode; if (!L) exit(LOVERFLOW);		//����һ���ձ����ж��Ƿ�ɹ�
	L->next = NULL;

	p = L;  //ָ����Ԫ���λ��
	Input(e);
	while(!BookCmp(e, m))
	{
		t = new LNode;			//����һ���½��,����������
		if (!t) exit(LOVERFLOW); 
		t->date = e;		

		p->next = t; t->next = NULL; p = t;				//���Ҫ��p = t����ΪpҪʼ��ָ��βָ��
		
		Input(e);
	}
	return OK;
}

//ͼ����Ϣ�����༭
Status EditList(LinkList L)
{
	LinkList p = L->next;  //���λ��ָ��
	float sum = 0, aver;
	int j = 0;
	if (!L->next) return ERROR;		//����Ҫ�ж������Ƿ�Ϊ��
	while (p)
	{
		sum += p->date.bookPrice; j++;
		p = p->next;		//ָ�����
	}
	aver = sum / j;		//��ƽ��ֵ
	printf("%.2f\n", aver);
	p = L->next;
	while (p)
	{
		if (p->date.bookPrice <= aver) p->date.bookPrice *= 1.2f;
		else p->date.bookPrice *= 1.1f;
		p = p->next;	//ָ�����
	}
	return OK;
}

int main()
{
	LinkList L;

	CreateList_R(L);

	EditList(L);
	
	ListTraverse(L);
	return 0;
}