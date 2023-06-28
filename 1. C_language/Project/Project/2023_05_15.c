#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

int main()
{

	/*FILE* fp;
	char str[] = "banana";

	fp = fopen("data/c.txt", "wb");
	if (fp == NULL)
	{
		printf("파일이 열리지 않습니다.\n");
		return 1;
	}

	int i = 0;

	while (str[i] !='\0')
	{
		fputc(str[i], fp);
		i++;
	}

	fputc('\n', fp);
	fclose(fp);*/

	/*FILE* fp;
	int ary[10] = { 13,10,13,13,10,26,13,10,13,10 };
	int i, res;
	fp = fopen("a.txt", "wb");

	for (i = 0; i < 10; i++)
	{
		fputc(ary[i], fp);
	}

	fclose(fp);

	fp = fopen("a.txt", "rt");
	while (1)
	{
		res = fgetc(fp);
		if (res == EOF) break;
		printf("%4d", res);
	}

	fclose(fp);*/

	//FILE* fp;
	//char* str[20];

	//fp = fopen("a.txt", "a+");
	//if (fp == NULL)
	//{
	//	printf("파일을 만들지 못했습니다.\n");
	//	return 1;
	//}

	//while (1)
	//{
	//	printf("과일 이름 : ");
	//	scanf("%s", str);
	//	if (strcmp(str, "end") == 0)
	//	{
	//		break;
	//	}

	//	else if (strcmp(str, "list") == 0)
	//	{
	//		fseek(fp, 0, SEEK_SET);
	//		while (1)
	//		{
	//			fgets(str, sizeof(str), fp);
	//			if (feof(fp))
	//			{
	//				break;
	//			}

	//			printf("%s", str);
	//		}
	//	}

	//	else
	//	{
	//		fprintf(fp, "%s\n", str);
	//	}
	//}

	//fclose(fp);

	//FILE* ifp, * ofp;
	//char str[80];
	//char* res;

	//ifp = fopen("a.txt", "r");
	//if (ifp == NULL)
	//{
	//	printf("입력 파일을 열지 못했습니다.\n");
	//	return 1;
	//}

	//ofp = fopen("b.txt", "w");
	//if (ofp == NULL)
	//{
	//	printf("출력 파일을 열지 못했습니다.\n");
	//	return 1;
	//}
	//
	//while (1)
	//{
	//	res = fgets(str, sizeof(str), ifp);
	//	if (res == NULL)
	//	{
	//		break;
	//	}

	//	str[strlen(str) - 1] = '\0';
	//	fputs(str, ofp);
	//	fputs(" ", ofp);
	//}

	//fclose(ifp);
	//fclose(ofp);

	//FILE* ifp, * ofp;
	//char name[20];
	//int kor, eng, math;
	//int total;
	//double avg;
	//int res;

	//ifp = fopen("a.txt", "r");
	//if (ifp == NULL)
	//{
	//	printf("입력 파일을 열지 못했습니다.\n");
	//	return 1;
	//}

	//ofp = fopen("b.txt", "w");
	//if (ofp == NULL)
	//{
	//	printf("출력 파일을 열지 못했습니다.\n");
	//	return 1;
	//}

	//while (1)
	//{
	//	res = fscanf(ifp, " %s %d %d %d", name, &kor, &eng, &math);
	//	if (res == EOF) break;

	//	total = kor + eng + math;
	//	avg = total / 3.0;
	//	fprintf(ofp, " %s %5d %7.1lf\n", name, total, avg);
	//}

	//fclose(ifp);
	//fclose(ofp);

	/*FILE* fp;
	int age;
	char name[20];

	fp = fopen("a.txt", "r");

	fscanf(fp, "%d", &age);
	fgets(name, sizeof(name), fp);

	printf("나이 : %d, 이름 : %s", age, name);
	fclose(fp);*/

/*
Q1. p.554 도전 실전 예제
*/
	//FILE* ifp1, * ifp2, * ofp;
	//char str1[20];
	//char str2[20];
	//char *res1, *res2;

	//ifp1 = fopen("a.txt", "r");
	//if (ifp1 == NULL)
	//{
	//	printf("a파일을 열지 못했습니다.\n");
	//	return 1;
	//}

	//ifp2 = fopen("b.txt", "r");
	//if (ifp2 == NULL)
	//{
	//	printf("b파일을 열지 못했습니다.\n");
	//	return 1;
	//}

	//ofp = fopen("c.txt", "w");
	//if (ofp == NULL)
	//{
	//	printf("c파일을 쓰지 못했습니다.\n");
	//	return 1;
	//}

	//for(int i=0;i<10;i++)
	//{
	//	int count = 0;
	//	res2 = fgets(str2, sizeof(str2), ifp2);
	//	if (res2 == NULL) break;
	//	fseek(ifp1, 0, SEEK_SET);

	//	for (int j = 0; j < 10; j++)
	//	{
	//		res1 = fgets(str1, sizeof(str1), ifp1);
	//		if (res1 == NULL) break;

	//		if (!(strcmp(res2, res1)))
	//		{
	//			count++;
	//		}

	//	}
	//	if (count == 0 )
	//	{
	//		fputs(res2, ofp);
	//	}
	//}

	//fclose(ifp1);
	//fclose(ifp2);
	//fclose(ofp);

/*
Q2. 99.txt 파일을 만들고, 여기에 구구단을 저장하도록 한다.
그리고 fseek()를 이용하여 원하는 구구단의 내용만을 찾아 출력하는 프로그램을 작성하라

ex> 몆단을 출력? 2

2단
=========================
2 X 1 = 2
2 X 2 =4
....
2 X 9 =18
==========================
*/
	//FILE* ifp;
	//int num;
	//char str[20];
	//char* res;

	//ifp = fopen("99.txt", "w");
	//if (ifp == NULL) return 1;

	//for (int i = 2; i <= 9; i++)
	//{
	//	for (int j = 1; j < 10; j++)
	//	{
	//		fprintf(ifp, "%d X %d = %d\n", i, j, i * j);
	//	}	
	//}

	//fclose(ifp);
	//
	//ifp = fopen("99.txt", "r");
	//if (ifp == NULL) return 1;

	//printf("몇 단을 출력? (2단 이상): ");
	//scanf("%d", &num);

	//fseek(ifp,0, SEEK_SET);

	//for (int i = 2; i < num; i++)
	//{
	//	for (int j = 1; j <= 9; j++)
	//	{
	//		res = fgets(str, sizeof(str), ifp);
	//	}
	//}

	//printf("%d단\n", num);
	//printf("==========================\n");
	//for (int i = 1; i <= 9; i++)
	//{
	//	res = fgets(str, sizeof(str), ifp);
	//	if (res == NULL) break;
	//	printf("%s", res);
	//}
	//printf("==========================\n");

	//fclose(ifp);

	/*
		Q3. 파일 복사 프로그램 만들기
		복사할 파일명과 복사 후 생성되는 파일명을 입력받아서
		파일의 내용을 복사하는 프로그램 작성

		단, txt 파일 뿐만 아니라 이미지 파일 등.. 모두 종류의 파일에 다 동일하게 적용할 수 있어야 한다.
		복사 잔행 과정을 백분율로 화면에 표시해 주고
		한번에 n바이트씩 복사하도록 한다.

		ex)4바이트
			원본 파일 : source.txt
			대상 파일 : dest.txt
	*/

	
	char src[20];
	char des[20];
	int byte, size;

	printf("원본파일 : ");
	scanf("%s", src);
	printf("복사파일 : ");
	scanf("%s", des);
	printf("전송 바이트 수 : ");
	scanf("%d", &byte);

	FILE* srcf, *desf;

	srcf = fopen(src, "rb");
	if (srcf == NULL) return 1;

	desf = fopen(des, "wb");
	if (desf == NULL) return 1;

	fseek(srcf, 0, SEEK_END);
	size = ftell(srcf);
	fseek(srcf, 0, SEEK_SET);
	//printf("%d\n", size);

	char* buffer = (char*)malloc(sizeof(char) * byte);
	if (buffer == NULL) exit(1);

	int count = 0;
	while (byte * count <= size)
	{
		system("cls");
		printf("원본파일 : %s\n",src);
		printf("복사파일 : %s\n",des);
		printf("전송 바이트 수 : %d\n",byte);
		printf("전송중... %.2lf %%\n", (double)byte * count * 100 / size);
		fread(buffer, byte, 1, srcf);
		fwrite(buffer,byte,1,desf);
		Sleep(10);
		count++;
	}

	system("cls");
	printf("원본파일 : %s\n", src);
	printf("복사파일 : %s\n", des);
	printf("전송 바이트 수 : %d\n", byte);
	printf("전송 완료!\n");

	free(buffer);
	fclose(srcf);
	fclose(desf);
	
	return 0;
}

