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
		cout << "해당 숫자가 없어 삭제할 수 없습니다" << endl;
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
		cout << "원하는 기능을 입력하세요 (1.입력, 2.삭제, 3.출력, 4.검색, 5.종료)" << endl;
		cin >> command;


		switch (command)
		{
		case 1:
		{
			int num;
			cout << "값을 입력하세요: ";
			cin >> num;

			Insert(num);
		}
		break;
		case 2:
		{
			int num;
			cout << "삭제할 값을 입력하세요: ";
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
			cout << "검색할 값을 입력하세요: ";
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
			cout << "잘못된 수를 입력하셨습니다. 다시 입력하세요" << endl;
		}
		break;
		}
	}


	return 0;
}