#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include <time.h>


int main()
{
	////1
	//int arr[8] = { 6,5,2,1,8,9,7,4 };
	//int n;
	//printf("�˻� ������: ");
	//scanf("%d", &n);

	//for (int i = 0; i < 8; i++)
	//{
	//	if (arr[i] == n)
	//	{
	//		printf("�ڷ��߿� %d�� �ֽ��ϴ�.", n);
	//		return 0;
	//	}
	//}

	//printf("�ڷ��߿� %d�� �����ϴ�.", n);

	////2
	//int arr[9] = { 6,5,2,1,8,9,7,4 };
	//int n;
	//printf("�˻� ������: ");
	//scanf("%d", &n);
	//arr[8] = n;
	//int i = 0;
	//
	//while(1)
	//{
	//	if (arr[i] == n)
	//	{
	//		break;
	//	}

	//	i++;
	//}

	//if (i == 8)
	//{
	//	printf("�ڷ��߿� %d�� �����ϴ�.", n);
	//}
	//else
	//{
	//	printf("�ڷ��߿� %d�� �ֽ��ϴ�.", n);
	//}

	//3
	int arr[9] = { 6,5,2,1,8,9,7,4 };
	int n;
	printf("�˻� ������: ");
	scanf("%d", &n);

	printf("  | ");

	for (int i = 0; i < 8; i++)
	{
		printf("%d ", i);
	}

	printf("\n---------------------------------------------------\n");

	arr[8] = n;
	int i = 0;
	
	while(1)
	{
		if (arr[i] == n)
		{
			break;
		}

		printf("  | ");
		for (int j = 0; j < i; j++)
		{
			printf("  ");
		}

		printf("*\n");
		printf("%d",i);
		printf(" | ");

		for (int i = 0; i < 8; i++)
		{
			printf("%d ", arr[i]);
		}

		i++;

		printf("\n");
	}

	if (i == 8)
	{
		printf("\n\n�ڷ��߿� %d�� �����ϴ�.\n", n);
	}
	else
	{
		printf("\n\n�ڷ��߿� %d�� �ֽ��ϴ�.\n", n);
	}


	return 0;
}