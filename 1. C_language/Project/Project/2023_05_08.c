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

	//printf("%d\n", szBuf == pszData); //주소 비교
	//printf("%d\n", "Test String" == pszData);
	//printf("%d\n", "Test String" == "Data String");
	//printf("%d\n", "Test String");
	//printf("%d\n", "Data String");

	//char str[80];
	//int num[5];

	///*printf("%d\n", sizeof(str));
	//printf("%d\n", sizeof(num));*/

	//printf("공백이 포함된 문자열 입력 : ");
	//fgets(str, sizeof(str), stdin);

	//str[strlen(str) - 1] = '\0';

	//printf("입력된 문자열은 %s입니다\n", str);

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

	printf("최초 문자열 : %s\n", str1);
	strcpy(str1, str2);
	printf("바뀐 문자열 : %s\n", str1);

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

	printf("2개의 과일 이름 입력 : ");
	scanf("%s%s", str1, str2);
	if (strlen(str1) > strlen(str2))
		resp = str1;
	else
		resp = str2;
	printf("이름이 긴 과일은 : %s\n", resp);*/

	/*char str1[80] = "pear";
	char str2[80] = "peach";

	printf("앞에서 3개의 문자만 비교하면?\n");
	if (strncmp(str1, str2, 3) == 0)
		printf("같다.\n");
	else
		printf("ekfmek.\n");*/

	/*printf("사전에 나중에 나오는 과일 이름 : ");
	if (strcmp(str1, str2) > 0)
		printf("%s\n", str1);
	else if(strcmp(str1, str2) == 0)
		printf("같은 단어 입니다.");
	else 
		printf("%s\n", str2);*/

	/*char str1[80] = "strawberry";
	char str2[80] = "strawberii";

	printf("%d\n",my_strncmp(str1, str2, 8));*/
	
	//printf("바꾼 후 문자열 : %s\n", str);
	//printf("다른 문자열 대입 : %s\n", my_strcat(str, "kiwi"));
	//printf("%d\n", my_strlen("Hello"));

/*
	Q1. p.353 도전 실전 예제 (+대소문자 구분)
*/
	//char s1[100];
	//char s2[100];
	//char s3[100];

	//char temps1[100];
	//char temps2[100];
	//char temps3[100];

	//printf("세 단어 입력 (100자 이내): ");
	//scanf("%s %s %s", s1, s2, s3);

	////복사본을 넣어서 데이터 손상 방지
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
	Q1. "I am a boy, I'm happy! 문자열이 있는데
		이중 boy의 위치주소를 출력하고 boy를 girl로 
		바꾸어 출력하는 프로그램을 작성하라.

		출력결과>
			boy의 위치주소 : 0FF2 C400
			바뀐 문자열 : I am a girl. I'm happy!
	*/

	//char sentence[50];
	//char tempSentence[50] = "";
	//char changeSentence[50] = "";
	//char letter[50];
	//char changeLetter[50];
	//int start = 0;

	//printf("문자열 입력 : ");
	//gets(sentence);
	//printf("수정 대상 단어 : ");
	//gets(letter);
	//printf("수정 할 단어 : ");
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

	//printf("함수 호출 전 a 값 : %d\n", a);

	//assign10();
	//assign20();

	//printf("함수 호출 전 a 값 : %d\n", a);
	int i;

	printf("일반 지역 변수(auto)를 사용한 한수...\n");
	for (i = 0; i < 3; i++)
	{
		auto_func();
	}

	printf("정적 지역 변수(static)를 사용한 함수...\n");
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

//char* my_strncpy(char* pd, char* ps, int n) //pd의 주소에서 값을 바꾸기 때문에 문자열 값이 변한다.
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