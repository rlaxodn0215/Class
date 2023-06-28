#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//int sum(int , int );
//int InputFunc();
//void OutputFunc(int a);
//void Abs(int num);
//int Sum(int n);
//int Fac(int n);
//int birth(int months);
void Calc(int n);
int Add(int a, int b);
int Sub(int a, int b);
int Muti(int a, int b);
double Div(int a, int b);

int main()
{
	/*
		Q1. p177 도전 실전 예제

	*/

	//int n;
	//int nextLine = 0;
	//printf("2 이상의 정수를 입력하시오 : ");
	//scanf("%d", &n);

	//for (int i = 2; i <= n; i++)
	//{
	//	int count = 0;

	//	for (int j = 1; j <= i; j++)
	//	{
	//		if (i % j == 0) count++;
	//	}

	//	if (count == 2) //1과 n만 나누었을 때 나오는 횟수
	//	{
	//		printf("%d\t", i);
	//		nextLine++;
	//		if (nextLine == 5)
	//		{
	//			printf("\n");
	//			nextLine = 0;
	//		}
	//	}
	//		

	//}

	/*
		Q2. 다음 식을 만족하는 모든 A와 Z를 구하는 프로그램을 작성하라.

		A  Z
	+	Z  A
	-----------
		N  N

		ex) n을 입력하시오.
		
		n = 9

		A  Z
	+	Z  A
	-----------
		9  9
	*/

	//int n;
	//printf("0~9까지의 정수를 입력하시오 : ");
	//scanf("%d", &n);

	//for (int i = 0; i <= n; i++)
	//{
	//	//i+j=n
	//	int j = n - i;
	//	printf("A : %d   Z: %d\n", i, j);
	//}


	/*int a = 10, b = 20;
	int s = 0;
	s = sum(a, b);

	printf("%d\n", s);*/

	/*
		Q3. 1. 입력함수
			2. 출력함수
	*/

	/*int result = InputFunc();
	OutputFunc(result);*/

	/*
		Q3. 입력받는 값의 절댓값을 구하는 함수 abs()를 구현하라.
		종료하려면 0을 입력하시오
		정수입력 : -34
		절댓값은 : 34
	*/

	/*int n;

	do
	{
		printf("절댓값을 구하라 (종료하려면 0을 입력하시오) : ");
		scanf("%d", &n);
		Abs(n);

	} while (n);*/

	//int n;
	//printf("양수 입력 : ");
	//scanf("%d", &n);
	//printf("합: %d      곱: %d", Sum(n), Fac(n));

	/*
		Q6. 달팽이 한 마리가 한달이 지나면 어른이 되고 
		다시 한달이 지나면 새끼를 낳는다.
		새로 태어난 달팽이 역시 한달이 지나면
		어른이 되고, 다시 한달 후 부터 새끼를 낳는 다고 할 때,
		달팽이가 매달 새끼를 낳으면 1년 후 전체 달팽이 수를 얼마인다?
	*/

	/*int months = 12 ;

	printf("달팽이의 수 : %d", birth(months));*/

	/*
		Q7. 사직연산을 위한 프로그램을 작성해라
		출력형태는 다음과 같다.
		ex) 원하는 연산을 선택하시오 (1: 덧셈, 2: 뺄셈, 3: 곱셈, 4: 나눗셈, 0:종료)
		입력:
		> 1
		> 두 정수를 입력하시오: 00 00
		> 결과는 00입니다.
	*/

	int n=0;

	do
	{
		printf("원하는 연산을 선택하시오 : 1.덧셈, 2.뺄셈, 3.곱셈, 4.나눗셈, 0:종료\n");
		printf("입력 : ");
		scanf("%d", &n);
		Calc(n);

	} while (n);

	return 0;
}

void Calc(int n)
{
	int a=0, b=0;

	switch (n)
	{
	case 1:
	{
		printf("두 정수를 입력하시오 : ");
		scanf("%d%d", &a, &b);
		int result = Add(a, b);
		printf("결과는 %d 입니다.\n", result);
	}
		break;
	case 2:
	{
		printf("두 정수를 입력하시오 : ");
		scanf("%d%d", &a, &b);
		int result = Sub(a, b);
		printf("결과는 %d 입니다.\n", result);
	}
		break;
	case 3:
	{
		printf("두 정수를 입력하시오 : ");
		scanf("%d%d", &a, &b);
		int result = Muti(a, b);
		printf("결과는 %d 입니다.\n", result);
	}
		break;
	case 4:
	{
		printf("두 정수를 입력하시오 : ");
		scanf("%d%d", &a, &b);
		double result = Div(a, b);
		printf("결과는 %.2lf 입니다.\n", result);
	}
		break;
	default:
	{
		printf("종료합니다.");
		return;
	}
		break;
	}
}

int Add(int a, int b)
{
	return a + b;
}

int Sub(int a, int b)
{
	return a - b;
}

int Muti(int a, int b)
{
	return a * b;
}

double Div(int a, int b)
{
	return (double)a / b;
}

//int birth(int months)
//{
//	if (months == 1) return 1;
//	if (months == 2) return 2;
//	int sum = birth(months - 2) + birth(months - 1);
//	return sum;
//}


//int Sum(int n)
//{
//	if (n == 1) return 1;
//	int sum = n + Sum(n - 1);
//
//	return sum;
//}
//
//int Fac(int n)
//{
//	if (n == 1) return 1;
//	int fac = n*Fac(n - 1);
//
//	return fac;
//}



//void Abs(int num)
//{
//	if (num == 0)
//	{
//		printf("\n종료합니다.");
//	}
//
//	else if (num > 0)
//	{
//		printf("정수입력 : %d\n", num);
//		printf("절댓값은 : %d\n\n", num);
//	}
//
//	else
//	{
//		printf("정수입력 : %d\n", num);
//		printf("절댓값은 : %d\n\n", -num);
//	}
//}

//int InputFunc()
//{
//	int n;
//	printf("2 이상의 정수를 입력하시오 : ");
//	scanf("%d", &n);
//	return n;
//}
//
//void OutputFunc(int n)
//{
//	int nextLine = 0;
//
//	for (int i = 2; i <= n; i++)
//	{
//		int count = 0;
//
//		for (int j = 1; j <= i; j++)
//		{
//			if (i % j == 0) count++;
//		}
//
//		if (count == 2) //1과 n만 나누었을 때 나오는 횟수
//		{
//			printf("%d\t", i);
//			nextLine++;
//			if (nextLine == 5)
//			{
//				printf("\n");
//				nextLine = 0;
//			}
//		}
//	}
//}

//int sum(int x1, int y1) 
//{
//	int result = x1 + y1;
//	return result;
//}