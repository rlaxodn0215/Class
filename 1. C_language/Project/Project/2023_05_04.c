#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
//void swap(int* pa, int* pb);
void swap(double* pa, double* pb);
void line_up(double* maxp, double* midp, double* minp);

int main()
{
	/*int score[10];
	int i;
	int total = 0;
	double avg;

	int count = sizeof(score) / sizeof(score[0]);

	for (i = 0; i < count; i++)
	{
		scanf("%d", &score[i]);
	}

	for (i = 0; i < count; i++)
	{
		total += score[i];
	}

	avg = (double)total / count;

	for (i = 0; i < count; i++)
	{
		printf("%5d", score[i]);
	}

	printf("\n");

	printf("��� : %.1lf\n", avg);*/

	/*
		Q1. ���̰� 5�� int �迭�� �����ϰ�, ����ڷκ��� 5���� ������ �Է¹޾� ������ ������ ����ϴ� ���α׷��� �ۼ��϶�.

		1. �Էµ� ���� �� �ִ�
		2. �Էµ� ���� �� �ּڰ�
		3. �Էµ� �������� ����
	*/

	//int nums[5], sum=0,max,min;
	//int count = sizeof(nums) / sizeof(nums[0]);

	//printf("5���� ������ �Է��ϼ��� : ");
	//
	////���� �Է�, ���� ���ϱ�
	//for (int i = 0; i < count; i++)
	//{
	//	scanf("%d", &nums[i]);
	//	sum += nums[i];
	//}
	////�ִ�, �ּҰ� ���ϱ�
	//max = nums[0];
	//min = nums[0];
	//for (int i = 1; i < count; i++)
	//{
	//	max = (max > nums[i]) ? max : nums[i];
	//	min = (min < nums[i]) ? min : nums[i];
	//}

	//printf("�Էµ� ���� �� �ִ밪 : %d\n", max);
	//printf("�Էµ� ���� �� �ּҰ� : %d\n", min);
	//printf("�Էµ� �������� ���� : %d\n", sum);

	/*
		Q2. p. 232 ��ҹ��� ��ȯ ���α׷��� �ۼ��ض�
	*/


	//// 1. �ҹ��ڸ� �빮�ڷ�
	//char sentence[80];
	//printf("���� �Է� : ");
	//gets(sentence);
	//int i = 0;
	//
	//while (sentence[i]>=0 && sentence[i]<=127)
	//{
	//	if (sentence[i] >= 97 && sentence[i] <= 122)
	//	{
	//		sentence[i] -= 32;
	//	}

	//	i++;
	//}

	//puts(sentence);

	//// 2. �빮�ڸ� �ҹ��ڷ�
	//char sentence[80];
	//printf("���� �Է� : ");
	//gets(sentence);
	//int i = 0;

	//while (sentence[i] >= 0 && sentence[i] <= 127)
	//{
	//	if (sentence[i] >= 65 && sentence[i] <= 90)
	//	{
	//		sentence[i] += 32;
	//	}

	//	i++;
	//}

	//puts(sentence);

	/*
		Q3. ���ڿ��� �Է¹޾Ƽ� �����ǿ� ���ڿ��� �귯������
		��µǴ� ���¿� ���� ���ڿ��� ��µǵ��� ���α׷��� �ۼ��϶�

		ex) hello
		hello
		ello h
		llo he

		ȭ������� & ��� ��� ���(timer)_sleep
	*/
	
	//char sentence[100];

	//printf("���� �Է� : ");
	//gets(sentence);
	//int num = 0;

	////���� ���� ���ϱ�
	//while (sentence[num] >= 0 && sentence[num] <= 127)
	//{
	//	num++;
	//}

	//while (1)
	//{
	//	Sleep(200);
	//	system("cls");

	//	int temp = sentence[0];

	//	for (int i = 1; i < num; i++)
	//	{
	//		sentence[i - 1] = sentence[i];
	//	}

	//	sentence[num-1] = temp;

	//	for (int i = 0; i < num; i++)
	//	{
	//		printf("%c", sentence[i]);
	//	}
	//}

	/*int a = 10 , b = 20;
	const int* pa = &a;
	printf("���� a�� �� : %d\n", *pa);
	pa = &b;
	printf("���� b�� �� : %d\n", *pa);
	a = 20;
	printf("���� a�� �� : %d\n", *pa);*/

	/*char ch;
	int in;
	double db;

	char* pc = &ch;
	int* pi = &in;
	double* pd = &db;

	printf("char�� ������ �ּ� ũ�� : %d\n", sizeof(&ch));
	printf("int�� ������ �ּ� ũ�� : %d\n", sizeof(&in));
	printf("double�� ������ �ּ� ũ�� : %d\n", sizeof(&db));
	printf("char*�� �������� ũ�� : %d\n", sizeof(pc));
	printf("int*�� �������� ũ�� : %d\n", sizeof(pi));
	printf("double*�� �������� ũ�� : %d\n", sizeof(pd));
	*/

	/*
	Q4. int�� num1, num2�� ����� ���ÿ� 10�� 20���� �ʱ�ȭ ���ְ�,
	int�� ������ ptr1, ptr2�� �����ϰ�
	�� num1�� num2�� �̿��ؼ� num1�� 10 ����, num2�� 10 �����ϰԵȴ�
	���� ptr1�� ptr2�� ����Ű�� ����� ���� �ٲ۴�.
	���������� ptr1�� ptr2�� ����Ű�� ������ ������ ����Ѵ�.
	�� ���� num1,num2�� ����ؼ� ����� ���� ������ Ȯ���Ѵ�.
	*/

	/*int num1 = 10, num2 = 20;
	int* ptr1=&num1, * ptr2=&num2;

	num1 += 10;
	num2 -= 20;

	int temp = ptr1;
	ptr1 = ptr2;
	ptr2 = temp;

	printf("������ ptr1�� ����Ű�� ���� : %d\n", *ptr1);
	printf("������ ptr2�� ����Ű�� ���� : %d\n", *ptr2);
	printf("num1 : %d		num2: %d\n", num1, num2);*/
/*
	int a = 10, b = 20;

	swap(&a, &b);
	printf("a: %d	b: %d\n", a, b);
*/
	double max, mid, min;

	printf("�Ǽ��� 3�� �Է� : ");
	scanf("%lf%lf%lf", &max, &mid, &min);
	line_up(&max, &mid, &min);
	printf("���ĵ� �� ��� : %.1lf, %.1lf, %.1lf\n", max, mid, min);

	return 0;
}

void line_up(double* maxp, double* midp, double* minp)
{
	if (*maxp < *midp) swap(maxp, midp);
	if (*maxp < *minp) swap(maxp, minp);
	if (*midp < *minp) swap(midp, minp);
}

void swap(double* pa, double* pb)
{
	double temp;

	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

//void swap(int* pa, int* pb)
//{
//	int temp = *pa;
//	*pa = *pb;
//	*pb = temp;
//}