#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int front, rear;		//ͷβָ��
	char str[50];
	scanf("%s", str, 50);
	while(str[0] != '0')		//������Ϊ0��ֹͣ
	{
		int flag = 1;
		for  (front=0, rear = strlen(str)-1; front<=rear; front++, rear--)
		{
			if (str[front] != str[rear])	flag = 0;
		}
		if(flag)	printf("YES\n");
		else		printf("NO\n");

		scanf("%s", str, 50);		//�ٴζ�ȡ
	}

	return 0;
}