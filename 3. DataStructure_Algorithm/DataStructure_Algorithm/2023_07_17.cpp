#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
//#include"StopWatch.h"

using namespace std;

int cursor = 0;
int head = 0;
int tail = -1;
int num = 0;

struct Node
{
	char data;
	Node* prev, * next;
};

Node node[10];

void Insert(int addr, char ch)
{
	if (addr > cursor)
	{
		cout << "���� ������ �Ѿ���ϴ�" << endl;
		return;
	}

	Node* cur = &node[head];

	for (int i = 0; i < addr; i++)
	{
		cur = cur->next;
	}

	node[cursor].data = ch;
	node[cursor].prev = cur->prev;
	node[cursor].next = cur;

	cur->prev->next = &node[cursor];
	cur->prev = &node[cursor];

	cursor++;
	num++;

}

void Delete(int addr)
{
	if (addr > cursor)
	{
		cout << "���� ������ �Ѿ���ϴ�" << endl;
		return;
	}

	Node* cur = &node[head];

	for (int i = 0; i < addr; i++)
	{
		cur = cur->next;
	}

	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;

	num--;
}

void Print()
{
	Node* cur = &node[head];

	int count = 0;
	while (cur != NULL && count != num)
	{
		cout << cur->data << " ";
		cur = cur->next;
		count++;
	}

	cout << endl;
}

void RevPrint()
{
	Node* cur = &node[tail];

	int count = 0;
	while (cur != NULL && count != num)
	{
		cout << cur->data << " ";
		cur = cur->prev;
		count--;
	}

	cout << endl;
}


int main()
{

	{
		node[0].data = 'A';
		node[0].prev = NULL;
		node[0].next = &node[1];
		cursor++;
		num++;
		tail++;

		node[1].data = 'B';
		node[1].prev = &node[0];
		node[1].next = &node[2];
		cursor++;
		num++;
		tail++;

		node[2].data = 'C';
		node[2].prev = &node[1];
		node[2].next = &node[3];
		cursor++;
		num++;
		tail++;

	}

	int command=0;
	int addr;
	char ch;

	while (command !=5)
	{
		cout << "���ϴ� ����� �Է��ϼ��� (1.�Է�, 2.����, 3.���, 4.���� ���, 5.����)" << endl;
		cin >> command;

		switch (command)
		{
		case 1:
		{
			cout << "������ �ּҿ� ���ڸ� �Է��ϼ���: ";
			cin >> addr >> ch;

			Insert(addr,ch);
		}
			break;
		case 2:
		{
			cout << "������ �ּҸ� �Է��ϼ���: ";
			cin >> addr;
			Delete(addr);
		}
			break;
		case 3:
		{
			Print();
		}
			break;
		case 4:
		{
			RevPrint();
		}
			break;
		case 5:
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