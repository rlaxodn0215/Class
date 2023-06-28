#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include <time.h>

int main()
{
	int k = 0;
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= 2*n - 1; i++)
	{
		for (int j = 1; j <= 2 * n - 1; j++)
		{
			if (i > n)
			{
				k++;
			}

			if (i==j)
			{
				printf("%d", i);
			}
		}

		printf("\n");
	}
}

