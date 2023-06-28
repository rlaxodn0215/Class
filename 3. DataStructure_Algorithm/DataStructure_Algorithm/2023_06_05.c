#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include <time.h>

void UpCounting(const int* x, const int nx);
void* bsearchx(const void* key, const void* base, size_t nmemb, size_t size, int(*compar)(const void*, const void*));
int compar(const int* a, const int* b);

int main()
{
	int nx, ky;
	printf("요소 개수: ");
	scanf("%d", &nx);

	int* x = (int*)calloc(nx, sizeof(int));

	UpCounting(x, nx);
	
	printf("검색값: ");
	scanf("%d", &ky);

	int* p = bsearchx(&ky, x, nx, sizeof(int), compar);

	if (p == NULL)
	{
		puts("검색에 실패하였습니다.");
	}

	else
	{
		printf("%d는 x[%d]에 있습니다.\n", ky, (int)(p - x));
	}

	return 0;
}

void* bsearchx(const void* key, const void* base, size_t nmemb, size_t size, int(*compar)(const void*, const void*))
{
	int checkNum =(int)nmemb / 2;
	int length = (int)nmemb / 4;
	int count = (log10((int)nmemb) / log10(2)) + 1;

	int* p = (int*)base;
	int* ky = key;

	while (count > 0)
	{
		int cpr = compar(key, &p[checkNum]);

		if (cpr > 0)
		{
			checkNum += length;
			length /= 2;
			if (length < 1) length = 1;
			count--;
		}

		else if (cpr < 0)
		{
			checkNum -= length;
			length /= 2;
			if (length < 1) length = 1;
			count--;
		}

		else
		{
			while (p[checkNum] == *ky)
			{
				checkNum--;
			}

			return &p[checkNum+1];
		}
	}

	return NULL;
}

int compar(const int* a, const int* b)
{
	if (*a > *b) return 1;
	else if (*a < *b) return -1;
	else return 0;
}

void UpCounting(const int* x, const int nx)
{
	printf("x[0]: ");
	scanf("%d", &x[0]);

	for (int i = 1; i < nx; i++)
	{
		do
		{
			printf("x[%d]: ", i);
			scanf("%d", &x[i]);
		} while (x[i] < x[i - 1]);
	}
}