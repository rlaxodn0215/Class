#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

//void print_str(char** ps);

//struct address
//{
//	char name[20];
//	int age;
//	char tel[20];
//	char addr[80];
//};

//struct list
//{
//	int num;
//	struct list* next;
//};

//enum season {SPRING, SUMMER,FALL,WINTER};

//struct Student
//{
//	int num;
//	double grade;
//};
//
//typedef struct Student std;

struct Student
{
	int Num;
	char Name[20];
	int grade[3];
	int Sum;
	double Avg;
	char rank;
	struct Student* nextSt;
};

int Input(struct Student* pS);
void Output(struct Student* pS, int human);
void Search(struct Student* pS);

int main() // argv: �ܺο��� ������ �ɼ�
{
	/*int i;
	for (i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}*/

	//Project.exe�� �ִ� ���Ͽ� ���� -> �ּ�â�� cmd ->  dir(���� ���Ͽ� �ִ� ���α׷� ������)
	//->exe ���� �̸� ���� + ���ڿ�->��µ�/ ������ ���� copy ���

	//char temp[128];
	//char* str[3] = { 0 }; //"";

	//for (int i = 0; i < 3; i++)
	//{
	//	printf("���ڿ��� �Է��ϼ��� : ");
	//	gets(temp);
	//	str[i] = (char*)malloc(sizeof(char) * strlen(temp)+1);
	//	if (str[i] == NULL) exit(1);
	//	strcpy(str[i], temp);
	//}

	//for (int i = 0; i < 3; i++)
	//{
	//	printf("%s\n", str[i]);
	//}

	//for (int i = 0; i < 3; i++)
	//{
	//	free(str[i]);
	//}


	//char temp[80];
	//char* str[21] = { 0 };
	////int i = 0;

	//while (i < 20)
	//{
	//	printf("���ڿ��� �Է��ϼ��� : ");
	//	gets(temp);
	//	if (!(strcmp(temp, "end"))) break;
	//	str[i] = (char*)malloc(strlen(temp) + 1);
	//	if (str[i] == NULL) break;
	//	strcpy(str[i], temp);
	//	i++;
	//}

	//print_str(str);

	//for (i = 0; str[i] != NULL; i++)
	//{
	//	free(str[i]);
	//}

	/*
		Q1. p.474 �Ҽ� ��� ���α׷� + �ݺ� ���� ����
	*/

	/*int num;

	while (1)
	{
		printf("��� �Է� (2 �̻�): ");
		scanf("%d", &num);
		if (num < 2) break;
		int* pNum = (int*)malloc(sizeof(int) * num);
		if (pNum == NULL) exit(1);

		for (int i = 2; i <= num; i++)
		{
			pNum[i-2] = 2;
		}

		for (int i = 2; i <= num; i++)
		{
			int count = 0;

			for (int j = 1; j <= i; j++)
			{
				if (i % j == 0) count++;
			}

			if (count == 2)
			{
				pNum[i-2] = i;
			}

			else
			{
				pNum[i-2] = 0;
			}
			
			count = 0;
		}

		for (int i = 0; i < num-1; i++)
		{
			if (pNum[i] == 0) printf("%3c", 'X');
			else printf("%3d", pNum[i]);
			if (!((i+1) % 5)) printf("\n");
		}

		printf("\n\n");
		free(pNum);
	}*/

	//struct address list[10];
	//struct address* plist=list;

	//int i = 0;
	//char contin;

	//printf("�̸�, ����, ��ȭ��ȣ, �ּҸ� �Է��ϼ��� (�ִ� 10��)\n");

	//while(i<10)
	//{
	//	printf("�̸�  : ");
	//	gets((plist + i)->name);
	//	printf("����  : ");
	//	scanf("%d", &(plist + i)->age);
	//	getchar();
	//	printf("��ȭ��ȣ  : ");
	//	gets((plist + i)->tel);
	//	printf("�ּ�  : ");
	//	gets((plist + i)->addr);
	//	i++;
	//	printf("\n");

	//	printf("�׸��Ͻðڽ��ϱ�? (y,n)");
	//	scanf("%c", &contin);
	//	if (contin == 'y') break;

	//	getchar();
	//}

	//for(int j = 0; j < i; j++)
	//{
	//	printf("\n%10s%5d%15s%20s\n", (plist + j)->name, (plist + j)->age, (plist + j)->tel, (plist + j)->addr);
	//}

	//struct list a = { 10,0 }, b = { 20.0 }, c;
	//struct list* head = &a;
	//c.num = 30;
	//c.next = NULL;

	//a.next = &b;
	//b.next = &c;

	//struct list* current;

	//current = head;

	//while (current != NULL)
	//{
	//	printf("%d  ", current->num);
	//	current = current->next;
	//}
	//enum season ss;
	//char* pc = NULL;

	//ss = SUMMER;

	//switch (ss)
	//{
	//case SPRING:
	//	pc = "inline";
	//	break;
	//case SUMMER:
	//	pc = "swimming";
	//	break;
	//case FALL:
	//	pc = "trip";
	//	break;
	//case WINTER:
	//	pc = "skiing";
	//	break;
	//default:
	//	break;
	//}

	//printf("���� ���� Ȱ�� => %s\n", pc);

	//std st;
	//st.grade;

	/*
		Q2. p.512 ���� ó�� ���α׷� 
		�л��� ��, �Է� �޾Ƽ� ó���ϴ� ������ ����
		�ڱ� ���� ����ü �̿�
		�Է��Լ�, ����Լ� ���� ����
		�й�, �̸�, ����(��/��/��)�� �Է� ���� �� �ִ� ����ü�� �����
		���� ���� �л��� ���� �����͸� �Է¹޾� ����ϴ� ���α׷� �ۼ�

		���� 4���� �޴��� �����ϰ�, �� �޴� ���ý� �۵��� ������ ����.
		1. �Է� - �й�, �̸�, ���� ������ �Է�
		2. ��� - ����(���)�� ���� (���ĵ� ���·�) ���
		3. �˻� - �̸����� �ش� �л��� ����, ������ ���
		4. ����

		��,
			1. ��ȣ �ߺ� �Ұ�, �̸��� �ߺ� ����
			2. �˻�->�̸� �˻����� �ϰ� ���� ã�� ���� �켱���� ���
			3. �޸� �Ҵ� ���, �ڱ� ���� ����ü Ȱ��,
				�Է�/ ���/ �˻��� ���� ���� �Լ��� �����Ѵ�.

				CreateConsoleScreenBuffer
				GetAsyncKeyState
				SetConsoleTextAttribute

	*/
	int human;
	int num=0;
	struct Student st[30];
	struct Student* pStudent = &st;

	for (int i = 0; i < 30; i++)
	{
		st[i].nextSt = &st[i + 1];
	}
	
	while (num != 4)
	{
		printf("1. �Է�, 2. ���, 3. �˻�, 4.���� : ");
		scanf("%d", &num);
		switch (num)
		{
		case 1: 
		{
			human=Input(pStudent);
		} 
		break;
		case 2:
		{
			Output(pStudent,human);
		}
		break;
		case 3:
		{
			Search(pStudent, human);
		}
		break;
		case 4: { break; }break;
		default: {printf("�ùٸ� ���ڸ� �Է��ϼ���\n");}break;
		}
	}

	return 0;
}

int Input(struct Student* pS)
{
	printf("�Է�â (�ִ� 30��)\n");
	struct Student* current = pS;
	struct Student* current1 = pS;
	int NumberOfStudent = 0;
	char contin;
	while (1)
	{
		printf("�й� : ");
		scanf("%d", &current->Num);
		getchar();
		printf("�̸� : ");
		gets(current->Name);
		printf("����, ����, ���� ���� : ");
		scanf("%d%d%d", &current->grade[0], &(current)->grade[1], &(current)->grade[2]);
		getchar();

		(current)->Sum = ((current)->grade[0] + (current)->grade[1] + (current)->grade[2]);
		(current)->Avg = (current)->Sum / 3.0;

		if (((current)->Avg) >= 90.0)
		{
			(current)->rank = 'A';
		}

		else if (((current)->Avg) >= 80.0)
		{
			(current)->rank = 'B';
		}

		else if (((current)->Avg) >= 70.0)
		{
			(current)->rank = 'C';
		}

		else
		{
			(current)->rank = 'F';
		}

		printf("�׸� �Է��Ͻðڽ��ϱ�? (y,n)");
		scanf("%c", &contin);
		if (contin == 'y')
		{
			current->nextSt = NULL;
			break;
		}
		current = current->nextSt;
		NumberOfStudent++;
	}

	return (NumberOfStudent+1);
	
}

void Output(struct Student* pS, int human)
{

	struct Student* current = pS;

	for (int i = 0; i < human; i++)
	{
		for (int j = 0; j < (human - 1)-i; j++)
		{
			if (current->Avg < current->nextSt->Avg)
			{
				struct Student temp= *current;
				*current = *(current->nextSt);
				*(current->nextSt) = temp;

				/*temp.Num = current->Num;
				strcpy(temp.Name, current->Name);
				temp.grade[0] = current->grade[0];
				temp.grade[1] = current->grade[1];
				temp.grade[2] = current->grade[2];
				temp.Sum = current->Sum;
				temp.Avg = current->Avg;
				temp.rank = current->rank;

				current->Num = current->nextSt->Num;
				strcpy(current->Name, current->nextSt->Name);
				current->grade[0] = current->nextSt->grade[0];
				current->grade[1] = current->nextSt->grade[1];
				current->grade[2] = current->nextSt->grade[2];
				current->Sum = current->nextSt->Sum;
				current->Avg = current->nextSt->Avg;
				current->rank = current->nextSt->rank;

				current->nextSt->Num = temp.Num;
				strcpy(current->nextSt->Name,temp.Name);
				current->nextSt->grade[0] = temp.grade[0];
				current->nextSt->grade[1] = temp.grade[1];
				current->nextSt->grade[2] = temp.grade[2];
				current->nextSt->Sum = temp.Sum;
				current->nextSt->Avg = temp.Avg;
				current->nextSt->rank = temp.rank;*/

			}

			current = current->nextSt;
		}
		current = pS;
	}

	current = pS;

	for (int i = 0; i < human; i++)
	{
		printf("%3d %4s %3d %3d %3d %5d %.1lf %2c\n", current->Num, current->Name, current->grade[0],
			current->grade[1], current->grade[2], current->Sum, current->Avg, current->rank);

		current = current->nextSt;
	}
}

void Search(struct Student* pS, int human)
{
	struct Student* current = pS;

	char name[20];
	printf("�̸��� �Է��ϼ��� : ");
	scanf("%s", name);
	for (int i = 0; i < human; i++)
	{
		if (!strcmp(current->Name, &name))
		{
			printf("%3d %4s %3d %3d %3d %5d %.1lf %2c\n", current->Num, current->Name, current->grade[0],
				current->grade[1], current->grade[2], current->Sum, current->Avg, current->rank);
		}

		current = current->nextSt;
	}
	getchar();
}

//void print_str(char** ps)
//{
//	while (*ps != NULL)
//	{
//		printf("%s\n", *ps);
//		ps++;
//	}
//}