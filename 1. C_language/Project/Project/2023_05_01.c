#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	/*
		Q1. 1�̻� 100�̸��� ���� m�� n�� �Է¹޾� 
			�� ���� ����� ����ϴ� ���α׷��� �ۼ�.
			��, m�� ����̸鼭 n�� ����� ������ �ѹ��� ����Ѵ�.

			ex) 7 9
			7 9 14 18 21 27
	*/

	/*int m, n;

	printf("�� ������ �Է��Ͻÿ� : ");
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= 100; i++)
	{
		if (i % m == 0 || i % n == 0)
		{
			printf("%d  ", i);
		}
		
	}*/

	/*
		Q2. ������ n�� �Է¹޾Ƽ� ������ ���� ���·� ����ϵ��� �Ѵ�.

		ex) n==5�ΰ��
	*
	**
	***
	****
	*****
		
		 *
		**
	   ***
	  ****
	 *****
    */

	/*int n;
	printf("n : ");
	scanf("%d", &n);

	for (int i = 0;i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i >= j) // ���鵵 ����
			{
				printf("*");
			}
		}
		printf("\n");
	}*/

	/*int n;
	printf("n : ");
	scanf("%d", &n);

	for (int i = n; i > 0; i--)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i > j)
			{
				printf(" ");
			}

			else
			{
				printf("*");
			}
		
		}
		printf("\n");
	}*/

	/*int n;
	printf("n : ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((i == j) || (i+j==n-1))
			{
				printf("*");
			}

			else
			{
				printf(" ");
			}
		}

		printf("\n");

	}*/

/*
	Q3. ������ �� n�� �Է��� �޾� ������ ���� ���°� �ǵ��� ���α׷��� �ۼ��϶�
	
	ex) n==5
	*   *
	** **
	*****
	** **
	*   *
	
	n==4
	*  *
	****
	****
	*  *
*/
	/*int n;
	printf("n : ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (((i <= j) && (i + j >= n-1))||((i >= j) && (i + j <= n-1)))
			{
				printf("*");
			}

			else
			{
				printf(" ");
			}
		}

		printf("\n");
	}*/
	

	/*
	* �ڸ��� ���߾� ����ϱ� %  d
		Q4. ������ ���� ���°� �ǵ��� �������� ����϶�.
		���ϴ� ���� n�� �Է¹޾� n�ܱ��� ����Ѵ�.

		ex) n = 6 (2�� ~ 18��) 

						�� �� ��
	 ---------------------------------------------------

	 2 X 1 = 2			3 X 1 = 3		4 X 1 = 4
	 2 X 2 = 4			3 X 2 = 6		4 X 2 = 6

	 ...



	 2 X 9 = 18
	 ----------------------------------------------------
	 5 X 1 =5
	*/

	int n;
	printf("�������� �ܼ��� �������� : ");
	scanf("%d", &n);

	printf("\n\t\t��\t��\t��\n");

	for (int i = 2; i <= n; i+=3)
	{
		printf("-------------------------------------------------------\n");

			for (int j = 1; j <=9; j++)
			{
				for (int k = 0; k <= 2; k++)
				{
					if (i + k <= n)
					{ 
						printf("%2d X %d = %d\t", i + k, j, (i + k) * j);
					}
				}

				printf("\n");
			}

		printf("\n");
	}

	return 0;
}