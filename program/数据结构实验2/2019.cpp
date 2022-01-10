#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE  100

//实现数组元素逆序
void Reserved(char *str, int i, int j)
{
	int temp;
	if (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		Reserved(str, ++i, --j);
	}
	else
	{
		return ;
	}
}

int main()
{
	char str[MAXSIZE];
	int  len;

	scanf("%s", str, MAXSIZE);
	while ( str[0] != '0' )
	{
		len = strlen(str);
		Reserved(str, 0, len-1);

		for (int i = 0; i < len; i++)
		{
			printf("%c", str[i]);
		}
		putchar('\n');
		scanf("%s", str, MAXSIZE);
	}

	return 0;
}
