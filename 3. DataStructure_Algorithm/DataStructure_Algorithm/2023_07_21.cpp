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
		cout << "원하는 기능을 입력하세요 (1.입력, 2.삭제, 3.출력, 4.종료)" << endl;
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
			cout << "잘 못된 수를 입력하였습니다. 다시 입력하세요" << endl;
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
	cout << "번호와 이름을 입력하세요" << endl;
	cout << "번호: ";
	cin >> st->no;
	cout << "이름: ";
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
	cout << "삭제하고 싶은 번호를 입력하세요" << endl;
	cout << "번호: ";
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
			cout << "해당 번호가 존재하지 않습니다" << endl;
			return;
		}

		while (temp->next->no !=num)
		{
			temp = temp->next;
			if (temp->next == NULL)
			{
				cout << "해당 번호가 존재하지 않습니다" << endl;
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
		cout << "헤드 값이 존재하지 않습니다" << endl;
	}

	while (temp !=NULL)
	{
		cout << "학생이름: " << temp->name << endl;
		cout << "번호: " << temp->no << endl;
		temp = temp->next;
	}

}