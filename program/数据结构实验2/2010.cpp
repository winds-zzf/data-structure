#include<stdio.h>
#include<stdlib.h>

int Ack(int m, int n)
{
	if (m == 0)  return n + 1;
	else if (m > 0 && n == 0) return Ack(m - 1, 1);
	else return Ack(m-1, Ack(m, n-1));
}

int main()
{
	int m, n;

	scanf("%d%d", &m, &n);
	while (m!= 0 || n!=0)
	{
		printf("%d\n", Ack(m, n));

		scanf("%d%d", &m, &n);
	}

	return 0;
}