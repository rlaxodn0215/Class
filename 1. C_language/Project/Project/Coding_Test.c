#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>

int main()
{
    int arr[] = { 1, 2, 3, 100, 99, 98 };
    int arr_len = 6;
    int answer = 0;
    int arrtemp[6];

    while (1)
    {
        int count = 0;

        for (int i = 0; i < arr_len; i++)
        {
            arrtemp[i] = arr[i];
        }

        for (int i = 0; i < arr_len; i++)
        {
            if (arrtemp[i] >= 50 && arrtemp[i] % 2 == 0)
            {
                arr[i] = arrtemp[i] / 2;
            }

            else if (arrtemp[i] < 50 && arrtemp[i] % 2 == 1)
            {
                arr[i] = 2 * arrtemp[i] + 1;
            }
            else
            {
                arr[i] = arrtemp[i];
            }
        }

        for (int i = 0; i < arr_len; i++)
        {
            if (arrtemp[i] == arr[i])
            {
                count++;
            }
        }

        if (count == arr_len)
        {
            break;
        }

        answer++;

    }

    printf("%d\n", answer);

    return 0;
}
