#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

//char* my_strncpy(char* pd, char* ps, int n);
//char* my_strncat(char* pd, char* ps, int n);
//int my_strlen(char* ps);
//int my_strcmp(char* pa, char* pb);

//void assign10();
//void assign20();
//
//int a;

void auto_func();
void static_func();

int main()
{
	//char szBuf[12] = { "Test string" };
	//char* pszData = "Test String";

	//printf("%d\n", szBuf == pszData); //�ּ� ��
	//printf("%d\n", "Test String" == pszData);
	//printf("%d\n", "Test String" == "Data String");
	//printf("%d\n", "Test String");
	//printf("%d\n", "Data String");

	//char str[80];
	//int num[5];

	///*printf("%d\n", sizeof(str));
	//printf("%d\n", sizeof(num));*/

	//printf("������ ���Ե� ���ڿ� �Է� : ");
	//fgets(str, sizeof(str), stdin);

	//str[strlen(str) - 1] = '\0';

	//printf("�Էµ� ���ڿ��� %s�Դϴ�\n", str);

	/*char str[80] = "apple juice";
	char* ps = "banana";

	puts(str);
	fputs(ps, stdout);
	puts("milk");*/

	/*int a = 10;
	int b = 20;

	char c[10] = "apple";
	char d[10] = "pie";

	printf("%d\n", a + b);
	printf("%s\n", c + d);*/

	/*char str1[80] = "strawberry";
	char str2[80] = "apple";
	char* ps1 = "banana";
	char* ps2 = str2;

	printf("%s\n", str1);

	printf("���� ���ڿ� : %s\n", str1);
	strcpy(str1, str2);
	printf("�ٲ� ���ڿ� : %s\n", str1);

	strcpy(str1, ps1);*/
	//printf()

	/*char str[20] = "mango tree";

	strncpy(str, "apple-pie", 5);

	printf("%s\n", str);*/

	/*char str[80] = "straw";

	strcat(str, "berry");
	printf("%s\n", str);
	strncat(str, "piece", 3);
	printf("%s\n", str);*/

	/*char str1[80], str2[80];
	char* resp;

	printf("2���� ���� �̸� �Է� : ");
	scanf("%s%s", str1, str2);
	if (strlen(str1) > strlen(str2))
		resp = str1;
	else
		resp = str2;
	printf("�̸��� �� ������ : %s\n", resp);*/

	/*char str1[80] = "pear";
	char str2[80] = "peach";

	printf("�տ��� 3���� ���ڸ� ���ϸ�?\n");
	if (strncmp(str1, str2, 3) == 0)
		printf("����.\n");
	else
		printf("ekfmek.\n");*/

	/*printf("������ ���߿� ������ ���� �̸� : ");
	if (strcmp(str1, str2) > 0)
		printf("%s\n", str1);
	else if(strcmp(str1, str2) == 0)
		printf("���� �ܾ� �Դϴ�.");
	else 
		printf("%s\n", str2);*/

	/*char str1[80] = "strawberry";
	char str2[80] = "strawberii";

	printf("%d\n",my_strncmp(str1, str2, 8));*/
	
	//printf("�ٲ� �� ���ڿ� : %s\n", str);
	//printf("�ٸ� ���ڿ� ���� : %s\n", my_strcat(str, "kiwi"));
	//printf("%d\n", my_strlen("Hello"));

/*
	Q1. p.353 ���� ���� ���� (+��ҹ��� ����)
*/
	//char s1[100];
	//char s2[100];
	//char s3[100];

	//char temps1[100];
	//char temps2[100];
	//char temps3[100];

	//printf("�� �ܾ� �Է� (100�� �̳�): ");
	//scanf("%s %s %s", s1, s2, s3);

	////���纻�� �־ ������ �ջ� ����
	//strcpy(temps1, s1); 
	//strcpy(temps2, s2);
	//strcpy(temps3, s3);




	//if (my_strcmp(temps1, temps2) > 0)
	//{
	//	if (my_strcmp(temps1, temps3) > 0)
	//	{

	//		if (my_strcmp(temps2, temps3) > 0)
	//		{
	//			printf("%s, %s, %s", s3, s2, s1);
	//		}

	//		else 
	//		{
	//			printf("%s, %s, %s", s2, s3, s1);
	//		}
	//	}

	//	else
	//	{

	//		if (my_strcmp(temps2, temps3) > 0)
	//		{
	//			printf("%s, %s, %s", s3, s1, s2);
	//		}

	//		else
	//		{
	//			printf("%s, %s, %s", s2, s1, s3);
	//		}
	//	}
	//}

	//else
	//{
	//		if (my_strcmp(temps2, temps3) > 0)
	//		{
	//			printf("%s, %s, %s", s1, s2, s3);
	//		}

	//		else
	//		{
	//			printf("%s, %s, %s", s1, s3, s2);
	//		}

	//}

	/*
	Q1. "I am a boy, I'm happy! ���ڿ��� �ִµ�
		���� boy�� ��ġ�ּҸ� ����ϰ� boy�� girl�� 
		�ٲپ� ����ϴ� ���α׷��� �ۼ��϶�.

		��°��>
			boy�� ��ġ�ּ� : 0FF2 C400
			�ٲ� ���ڿ� : I am a girl. I'm happy!
	*/

	//char sentence[50];
	//char tempSentence[50] = "";
	//char changeSentence[50] = "";
	//char letter[50];
	//char changeLetter[50];
	//int start = 0;

	//printf("���ڿ� �Է� : ");
	//gets(sentence);
	//printf("���� ��� �ܾ� : ");
	//gets(letter);
	//printf("���� �� �ܾ� : ");
	//gets(changeLetter);

	//for (int i = 0; i < strlen(sentence); i++)
	//{
	//	int count = 0;

	//	for (int j = 0; j < strlen(letter); j++)
	//	{
	//		if (sentence[i+j] == *(letter + j))
	//		{
	//			count++;
	//		}
	//	}

	//	if (count == strlen(letter))
	//	{
	//		printf("%x\n", &sentence[i]);
	//		start = i;
	//	}
	//}

	//strncpy(changeSentence, sentence, start);
	//strcat(changeSentence, changeLetter);

	//for (int i = 0; i < strlen(sentence) - start; i++)
	//{
	//	tempSentence[i] = sentence[start+strlen(letter) + i];
	//}

	//strcat(changeSentence, tempSentence);
	//
	//printf("%s\n", changeSentence);

	//printf("�Լ� ȣ�� �� a �� : %d\n", a);

	//assign10();
	//assign20();

	//printf("�Լ� ȣ�� �� a �� : %d\n", a);
	int i;

	printf("�Ϲ� ���� ����(auto)�� ����� �Ѽ�...\n");
	for (i = 0; i < 3; i++)
	{
		auto_func();
	}

	printf("���� ���� ����(static)�� ����� �Լ�...\n");
	for (i = 0; i < 3; i++)
	{
		static_func();
	}


	return 0;
}

void auto_func()
{
	auto int a = 0;
	a++;
	printf("%d\n", a);
}

void static_func()
{
	static int a;

	a++;
	printf("%d\n", a);
}


//void assign10()
//{
//	a = 10;
//}
//void assign20() 
//{
//	int a;
//
//	a = 20;
//}

//int my_strcmp(char* pa, char* pb)
//{
//
//	for (int i = 0; i < strlen(pa); i++)
//	{
//		if ((*pa >= 65) && (*pa <= 90))
//		{
//			*pa += 32;
//		}
//	}
//
//	for (int i = 0; i < strlen(pb); i++)
//	{
//		if ((*pb >= 65) && (*pb <= 90))
//		{
//			*pb += 32;
//		}
//	}
//
//
//	while ((*pa == *pb) && (*pa != '\0'))
//	{
//		pa++;
//		pb++;
//	}
//
//	if (*pa > *pb) return 1;
//	else if (*pa < *pb) return -1;
//	else return 0;
//}

//int my_strlen(char* ps)
//{
//	int cnt = 0;
//
//	while (*ps != '\0')
//	{
//		cnt++;
//		ps++;
//	}
//
//	return cnt;
//}

//char* my_strncat(char* pd, char* ps, int n)
//{
//
//	while (*pd != '\0')
//	{
//		pd++;
//	}
//
//	while (*ps != '\0'&& n!=0)
//	{
//		*pd = *ps;
//		pd++;
//		ps++;
//		n--;
//	}
//
//	pd = '\0';
//
//	return pd;
//}

//char* my_strncpy(char* pd, char* ps, int n) //pd�� �ּҿ��� ���� �ٲٱ� ������ ���ڿ� ���� ���Ѵ�.
//{
//	char* p0 = pd;
//
//
//	while (*ps != '\0' && n !=0)
//	{
//		*pd = *ps;
//		pd++;
//		ps++;
//		n--;
//	}
//
//	//*pd = '\0';
//
//	return pd;
//}