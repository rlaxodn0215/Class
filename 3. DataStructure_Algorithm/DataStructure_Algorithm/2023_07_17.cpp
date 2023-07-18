#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
//#include"StopWatch.h"

using namespace std;

const int MX = 10;

int data[MX];
int prev[MX];
int next[MX];
int free[MX];

void Insert(int addr, int num)
{

}

void Delete(int addr)
{

}

void Print()
{

}

int main()
{

	int command=0;

	while (command !=4)
	{
		cout << "원하는 기능을 입력하세요 (1.입력, 2.삭제, 3.출력, 4.종료)" << endl;
		cin >> command;

		switch (command)
		{
		case 1:
		{
			//InsertData();
		}
			break;
		case 2:
		{
			//DeleteData();
		}
			break;
		case 3:
		{
			Print();
		}
			break;
		case 4:
		{

		}
			break;
		default:
		{
			cout << "잘못된 수를 입력하셨습니다. 다시 입력하세요" << endl;
		}
			break;
		}
		
	}

	return 0;
}