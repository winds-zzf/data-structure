#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#include<stdio.h>
#include<stdlib.h>
typedef int Status;	//��intȡ����ΪStatus


typedef struct SNode	//SΪStack������ջ���Stack Node
{
	int date;			//��ջ���������
	struct SNode* next;	//��ջ���ָ����
}SNode, * LinkStack;

//��ջ�ĳ�ʼ��������һ������ջ
Status InitStack(LinkStack& S)	//S��ָ��SNode����ָ�����Ӧ���ǽṹ��ָ������LinkStack
{
	S = NULL;		//����û��ͷ��㣬���ֱ����ͷָ��Ϊ�գ���ʾ����ջ
	return OK;
}

//�Ѵ�����ջ�����
Status ClearStack(LinkStack& S)	//��ջû��ͷ��㣬�����ջ��Ҫ�޸�S
{
	LinkStack p;			//��ʱ���ָ��p�Ĵ�ջ����ɾ��Ԫ��
	if (!S) return OK;		//S==NULL˵������
	while (S)				//��Ϊs��ֱ��ָ��ջ��Ԫ�صģ����ֻҪS��Ϊ�գ���˵��ջ��Ԫ������
	{
		p = S; S = S->next; delete p;		//�Ĵ棬�ƶ���ɾ��
	}
	return OK;
}

//������ջ��ջ
Status Push(LinkStack& S, int e)
{
	LinkStack p;	//��ʱջ���ָ��
	p = new SNode;
	if (!p) exit(OVERFLOW);
	p->date = e;

	p->next = S;
	S = p;

	return OK;
}

//�ǿ���ջ����ջ��Ԫ��
Status Pop(LinkStack& S, int &e)
{
	LinkStack p;
	if (!S) return ERROR;
	e = S->date;
	p = S;	S = S->next; delete p;
	return OK;
}


int main()
{
	int m, e;
	LinkStack S;
	InitStack(S);

	scanf("%d", &m);
	while (m)		//������Ϊ0��ֹͣ
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%d", &e);
			if (e == -1)
			{
				if (Pop(S, e))	printf("%d\n", e);		//��ջ������������
				else
				{
					printf("POP ERROR\n");				//��ջ�쳣�����ش�����ʾ
					while (getchar() != '\n') ;			//��ձ���ʣ����
					break;
				}
			}
			else
			{
				Push(S, e);
			}
		}

		scanf("%d", &m);		//�ٴζ�ȡ
		ClearStack(S);				//�ٴ�ʹ��ǰ���ջ�ռ�
	}

	return 0;
}