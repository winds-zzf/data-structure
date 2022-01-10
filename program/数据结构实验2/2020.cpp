#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

//���ַ����������ַ�����
int my_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

//�������ܣ����ַ����в����Ӵ�
void InsertString(char *str, char *src, int pos)
{
	int x = my_strlen(src);		//��ȡ�Ӵ����ȣ� ��ƫ����

	for (int i = my_strlen(str); i >= pos-1; i--)
	{
		str[i + x] = str[i];		//pos�����Ժ�Ԫ�����ƫ��x
	}
	for (int i = pos-1, j=0; j < x; j++, i++)
	{
		str[i] = src[j];
	}
}

int main()
{
	char str[MAXSIZE], src[MAXSIZE];
	int pos;

	scanf("%d", &pos);
	while (pos)
	{
		scanf("%s", str, 50);
		scanf("%s", src, 50);
		InsertString(str, src, pos);

		for (int i = 0; i < my_strlen(str); i++)
		{
			printf("%c", str[i]);
		}
		printf("\n");

		scanf("%d", &pos);
	}

	return 0;
}