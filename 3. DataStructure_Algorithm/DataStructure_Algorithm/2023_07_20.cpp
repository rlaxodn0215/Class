#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
//#include"StopWatch.h"

using namespace std;

struct Data
{
	int no;
};

struct Node
{
	Data data;
	Node* left, * right;
};

Node* rootNode;
Node nodes[10];
int cursor = 1;

void Insert(int num)
{
	if (rootNode == NULL)
	{
		rootNode = &nodes[0];
		rootNode->data.no = num;
		rootNode->left = NULL;
		rootNode->right = NULL;
	}

	else
	{
		Node* cur = rootNode;

		while (1)
		{
			if (cur->data.no > num)
			{
				if (cur->left == NULL)
				{
					cur->left = &nodes[cursor];
					cur->left->data.no = num;
					cursor++;
					break;
				}

				else
				{
					cur = cur->left;
				}
			}

			else
			{

				if (cur->left == NULL)
				{
					cur->right = &nodes[cursor];
					cur->right->data.no = num;
					cursor++;
					break;
				}

				else
				{
					cur = cur->right;
				}
			}
		}

	}
}

void Delete(int num)
{
	if (Search(num))
	{
		
	}

	else
	{
		cout << "�ش� ���ڰ� ���� ������ �� �����ϴ�" << endl;
	}
}

void Print()
{

}

bool Search(int num)
{
	Node* cur = rootNode;

	while (1)
	{
		if (cur->data.no == num)
		{

			break;
		}

		else if (cur->data.no > num)
		{

		}

		else
		{

		}
	}
}

int main()
{
	int command = 0;

	while (command != 5)
	{
		cout << "���ϴ� ����� �Է��ϼ��� (1.�Է�, 2.����, 3.���, 4.�˻�, 5.����)" << endl;
		cin >> command;


		switch (command)
		{
		case 1:
		{
			int num;
			cout << "���� �Է��ϼ���: ";
			cin >> num;

			Insert(num);
		}
		break;
		case 2:
		{
			int num;
			cout << "������ ���� �Է��ϼ���: ";
			cin >> num;
			Delete(num);
		}
		break;
		case 3:
		{
			Print();
		}
		break;
		case 4:
		{
			int num;
			cout << "�˻��� ���� �Է��ϼ���: ";
			cin >> num;
			Search(num);
		}
		break;
		case 5:
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