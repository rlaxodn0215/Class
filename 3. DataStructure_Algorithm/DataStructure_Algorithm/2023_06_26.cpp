#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include"StopWatch.h"

using namespace std;

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void func(int * arr,int arrlen)
{
	int checknum = arrlen /2;
	int compareCount = 0;
	int exchangeCount = 0;


	while (checknum)
	{
		for (int i = 0; i + checknum < arrlen; i++)
		{
			for (int j = i + checknum; j < arrlen; j += checknum)
			{
				if (arr[i] > arr[j])
				{
					swap(arr[i], arr[j]);
					exchangeCount++;
				}
				compareCount++;
			}
		}
		checknum /= 2;
	}


	for (int i = 0; i < arrlen; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl << "비교 횟수: " << compareCount << endl;
	cout << "교환 횟수: " << exchangeCount << endl;
	
}

int main()
{
	StopWatch time;

	time.Start();
	for (int i = 0; i < 1000; i++)
	{
		int arr[9] = { 8,1,4,2,7,6,3,5,9 };
		func(arr, 9);
	}
	time.Stop();

	cout << "걸린 시간은: " << time.getElapsedTime() << "ms 입니다." << endl;
	return 0;
}