#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

//void print_ary(int* pa, int size);
//void input_ary(double* pa, int size);
//void output_ary(double* pa, int size, double max);
//double find_max(double* pa, int size);
//void input_nums(int* lotto_nums, int size);
//void print_nums(int* lotto_nums, int size);

int main()
{
	/*int ary[5] = { 10,20,30,40,50 };
	int* pa = ary;
	int* pb = pa + 3;

	printf("pa : %u\n", pa);
	printf("pb : %u\n", pb);

	pa++;
	printf("pb - pa : %u\n", pb - pa);

	printf("�տ� �ִ� �迭 ����� �� ��� : ");
	if (pa < pb) printf("%d\n", *pa);
	else printf("%d\n", *pb);*/

	/*
	Q1. ������ �̿��� �ڵ�� ��ȯ
	. ���ڿ��� �Է¹޾Ƽ� �����ǿ� ���ڿ��� �귯������
		��µǴ� ���¿� ���� ���ڿ��� ��µǵ��� ���α׷��� �ۼ��϶�

		ex) hello
		hello
		ello h
		llo he
	*/

	//char sentence[100];
	//char* pSentence = sentence;

	//printf("���� �Է� : ");
	//gets(sentence);
	//int num = 0;
	//
	////���� ���� ���ϱ�
	//while (*(pSentence +num) >= 0 && *(pSentence +num) <= 127)
	//{
	//	num++;
	//}
	//
	//while (1)
	//{
	//	Sleep(200);
	//	system("cls");
	//
	//	int temp = *pSentence;
	//
	//	for (int i = 1; i < num; i++)
	//	{
	//		pSentence[i - 1] = pSentence[i];
	//	}
	//
	//	*(pSentence+num-1) = temp;
	//
	//	for (int i = 0; i < num; i++)
	//	{
	//		printf("%c", pSentence[i]);
	//	}
	//}

	/*
		Q2. ���̰� 6�� int�� �迭 Arr�� �����ϰ� �� 1,2,3,4,5,6���� �ʱ�ȭ �� ������
		�迭�� ����� ���� ������ 6,5,4,3,2,1�� �ǵ��� �����ϴ� ���α׷��� �ۼ��϶�.

		��, �迭�� �� �հ� �ǵڸ� ����Ű�� ������ ���� �� ���� �����Ͽ� �̸� Ȱ���ϸ� ����� ���� ������ �ٲ۴�.
	*/

	//������ ���ڸ� �Է¹޴´�
	//char Arr[100];
	//printf("������ ���ڿ� ���ڸ� �Է��Ͻÿ� : ");
	//gets(Arr);
	//char* pArrFirst = Arr;
	//int num = 0;

	//while ((*(pArrFirst + num) >= 65 && *(pArrFirst + num) <= 122) ||
	//	*(pArrFirst + num) >= 48 && *(pArrFirst + num) <= 57 || (*(pArrFirst + num) == 32))
	//{
	//	num++;
	//}

	//char* pArrLast = Arr + num-1;

	//for (int i = 0; i < (num/2+1); i++)
	//{
	//	char temp = *(Arr + i);
	//	*(Arr + i) = *(Arr + num - i);
	//	*(Arr + num - i) = temp;
	//}
	//
	////puts(Arr);

	//for (int i = 0; i <= num; i++)
	//{
	//	printf("%c",pArrFirst[i]);
	//}

	/*int answer = 0;
	int nDiv = 45;
	int ThreeForward = 0;
	int ThreeReverse = 0;

	for (int i = 0; i < 9; i++)
	{
		ThreeForward += (nDiv % 3) * (10 ^ i);
		nDiv /= 3;
	}
	
	printf("%d", ThreeForward);*/

	/*int ary1[5] = { 10,20,30,40,50 };
	int ary2[7] = { 10,20,30,40,50,60,70 };

	print_ary(ary1, 5);
	printf("\n");
	print_ary(ary2, 7);*/
	
	/*double ary[5];
	double max;
	int size = sizeof(ary) / sizeof(ary[0]);

	input_ary(ary, size);
	max = find_max(ary, size);
	output_ary(ary, size, max);*/

	//int lotto_nums[6];
	//int size = sizeof(lotto_nums) / sizeof(lotto_nums[0]);

	//input_nums(lotto_nums,size);
	//print_nums(lotto_nums,size);
	
	char ch;
	int res;
	int count = -1;
	int max = 0;
	while (1)
	{
		res = scanf("%c", &ch);
		if (res == EOF) break;
		if (res == 1) count++;
		max = (max > count) ? max : count;
		if (ch == '\n') count = -1;
	}


	printf("���� �� �ܾ��� ���� : %d", max);

	
	return 0;
}
//void input_nums(int* lotto_nums, int size)
//{
//	int num = 0;
//
//	do
//	{
//		int count = 0;
//		printf("��ȣ �Է� : ");
//		scanf("%d", lotto_nums +num);
//		for (int i = 0; i < num; i++)
//		{
//
//			if (lotto_nums[num] == lotto_nums[i])
//			{
//				printf("���� ��ȣ�� �ֽ��ϴ�!\n");
//				break;
//			}
//
//			count++;
//		}
//
//		if (count == num)
//		{
//			num++;
//		}
//		
//	} while (num < size);
//}
//
//void print_nums(int* lotto_nums, int size)
//{
//	printf("�ζ� ��ȣ : ");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%d ", lotto_nums[i]);
//	}
//}

//void input_ary(double* pa, int size)
//{
//	int i;
//	printf("%d���� �Ǽ��� �Է� : ", size);
//
//	for (int i = 0; i < size; i++)
//	{
//		scanf("%lf", pa + i);
//	}
//}
//void output_ary(double* pa, int size, double max)
//{
//	printf("�Էµ� �Ǽ��� : ");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.1lf ", *(pa+i));
//	}
//	printf("\n �迭�� �ִ� : %.1lf", max);
//}
//double find_max(double* pa, int size)
//{
//	double max = pa[0];
//
//	for (int i = 1; i < size; i++)
//	{
//		max = (max > pa[i]) ? max : *(pa + i);
//	}
//
//	return max;
//}

//void print_ary(int* pa, int size)
//{
//	int i;
//
//	for (i = 0; i < size; i++)
//	{
//		printf("%d ", pa[i]);
//	}
//}