#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	//int a = 20, b = 3;
	//double res;

	//res = (a) / ((double)b);
	//printf("a = %d, b = %d\n", a, b);
	//printf("a / b의 결과 : %.1lf\n", res);

	//a = (int)res;
	//printf("(int)%.1lf의 결과 : %d\n", res, a);

	//int i = 10;
	//double d = i;

	//printf("%d\n", sizeof(char));
	//printf("%d\n", sizeof(int));
	//printf("%d\n", sizeof(double));

	//int a = 10, b = 20;
	//int res = 2;

	//a += 20;
	//res *= (b + 10);

	//printf("a = %d, b = %d\n", a, b);
	//printf("res = %d\n", res);
	
	/*int a = 10, b = 20, res;
	res = (a > b) ? a : b;
	printf("큰 값 : %d\n", res);*/

	/*
		Q1. 사용자로부터 정수 3개를 입력받아 각 a,b,c에 저장을 하고
			조건 연산자를 이용하여 이 변수들 중에 가장 큰 값을 구해 출력하는 프로그램 작성
	*/

	/*int a, b, c, big;

	printf("세 정수를 입력하시오 : ");
	scanf("%d%d%d", &a, &b, &c);

	(a > b) ? (big = a) : (big = b);
	(big > c) ? big : (big = c);

	printf("가장 큰 값은 %d 입니다.", big);*/

	//int a = 10; // 0x0000 000A		
	//int b = 12; // 0x0000 000C	

	//printf("a & b : %d\n", a & b);
	//printf("a ^ b : %d\n", a ^ b);
	//printf("a | b : %d\n", a | b);
	//printf("~a : %d\n", ~a);
	//printf("a<<1 : %d\n", a<<1);
	//printf("a>>2 : %d\n", a>>2);
	
	//int a = 20;
	//int b = 0;

	//if (a > 10)
	//{
	//	b = a;
	//}

	//printf("a : %d, b : %d\n", a, b);

	/*int a = 7;

	if (a >= 10)
	{
		a = 1;
	}
	else
	{
		a = -1;
	}

	printf("a : %d\n", a);*/

	/*int a = 0, b = 0;

	if (a > b)
	{
		b = 1;
	}

	else if (a == 0)
	{
		b = 2;
	}

	else
	{
		b = 3;
	}

	printf("b : %d\n", b);*/

	/*
		Q2. 두 개의 정수를 입력받아 두 수의 차를 출력하는 프로그램을 작성.
		단, 무조건 큰 수에서 작은 수를 뺴야 한다.

		ex) 12 5 -> 7
			4 16 -> 12
	*/

//case 1. if ~else 문을 사용

	//int a, b, sub;

	//printf("두 정수를 입력하시오 : ");

	//scanf("%d%d", &a, &b);

	//if (a > b)
	//{
	//	sub = a - b;
	//}

	//else
	//{
	//	sub = b - a;
	//}

	//printf("두 정수의 차는 %d 입니다.", sub);
	
	

//csae 2. 조건 연산자 이용

	/*int a, b, sub;

	printf("두 정수를 입력하시오 : ");

	scanf("%d%d", &a, &b);

	sub = (a > b) ? (a - b) : (b - a);

	printf("두 정수의 차는 %d 입니다.", sub);*/

	//int rank = 2, m = 0;

	//switch (rank)
	//{
	//case 1:
	//	m = 300;
	//	break;
	//case 2:
	//	m = 200;
	//	//break;
	//case 3:
	//	m = 100;
	//	break;
	//default:
	//	m = 10;
	//	break;
	//}

	//printf("m: %d\n", m);
/*
	Q3. 학생이 전체 평균 점수에 대한 학점을 출력하는 프로그램을 작성
	성적이 90점 이상 A
	성적이 80점 이상 B
	성적이 70점 이상 C
	성적이 60점 이상 D

	프로그램 실행시 국어, 영어, 수학의 점수를 입력받는다.
	그 평균을 구하고, 위 평가기준을 참고하여 적절한 학점을 출력하라.

*/

	//int Kor, Eng, Mat;
	//float Avg;
	//
	//printf("국어점수 : ");
	//scanf("%d", &Kor);
	//printf("영어점수 : ");
	//scanf("%d", &Eng);
	//printf("수학점수 : ");
	//scanf("%d", &Mat);
	//
	//Avg = (Kor + Eng + Mat) / 3.0f;
	//
	//if (Avg < 60.0f)
	//{
	//	printf("평균점수는 %.2f, 학점은 F 입니다.", Avg);
	//}
	//
	//else if (Avg < 70.0f)
	//{
	//	printf("평균점수는 %.2f, 학점은 D 입니다.", Avg);
	//}
	//
	//else if (Avg < 80.0f)
	//{
	//	printf("평균점수는 %.2f, 학점은 C 입니다.", Avg);
	//}
	//
	//else if (Avg < 90.0f)
	//{
	//	printf("평균점수는 %.2f, 학점은 B 입니다.", Avg);
	//}

	//else
	//{
	//	printf("평균점수는 %.2f, 학점은 A 입니다.", Avg);
	//}
	
	/*int a = 1;

	while (a<10)
	{
		printf("%d\n", a);
		a *= 2;
	}


	for (int a = 1;a<10;a*=2)
	{
		printf("%d\n", a);
	}
	*/

/*
	Q4. Factorial 계산, 어떤 양의 정수 n을 입력 받아서 n!를 구하는 프로그램을 작성하시오.
*/

	//int Num, Fac = 1;
	//printf("정수를 입력하시오 : ");
	//scanf("%d", &Num);

	///*for (int i = 1;i<=num;i++)
	//{
	//	fac *= i;
	//}*/

	//while (Num>0)
	//{
	//	Fac *= Num;
	//	Num--;
	//}
	//
	//printf("%Factorial 값은 %d 입니다.", Fac);
	//

/*
	두 수를 입력받아 두 수 사이에 존재하는 정수의 합을 구하는 프로그램 작성
	ex) 3 5 or 5 3
*/
	//int a, b, Sum=0;
	//printf("두 정수를 입력하시오 : ");
	//scanf("%d%d", &a, &b);

	//if (a > b)
	//{
	//	//a,b큰 순서로 만들기
	//	int temp = b;
	//	b = a;
	//	a = temp;
	//}

	//else if (a == b)
	//{
	//	printf("같은 수를 입력하였습니다. 다시 해주세요.");
	//}

	//else
	//{

	//	for (int i = a; i <= b; i++)
	//	{
	//		Sum += i;
	//	}

	//	printf("두 수 사이의 합은 %d 입니다.", Sum);

	//}

	/*
		Q6. 사용자로부터 양의 정수 M과 N을 입력받아
		N개 만큼 M의 배수를 출력하는 프로그램을 작성해라

		ex) 3 4
		=> 3 6 9 12
	*/

	//unsigned int M, N;
	//printf("양의 정수 M과 N을 입력하시오 : ");
	//scanf("%d%d", &M, &N);

	//if (M < 0 || N < 0)
	//{
	//	printf("음수를 입력하였습니다. 다시 입력하세요");
	//}

	//for (int i = 1; i <=N; i++)
	//{
	//	printf("%d\t", M*i);
	//}

/*
Q7. 사용자로부터 계속 정수를 입력받아 그 값을 더해 나가는 프로그램을 작성하라.
단, 사용자가 0을 입력할때까지 계속되어야 하며 0이 입력하면 입력된 모든 정수의 합을 출력한다. do while
*/

	int Num, Sum = 0;
	
	//do ~ while문 사용

	/*do
	{
		printf("정수를 입력하시오 : ");
		scanf("%d", &Num);
		Sum += Num;
	} while (Num != 0);

	printf("지금까지 모든 정수의 합은 %d입니다.", Sum);*/

	//while문 사용
	/*while (1)
	{
		printf("정수를 입력하시오 : ");
		scanf("%d", &Num);

		Sum += Num;
		if (Num == 0)
		{
			break;
		}
	}

	printf("지금까지 모든 정수의 합은 %d입니다.", Sum);*/



	printf("정수를 입력하시오 : ");
	scanf("%d", &Num);

	while (Num != 0)
	{
		printf("정수를 입력하시오 : ");
		scanf("%d", &Num);
		Sum += Num;
	}

	printf("지금까지 모든 정수의 합은 %d입니다.", Sum);

	return 0;
}