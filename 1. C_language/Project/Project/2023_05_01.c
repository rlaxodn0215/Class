#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	/*
		Q1. 1이상 100미만인 정수 m과 n을 입력받아 
			두 수의 배수를 출력하는 프로그램을 작성.
			단, m의 배수이면서 n의 배수인 정수는 한번만 출력한다.

			ex) 7 9
			7 9 14 18 21 27
	*/

	/*int m, n;

	printf("두 정수를 입력하시오 : ");
	scanf("%d %d", &m, &n);

	for (int i = 1; i <= 100; i++)
	{
		if (i % m == 0 || i % n == 0)
		{
			printf("%d  ", i);
		}
		
	}*/

	/*
		Q2. 임의의 n을 입력받아서 다음과 같은 형태로 출력하도록 한다.

		ex) n==5인경우
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
			if (i >= j) // 공백도 넣자
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
	Q3. 임의의 수 n의 입력을 받아 다음과 같은 형태가 되도록 프로그램을 작성하라
	
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
	* 자릿수 맞추어 출력하기 %  d
		Q4. 다음과 같이 형태가 되도록 구구단을 출력하라.
		원하는 단을 n을 입력받아 n단까지 출력한다.

		ex) n = 6 (2단 ~ 18단) 

						구 구 단
	 ---------------------------------------------------

	 2 X 1 = 2			3 X 1 = 3		4 X 1 = 4
	 2 X 2 = 4			3 X 2 = 6		4 X 2 = 6

	 ...



	 2 X 9 = 18
	 ----------------------------------------------------
	 5 X 1 =5
	*/

	int n;
	printf("구구단의 단수를 적으세요 : ");
	scanf("%d", &n);

	printf("\n\t\t구\t구\t단\n");

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