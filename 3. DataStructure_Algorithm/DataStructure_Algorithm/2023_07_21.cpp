#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
//#include"StopWatch.h"

using namespace std;

struct Student
{
	string name;
	int no;
	Student* next;
};


struct StudentList
{
	Student* head;
};

void Initalize(StudentList *list);
void Insert(StudentList* list);
void Delete(StudentList* list);
void Print(StudentList* list);

int main()
{
	StudentList* list = new StudentList;
	Initalize(list);

	int command = 0;

	while (command != 4)
	{
		cout << "���ϴ� ����� �Է��ϼ��� (1.�Է�, 2.����, 3.���, 4.����)" << endl;
		cin >> command;
		switch (command)
		{
		case 1:
			Insert(list);
			break;
		case 2:
			Delete(list);
			break;
		case 3:
			Print(list);
			break;
		case 4:
			break;
		default:
			cout << "�� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���" << endl;
			break;
		}
	}
	return 0;
}

void Initalize(StudentList* list)
{
	list->head = NULL;
}
void Insert(StudentList* list)
{
	Student* st = new Student;
	cout << endl;
	cout << "��ȣ�� �̸��� �Է��ϼ���" << endl;
	cout << "��ȣ: ";
	cin >> st->no;
	cout << "�̸�: ";
	cin >> st->name;

	st->next = NULL;

	Student* temp = list->head;

	if (list->head == NULL)
	{
		list->head = st;
	}

	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = st;
	}

}
void Delete(StudentList* list)
{
	int num;
	cout << "�����ϰ� ���� ��ȣ�� �Է��ϼ���" << endl;
	cout << "��ȣ: ";
	cin >> num;

	Student* temp = list->head;

	if (temp->no == num)
	{
		Student* temp1 = list->head->next;
		delete temp;
		list->head = temp1;
	}

	else
	{
		if (temp->next == NULL)
		{
			cout << "�ش� ��ȣ�� �������� �ʽ��ϴ�" << endl;
			return;
		}

		while (temp->next->no !=num)
		{
			temp = temp->next;
			if (temp->next == NULL)
			{
				cout << "�ش� ��ȣ�� �������� �ʽ��ϴ�" << endl;
				return;
			}
		}


		Student* temp2 = temp;
		temp2->next = temp->next;
		delete temp;
	}

}
void Print(StudentList* list)
{
	Student* temp = list->head;

	if (temp == NULL)
	{
		cout << "��� ���� �������� �ʽ��ϴ�" << endl;
	}

	while (temp !=NULL)
	{
		cout << "�л��̸�: " << temp->name << endl;
		cout << "��ȣ: " << temp->no << endl;
		temp = temp->next;
	}

}