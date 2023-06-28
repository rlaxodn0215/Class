#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>

int main()
{
    int arr[6] = { 1,2,3,4,5,6 };
    int arr_len = 6;

    int n = 1;
    while (1)
    {
        if (arr_len > pow(2, n - 1) && arr_len <= pow(2, n))
        {
            break;
        }
        n++;
    }

    int* answer = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < arr_len; i++)
    {
        answer[i] = arr[i];
    }

    for (int i = arr_len; i < n; i++)
    {
        answer[i] = 0;
    }

    free(answer);
	return 0;
}

