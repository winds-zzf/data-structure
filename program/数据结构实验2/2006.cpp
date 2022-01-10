#include<stdio.h>
#include<stdlib.h>
int main()
{
	int counter=0;
	char ch;
	int flag;


	while (1)
	{
		flag = 1;
		ch = getchar();
		counter = 0;
		if (ch == '0') break;
		while (ch != '\n')
		{
			if (ch == 'I')
			{
				counter++;
			}
			else if(ch == 'O')
			{
				counter--;
				if (counter < 0) flag = 0;	//始终为非负数
			}
			ch = getchar();
		}
		if (flag && !counter) printf("TRUE\n");
		else printf("FALSE\n");
	}


	return 0;
}