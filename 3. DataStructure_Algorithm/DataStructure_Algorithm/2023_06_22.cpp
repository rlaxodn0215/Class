#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include"StopWatch.h"

using namespace std;

void swap(int & a, int & b)
{
	int temp = a;
	a = b;
	b = temp;
}

void func(int * arr, int arrlen)
{
	for (int i = 1; i < arrlen; i++)
	{
		bool changePoint=false;

		for (int k = 0; k < arrlen; k++)
		{
			cout << " " << arr[k] << " ";
		}
		cout << endl;

		for (int j = 0; j < i ; j++)
		{
			if (arr[j]> arr[i])
			{

				changePoint = true;

				for (int n = 0; n < arrlen; n++)
				{
					if (n == j)
					{
						cout << "^--";
					}

					else if (n> j && n<i)
					{
						cout << "---";
					}

					else if (n < j)
					{
						cout << "   ";
					}

					else
					{
						cout << "-+";
						break;
					}
				}

				cout << endl;
				break;
			}
		}

		for (int s =i-1; s >= 0; s--)
		{
			if (arr[s] > arr[s+1])
			{
				swap(arr[s], arr[s+1]);

			}
		}


		if (!changePoint)
		{
			for (int n = 0; n < arrlen; n++)
			{

				if (n == i)
				{
					cout << " +";
					break;
				}

				else
				{
					cout << "   ";
				}
			}
			cout << endl;
		}
	}

	for (int k = 0; k < arrlen; k++)
	{
		cout << " " << arr[k] << " ";
	}
	cout << endl;

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