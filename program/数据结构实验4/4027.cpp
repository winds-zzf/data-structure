#include <iostream>
using namespace std;


int CoSort(int a[], int m)
{
	int i, j;
	int b[m];
	int c[m];

	for (i = 0; i < m; i++)
	{
		c[i] = 0;
		b[i] = 0;
	}

	int k = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (a[i] > a[j])
			{
				b[k]++;
				//cout<<"b[k]++£º"<<k<<endl;
			}
		}
		k++;
	}

	for (i = 0; i < m; i++)
	{

		c[b[i]] = a[i];
		//cout<<c[b[i]]<<"*"<<a[i]<<"*"<<b[i]<<"*"<<c[i]<<endl;
		k++;
	}

	for (i = 0; i < m; i++)
	{
		cout << c[i];
		if (i != m - 1)cout << " ";
	}
	cout << endl;
	return 0;
}


int main()
{
	while (1)
	{
		int m; int i, j;
		cin >> m;
		if (0 == m) break;
		int a[m];
		for (i = 0; i < m; i++)
			cin >> a[i];
		CoSort(a, m);
	}
}