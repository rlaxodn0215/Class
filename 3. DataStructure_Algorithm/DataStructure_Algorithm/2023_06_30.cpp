#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
//#include"StopWatch.h"

using namespace std;

int arr[1000001];
int arrtemp[1000001];

void Merge(int start,int middle, int end)
{
	int index = start, i, j, k = 1;
	for (i = start; i <= middle; i++)
	{
		for (j = middle + k; j <= end; j++)
		{
			if (arr[i] >= arr[j])
			{
				arrtemp[index++] = arr[j];
				if (index == end) arrtemp[index] = arr[i];
				k++;
			}

			else
			{
				arrtemp[index++] = arr[i];
				if (index == end) arrtemp[index] = arr[j];
				break;
			}
		}

		if (j > end)
		{
			arrtemp[index++] = arr[i];
		}

	}

	for (int i = start; i <= end; i++)
	{
		arr[i] = arrtemp[i];
	}
}

void func(int* arr,int*arrtemp, int start, int end)
{
	if (start == end && end==0) arrtemp[0] = arr[0];
	if (start == end) return;
	int middle = (end + start) / 2;
	func(arr,arrtemp, start, middle);
	func(arr,arrtemp, middle+1, end);
	Merge(start, middle, end);
}


int main()
{
	int num;
	cin >> num;

	for (int i = 0; i < num; i++)
	{
		cin >> arr[i];
	}

	func(arr,arrtemp, 0, num-1);

	for (int i = 0; i < num; i++)
	{
		cout << arrtemp[i] << "\n";
	}

	return 0;
}