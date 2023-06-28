#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include <time.h>

int mid3(int a, int b, int c);
int mid3_Q5(int a, int b, int);

int main()
{
	
	clock_t StartClock = clock();

	for (int i = 0; i < 1000000; i++)
	{
		mid3(3, 2, 1);
	}

	clock_t EndClock = clock();

	printf("mid3() : %lf\n", ((double)EndClock - (double)StartClock) / CLOCKS_PER_SEC);

	StartClock = clock();

	for (int i = 0; i < 1000000; i++)
	{
		mid3_Q5(3, 2, 1);
	}

	EndClock = clock();

	printf("mid3_Q5() : %lf\n", ((double)EndClock - (double)StartClock) / CLOCKS_PER_SEC);


}

int mid3(int a, int b, int c)
{
	if (a >= b)
	{
		if (b >= c)
		{
			return b;
		}

		else if (a >= c)
		{
			return c; // a==c
		}

		else
		{
			return a;
		}
	}

	else if (a >= c)
	{
		return a;
	}

	else if (b >= c)
	{
		return c;
	}

	else
	{
		return b;
	}
}

int mid3_Q5(int a, int b, int c)
{
	if ((b >= a && c <= a) || (b <= a && c >= a))
		return a;
	else if ((a > b && c < b) || (a<b && c>b))
		return b;
	return c;
}