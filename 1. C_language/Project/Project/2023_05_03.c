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
		Q1. p177 ���� ���� ����

	*/

	//int n;
	//int nextLine = 0;
	//printf("2 �̻��� ������ �Է��Ͻÿ� : ");
	//scanf("%d", &n);

	//for (int i = 2; i <= n; i++)
	//{
	//	int count = 0;

	//	for (int j = 1; j <= i; j++)
	//	{
	//		if (i % j == 0) count++;
	//	}

	//	if (count == 2) //1�� n�� �������� �� ������ Ƚ��
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
		Q2. ���� ���� �����ϴ� ��� A�� Z�� ���ϴ� ���α׷��� �ۼ��϶�.

		A  Z
	+	Z  A
	-----------
		N  N

		ex) n�� �Է��Ͻÿ�.
		
		n = 9

		A  Z
	+	Z  A
	-----------
		9  9
	*/

	//int n;
	//printf("0~9������ ������ �Է��Ͻÿ� : ");
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
		Q3. 1. �Է��Լ�
			2. ����Լ�
	*/

	/*int result = InputFunc();
	OutputFunc(result);*/

	/*
		Q3. �Է¹޴� ���� ������ ���ϴ� �Լ� abs()�� �����϶�.
		�����Ϸ��� 0�� �Է��Ͻÿ�
		�����Է� : -34
		������ : 34
	*/

	/*int n;

	do
	{
		printf("������ ���϶� (�����Ϸ��� 0�� �Է��Ͻÿ�) : ");
		scanf("%d", &n);
		Abs(n);

	} while (n);*/

	//int n;
	//printf("��� �Է� : ");
	//scanf("%d", &n);
	//printf("��: %d      ��: %d", Sum(n), Fac(n));

	/*
		Q6. ������ �� ������ �Ѵ��� ������ ��� �ǰ� 
		�ٽ� �Ѵ��� ������ ������ ���´�.
		���� �¾ ������ ���� �Ѵ��� ������
		��� �ǰ�, �ٽ� �Ѵ� �� ���� ������ ���� �ٰ� �� ��,
		�����̰� �Ŵ� ������ ������ 1�� �� ��ü ������ ���� ���δ�?
	*/

	/*int months = 12 ;

	printf("�������� �� : %d", birth(months));*/

	/*
		Q7. ���������� ���� ���α׷��� �ۼ��ض�
		������´� ������ ����.
		ex) ���ϴ� ������ �����Ͻÿ� (1: ����, 2: ����, 3: ����, 4: ������, 0:����)
		�Է�:
		> 1
		> �� ������ �Է��Ͻÿ�: 00 00
		> ����� 00�Դϴ�.
	*/

	int n=0;

	do
	{
		printf("���ϴ� ������ �����Ͻÿ� : 1.����, 2.����, 3.����, 4.������, 0:����\n");
		printf("�Է� : ");
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
		printf("�� ������ �Է��Ͻÿ� : ");
		scanf("%d%d", &a, &b);
		int result = Add(a, b);
		printf("����� %d �Դϴ�.\n", result);
	}
		break;
	case 2:
	{
		printf("�� ������ �Է��Ͻÿ� : ");
		scanf("%d%d", &a, &b);
		int result = Sub(a, b);
		printf("����� %d �Դϴ�.\n", result);
	}
		break;
	case 3:
	{
		printf("�� ������ �Է��Ͻÿ� : ");
		scanf("%d%d", &a, &b);
		int result = Muti(a, b);
		printf("����� %d �Դϴ�.\n", result);
	}
		break;
	case 4:
	{
		printf("�� ������ �Է��Ͻÿ� : ");
		scanf("%d%d", &a, &b);
		double result = Div(a, b);
		printf("����� %.2lf �Դϴ�.\n", result);
	}
		break;
	default:
	{
		printf("�����մϴ�.");
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
//		printf("\n�����մϴ�.");
//	}
//
//	else if (num > 0)
//	{
//		printf("�����Է� : %d\n", num);
//		printf("������ : %d\n\n", num);
//	}
//
//	else
//	{
//		printf("�����Է� : %d\n", num);
//		printf("������ : %d\n\n", -num);
//	}
//}

//int InputFunc()
//{
//	int n;
//	printf("2 �̻��� ������ �Է��Ͻÿ� : ");
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
//		if (count == 2) //1�� n�� �������� �� ������ Ƚ��
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