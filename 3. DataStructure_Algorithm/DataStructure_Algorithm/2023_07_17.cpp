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
		cout << "���ϴ� ����� �Է��ϼ��� (1.�Է�, 2.����, 3.���, 4.����)" << endl;
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
			cout << "�߸��� ���� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���" << endl;
		}
			break;
		}
		
	}

	return 0;
}