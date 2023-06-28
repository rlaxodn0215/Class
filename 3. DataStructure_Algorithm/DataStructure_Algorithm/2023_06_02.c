#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include <time.h>

int main()
{
	int num = 10;
	int n;
	int arr[10] = {5,7,28,29,31,39,58,68,72,95};
	
	scanf("%d", &n);

	printf("  | ");

	for (int i = 0; i < num; i++)
	{
		printf("%d ", i);
	}

	printf("\n---------------------------------------------------\n");


	int count = 0;
	int length = num / 2;
	int check = num / 2;
	while (1)
	{
		count++;
		printf("  | ");

		for (int i = check - length; i < check; i++)
		{
			//printf("")
		}

		if (arr[check] == n)
		{
			printf("%d는 arr[%d]에 있는걸 %d번만에 찾았습니다", n, check, count);
			break;
		}

		else if (arr[check] < n)
		{
			check += length / 2;
			length /= 2;
			if (length == 0) length = 2;
		}

		else
		{
			check -= length / 2;
			length /= 2;
			if (length == 0) length = 2;
		}

	}

	printf("\n");
	
	return 0;
}