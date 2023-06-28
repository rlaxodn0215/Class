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

	printf("앞에 있는 배열 요소의 값 출력 : ");
	if (pa < pb) printf("%d\n", *pa);
	else printf("%d\n", *pb);*/

	/*
	Q1. 포인터 이용한 코드로 변환
	. 문자열을 입력받아서 광고판에 문자열이 흘러가듯이
		출력되는 형태와 같이 문자열이 출력되도록 프로그램을 작성하라

		ex) hello
		hello
		ello h
		llo he
	*/

	//char sentence[100];
	//char* pSentence = sentence;

	//printf("문장 입력 : ");
	//gets(sentence);
	//int num = 0;
	//
	////문장 길이 구하기
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
		Q2. 길이가 6인 int형 배열 Arr을 선언하고 각 1,2,3,4,5,6으로 초기화 한 다음에
		배열에 저장된 값의 순서가 6,5,4,3,2,1이 되도록 변경하는 프로그램을 작성하라.

		단, 배열의 맨 앞과 맨뒤를 가리키는 포인터 변수 두 개를 선언하여 이를 활용하며 저장된 값의 순서를 바꾼다.
	*/

	//임의의 숫자를 입력받는다
	//char Arr[100];
	//printf("임의의 숫자와 문자를 입력하시오 : ");
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


	printf("가장 긴 단어의 길이 : %d", max);

	
	return 0;
}
//void input_nums(int* lotto_nums, int size)
//{
//	int num = 0;
//
//	do
//	{
//		int count = 0;
//		printf("번호 입력 : ");
//		scanf("%d", lotto_nums +num);
//		for (int i = 0; i < num; i++)
//		{
//
//			if (lotto_nums[num] == lotto_nums[i])
//			{
//				printf("같은 번호가 있습니다!\n");
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
//	printf("로또 번호 : ");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%d ", lotto_nums[i]);
//	}
//}

//void input_ary(double* pa, int size)
//{
//	int i;
//	printf("%d개의 실수값 입력 : ", size);
//
//	for (int i = 0; i < size; i++)
//	{
//		scanf("%lf", pa + i);
//	}
//}
//void output_ary(double* pa, int size, double max)
//{
//	printf("입력된 실수값 : ");
//	for (int i = 0; i < size; i++)
//	{
//		printf("%.1lf ", *(pa+i));
//	}
//	printf("\n 배열의 최댓값 : %.1lf", max);
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