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

void func(int * arr, int start, int end)
{
	int pivotIndex = (end+start) / 2;
	int pivot = arr[pivotIndex];
	int front = start;
	int back = end - 1;

	if (start >= end) return;

	while (front <=pivotIndex)
	{
		if ( pivot <= arr[front])
		{
			while (back >= pivotIndex)
			{
				if (pivot >= arr[back])
				{
					swap(arr[front], arr[back]);
					if (back == pivotIndex) pivotIndex = front;
					else if (front == pivotIndex) pivotIndex = back;

					break;
				}

				back--;
			}


		}
		if (front < pivotIndex)
			front++;
		else if(pivotIndex ==front && pivotIndex==back)
			break;
	}

	func(arr,start, pivotIndex);
	func(arr, pivotIndex+1, end);


}

int main()
{
	int arr[11] = { 5,7,9,4,11,2,6,3,1,8,10 };
	func(arr, 0,11);

	for (int i = 0; i < 11; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}