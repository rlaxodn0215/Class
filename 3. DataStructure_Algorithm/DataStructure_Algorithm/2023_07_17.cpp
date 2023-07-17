#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
//#include"StopWatch.h"

using namespace std;

int unused = 0;
int dat[10];
int nxt[10];

int free[10];
int freenxt[10];


void InsertData()
{
	

}

void DeleteData()
{

}

void PrintData()
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
			InsertData();
		}
			break;
		case 2:
		{
			DeleteData();
		}
			break;
		case 3:
		{
			PrintData();
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