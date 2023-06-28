#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include <time.h>


int main()
{
	/*const int size = 10;
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };

	for (int i = 0; i < (10/2); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%d ", arr[j]);
		}

		printf("\narr[%d]와 arr[%d]를 교환합니다.\n\n", i, 9 - i);

		int temp = arr[i];
		arr[i] = arr[9 - i];
		arr[9 - i] = temp;
	}

	printf("역순정렬을 종료합니다.");*/

	////1.
	//int N;
	//printf("N값 입력: ");
	//scanf("%d", &N);

	//int count = 0;

	//for (int i = 2; i <= N; i++)
	//{
	//	for (int j = 2; j < i; j++)
	//	{
	//		count++;

	//		if (i % j == 0)
	//			break;

	//	}
	//}

	//printf("%d\n", count);

	////2
	//int n;
	//printf("n값 입력: ");
	//scanf("%d", &n);

	//int count = 0;

	//for (int i = 3; i <= n; i += 2)
	//{
	//	for (int j = 3; j < i; j += 2)
	//	{
	//		count++;
	//		if (i % j == 0)
	//			break;
	//	}
	//}

	//printf("%d\n", count);

	////3
	//int n;
	//printf("n값 입력: ");
	//scanf("%d", &n);

	//int arr[500] = {0,};
	//arr[0] = 2;
	//int count = 0;

	//for (int i = 3; i <= n; i += 2)
	//{
	//	for (int j = 1; j < 500; j ++)
	//	{
	//		if (arr[j] != 0)
	//		{
	//			count++;
	//			if (i % arr[j] == 0)
	//				break;
	//		}

	//		else
	//		{
	//			arr[j] = i;
	//			break;
	//		}
	//	}
	//}

	//printf("%d\n", count);

	//4
	int n;
	printf("n값 입력: ");
	scanf("%d", &n);

	int arr[500] = {0,};
	arr[0] = 2;
	int count = 0;

	int ptr=0;
	for (int i = 3; i <= n; i += 2)
	{
		for (int j = 1; j < 500; j++)
		{

			if (arr[j] != 0 && arr[j]<= sqrt(i))
			{
				count++;
				if (i % arr[j] == 0)
					break;
			}

			else
			{
				ptr++;
				arr[ptr] = i;
				printf("%3d ", arr[ptr]);
				break;
			}
		}
	}

	printf("\n\ncount: %d\n", count);

	return 0;
}