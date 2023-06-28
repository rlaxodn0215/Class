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

void func1(int *arr, int arrlen)
{
	for (int i = 0; i < arrlen; i++)
	{
		int min = i;

		for (int j = i+1; j < arrlen; j++)
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
		}

		for (int k = 0; k < arrlen; k++)
		{
			if (k == i)
			{
				cout << "* ";
			}

			else if(k==min)
			{
				cout << "+ ";
			}

			else
			{
				cout << "  ";
			}
		}
		cout << endl;

		for (int t = 0; t < arrlen; t++)
		{
			cout << arr[t] << " ";
		}
		cout << endl;

		swap(arr[min], arr[i]);
	}


}

void func2(int* arr, int arrlen)
{
	for (int i = 0; i < arrlen; i++)
	{

		for (int j = i + 1; j < arrlen; j++)
		{
			if (arr[i] > arr[j])
			{

				for (int k = 0; k < arrlen; k++)
				{
					if (k == i)
					{
						cout << "* ";
					}

					else if (k == j)
					{
						cout << "+ ";
					}

					else
					{
						cout << "  ";
					}
				}
				cout << endl;

				for (int t = 0; t < arrlen; t++)
				{
					cout << arr[t] << " ";
				}
				cout << endl;

				swap(arr[j], arr[i]);
			}
		}



	}


}

void func3(int* arr, int arrlen)
{
	int pass = 1;
	int compareCount = 0;
	int exchangeCount = 0;
	int lastChange = -1;
	for (int i = 0; i < arrlen; i++)
	{
		lastChange = -1;
		//cout << "패스 " << pass << endl;

		for (int j = arrlen-1; j >= i + 1; j--)
		{
			compareCount++;
			if (arr[j] < arr[j - 1])
			{
				lastChange = j - 1;
				for (int k = 0; k < arrlen; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " + ";
					}
				}

				cout << endl;

				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
				exchangeCount++;
			}

			else
			{
				for (int k = 0; k < arrlen; k++)
				{
					if (k != j - 1)
						cout << arr[k] << "   ";
					else
					{
						cout << arr[k];
						cout << " - ";
					}
				}

				cout << endl;
			}

		}

		if (lastChange != -1)
			i = lastChange;

		for (int k = 0; k < arrlen; k++)
		{
			cout << arr[k] << "   ";
		}

		cout << endl;
		pass++;
	}
	cout << endl;
	//cout << "비교를 " << compareCount << "회 했습니다." << endl;
	//cout << "교환을 " << exchangeCount << "회 했습니다." << endl;
}

int main()
{
	int arr[7] = { 6,4,8,3,1,9,7 };
	//func1(arr, 7);
	func2(arr, 7);

	return 0;
}