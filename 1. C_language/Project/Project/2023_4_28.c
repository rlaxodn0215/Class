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
	//printf("a / b�� ��� : %.1lf\n", res);

	//a = (int)res;
	//printf("(int)%.1lf�� ��� : %d\n", res, a);

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
	printf("ū �� : %d\n", res);*/

	/*
		Q1. ����ڷκ��� ���� 3���� �Է¹޾� �� a,b,c�� ������ �ϰ�
			���� �����ڸ� �̿��Ͽ� �� ������ �߿� ���� ū ���� ���� ����ϴ� ���α׷� �ۼ�
	*/

	/*int a, b, c, big;

	printf("�� ������ �Է��Ͻÿ� : ");
	scanf("%d%d%d", &a, &b, &c);

	(a > b) ? (big = a) : (big = b);
	(big > c) ? big : (big = c);

	printf("���� ū ���� %d �Դϴ�.", big);*/

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
		Q2. �� ���� ������ �Է¹޾� �� ���� ���� ����ϴ� ���α׷��� �ۼ�.
		��, ������ ū ������ ���� ���� ���� �Ѵ�.

		ex) 12 5 -> 7
			4 16 -> 12
	*/

//case 1. if ~else ���� ���

	//int a, b, sub;

	//printf("�� ������ �Է��Ͻÿ� : ");

	//scanf("%d%d", &a, &b);

	//if (a > b)
	//{
	//	sub = a - b;
	//}

	//else
	//{
	//	sub = b - a;
	//}

	//printf("�� ������ ���� %d �Դϴ�.", sub);
	
	

//csae 2. ���� ������ �̿�

	/*int a, b, sub;

	printf("�� ������ �Է��Ͻÿ� : ");

	scanf("%d%d", &a, &b);

	sub = (a > b) ? (a - b) : (b - a);

	printf("�� ������ ���� %d �Դϴ�.", sub);*/

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
	Q3. �л��� ��ü ��� ������ ���� ������ ����ϴ� ���α׷��� �ۼ�
	������ 90�� �̻� A
	������ 80�� �̻� B
	������ 70�� �̻� C
	������ 60�� �̻� D

	���α׷� ����� ����, ����, ������ ������ �Է¹޴´�.
	�� ����� ���ϰ�, �� �򰡱����� �����Ͽ� ������ ������ ����϶�.

*/

	//int Kor, Eng, Mat;
	//float Avg;
	//
	//printf("�������� : ");
	//scanf("%d", &Kor);
	//printf("�������� : ");
	//scanf("%d", &Eng);
	//printf("�������� : ");
	//scanf("%d", &Mat);
	//
	//Avg = (Kor + Eng + Mat) / 3.0f;
	//
	//if (Avg < 60.0f)
	//{
	//	printf("��������� %.2f, ������ F �Դϴ�.", Avg);
	//}
	//
	//else if (Avg < 70.0f)
	//{
	//	printf("��������� %.2f, ������ D �Դϴ�.", Avg);
	//}
	//
	//else if (Avg < 80.0f)
	//{
	//	printf("��������� %.2f, ������ C �Դϴ�.", Avg);
	//}
	//
	//else if (Avg < 90.0f)
	//{
	//	printf("��������� %.2f, ������ B �Դϴ�.", Avg);
	//}

	//else
	//{
	//	printf("��������� %.2f, ������ A �Դϴ�.", Avg);
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
	Q4. Factorial ���, � ���� ���� n�� �Է� �޾Ƽ� n!�� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.
*/

	//int Num, Fac = 1;
	//printf("������ �Է��Ͻÿ� : ");
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
	//printf("%Factorial ���� %d �Դϴ�.", Fac);
	//

/*
	�� ���� �Է¹޾� �� �� ���̿� �����ϴ� ������ ���� ���ϴ� ���α׷� �ۼ�
	ex) 3 5 or 5 3
*/
	//int a, b, Sum=0;
	//printf("�� ������ �Է��Ͻÿ� : ");
	//scanf("%d%d", &a, &b);

	//if (a > b)
	//{
	//	//a,bū ������ �����
	//	int temp = b;
	//	b = a;
	//	a = temp;
	//}

	//else if (a == b)
	//{
	//	printf("���� ���� �Է��Ͽ����ϴ�. �ٽ� ���ּ���.");
	//}

	//else
	//{

	//	for (int i = a; i <= b; i++)
	//	{
	//		Sum += i;
	//	}

	//	printf("�� �� ������ ���� %d �Դϴ�.", Sum);

	//}

	/*
		Q6. ����ڷκ��� ���� ���� M�� N�� �Է¹޾�
		N�� ��ŭ M�� ����� ����ϴ� ���α׷��� �ۼ��ض�

		ex) 3 4
		=> 3 6 9 12
	*/

	//unsigned int M, N;
	//printf("���� ���� M�� N�� �Է��Ͻÿ� : ");
	//scanf("%d%d", &M, &N);

	//if (M < 0 || N < 0)
	//{
	//	printf("������ �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���");
	//}

	//for (int i = 1; i <=N; i++)
	//{
	//	printf("%d\t", M*i);
	//}

/*
Q7. ����ڷκ��� ��� ������ �Է¹޾� �� ���� ���� ������ ���α׷��� �ۼ��϶�.
��, ����ڰ� 0�� �Է��Ҷ����� ��ӵǾ�� �ϸ� 0�� �Է��ϸ� �Էµ� ��� ������ ���� ����Ѵ�. do while
*/

	int Num, Sum = 0;
	
	//do ~ while�� ���

	/*do
	{
		printf("������ �Է��Ͻÿ� : ");
		scanf("%d", &Num);
		Sum += Num;
	} while (Num != 0);

	printf("���ݱ��� ��� ������ ���� %d�Դϴ�.", Sum);*/

	//while�� ���
	/*while (1)
	{
		printf("������ �Է��Ͻÿ� : ");
		scanf("%d", &Num);

		Sum += Num;
		if (Num == 0)
		{
			break;
		}
	}

	printf("���ݱ��� ��� ������ ���� %d�Դϴ�.", Sum);*/



	printf("������ �Է��Ͻÿ� : ");
	scanf("%d", &Num);

	while (Num != 0)
	{
		printf("������ �Է��Ͻÿ� : ");
		scanf("%d", &Num);
		Sum += Num;
	}

	printf("���ݱ��� ��� ������ ���� %d�Դϴ�.", Sum);

	return 0;
}