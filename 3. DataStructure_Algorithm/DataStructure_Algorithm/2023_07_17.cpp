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
		cout << "���ϴ� ����� �Է��ϼ��� (1.�Է�, 2.����, 3.���, 4.����)" << endl;
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
			cout << "�߸��� ���� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���" << endl;
		}
			break;
		}
		
	}

	return 0;
}