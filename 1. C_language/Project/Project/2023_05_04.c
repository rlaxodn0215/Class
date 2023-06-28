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

	printf("평균 : %.1lf\n", avg);*/

	/*
		Q1. 길이가 5인 int 배열을 선언하고, 사용자로부터 5개의 정수를 입력받아 다음의 내용을 출력하는 프로그램을 작성하라.

		1. 입력된 정수 중 최댓값
		2. 입력된 정수 중 최솟값
		3. 입력된 정수들의 종합
	*/

	//int nums[5], sum=0,max,min;
	//int count = sizeof(nums) / sizeof(nums[0]);

	//printf("5개의 정수를 입력하세요 : ");
	//
	////정수 입력, 종합 구하기
	//for (int i = 0; i < count; i++)
	//{
	//	scanf("%d", &nums[i]);
	//	sum += nums[i];
	//}
	////최대, 최소값 구하기
	//max = nums[0];
	//min = nums[0];
	//for (int i = 1; i < count; i++)
	//{
	//	max = (max > nums[i]) ? max : nums[i];
	//	min = (min < nums[i]) ? min : nums[i];
	//}

	//printf("입력된 정수 중 최대값 : %d\n", max);
	//printf("입력된 정수 중 최소값 : %d\n", min);
	//printf("입력된 정수들의 종합 : %d\n", sum);

	/*
		Q2. p. 232 대소문자 변환 프로그램을 작성해라
	*/


	//// 1. 소문자를 대문자로
	//char sentence[80];
	//printf("문장 입력 : ");
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

	//// 2. 대문자를 소문자로
	//char sentence[80];
	//printf("문장 입력 : ");
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
		Q3. 문자열을 입력받아서 광고판에 문자열이 흘러가듯이
		출력되는 형태와 같이 문자열이 출력되도록 프로그램을 작성하라

		ex) hello
		hello
		ello h
		llo he

		화면지우기 & 잠시 대기 기능(timer)_sleep
	*/
	
	//char sentence[100];

	//printf("문장 입력 : ");
	//gets(sentence);
	//int num = 0;

	////문장 길이 구하기
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
	printf("변수 a의 값 : %d\n", *pa);
	pa = &b;
	printf("변수 b의 값 : %d\n", *pa);
	a = 20;
	printf("변수 a의 값 : %d\n", *pa);*/

	/*char ch;
	int in;
	double db;

	char* pc = &ch;
	int* pi = &in;
	double* pd = &db;

	printf("char형 변수의 주소 크기 : %d\n", sizeof(&ch));
	printf("int형 변수의 주소 크기 : %d\n", sizeof(&in));
	printf("double형 변수의 주소 크기 : %d\n", sizeof(&db));
	printf("char*형 포인터의 크기 : %d\n", sizeof(pc));
	printf("int*형 포인터의 크기 : %d\n", sizeof(pi));
	printf("double*형 포인터의 크기 : %d\n", sizeof(pd));
	*/

	/*
	Q4. int형 num1, num2를 선언과 동시에 10과 20으로 초기화 해주고,
	int형 포인터 ptr1, ptr2를 선언하고
	각 num1과 num2를 이용해서 num1은 10 증가, num2는 10 감소하게된다
	이후 ptr1과 ptr2가 가리키는 대상을 서로 바꾼다.
	마지막으로 ptr1과 ptr2가 가리키는 변수의 내용을 출력한다.
	각 변수 num1,num2도 출력해서 저장된 값이 같은지 확인한다.
	*/

	/*int num1 = 10, num2 = 20;
	int* ptr1=&num1, * ptr2=&num2;

	num1 += 10;
	num2 -= 20;

	int temp = ptr1;
	ptr1 = ptr2;
	ptr2 = temp;

	printf("포인터 ptr1이 가리키는 변수 : %d\n", *ptr1);
	printf("포인터 ptr2이 가리키는 변수 : %d\n", *ptr2);
	printf("num1 : %d		num2: %d\n", num1, num2);*/
/*
	int a = 10, b = 20;

	swap(&a, &b);
	printf("a: %d	b: %d\n", a, b);
*/
	double max, mid, min;

	printf("실수값 3개 입력 : ");
	scanf("%lf%lf%lf", &max, &mid, &min);
	line_up(&max, &mid, &min);
	printf("정렬된 값 출력 : %.1lf, %.1lf, %.1lf\n", max, mid, min);

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