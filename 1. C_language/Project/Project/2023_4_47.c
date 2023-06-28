#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h> //string 함수 이용

int main()
{
	//unsigned char	alphabet; // 0 ~ 255
	//unsigned int	year, month;
	//float	pi;
	//double	doublePI;

	//alphabet = 'a'; // ""는 문자열로 나온다.
	//year = 2023;
	//pi = 3.14f;
	//doublePI = 3.14;
	//month = 4;
	//year = month;

	//int a;
	//int b, c;
	//double da; // 선언 먼저, 그 다음 초기화
	//char ch;

	//a = 10;
	//b = a;
	//c = a + 20;
	//da = 3.5;
	//ch = 'A';

	//printf("변수 a의 값 : %d\n", a);
	//printf("변수 b의 값 : %d\n", b);
	//printf("변수 c의 값 : %d\n", c);
	//printf("변수 da의 값 : %.1f\n", da);
	//printf("변수 ch의 값 : %c\n", ch);

	//char ch1 = 'A';
	//char ch2 = 65;

	//printf("문자 %c의 아스키 코드 값 : %d\n", ch1, ch1);
	//printf("아스키 코드 값이 %d인 문자 : %c\n", ch2, ch2);

	//short sh = 1000;

	//if (sh > 32767)
	//	printf("short 크기 이상의 값 입니다..."); // 값 초과시 대비! -> 예외처리 필수!!

	//printf("%d\n", sizeof(sh));

	// 데이터 값 초과시 초과한 수만큼 다른 데이터에 저장
	//

	//float ft = 1.234567890123456789;
	//double db = 1.234567890123456789;

	//printf("float형 변수의 값	: %.20f\n", ft);
	//printf("double형 변수의 값	: %.20f\n", db);

	//float a = 0.12f;
	//a *=10;
	//printf("%.20f\n", a); // (! = 1.2) 실수형 자료형을 판단할 때 범위 지정

	/*int a;
	a += 1;
	printf("%d\n", a);*/

	//char name[4+1] = "hong";//\0
	//문자열 끝에 '\0'이 추가되어 글자수의 하나 더한값을 배열에 넣는다. -> 배열 포인터는 시작값만 저장하기 때문에 끝나는 값을 넣어야 한다. 

	//name = "gil"; -> 안됨
	//printf("%s \n", name);

	//char name[128];

	//strcpy(name, "hong"); // strcpy_s(name,128, "hong");
	//
	//printf("%s \n", name);

	//const int age = 25; // 변수를 상수화 (변경X)

	/*int nnumber = 0;
	int inumber = 0;
	char ca = 'c';
	char strname[128];
	char sname[128];
	float fnumber = 0.0f;
	double dnumber = 0.0;*/

	//목적을 분명하게 하는 변수명 정하기 (길어도 괜찮다!)

	/*int Kor = 70, Eng = 80, Mat = 90;
	int total = 0;

	total = Kor + Eng + Mat;
	printf("국어 : %d, 영어 : %d, 수학 : %d \n", Kor, Eng, Mat);
	printf("총점 : %d \n", total);*/

	//int age;
	//printf("나이를 입력하시오 : ");
	//int ret = scanf("%d", &age); 
	////주소값을 이용한다./ 리턴값이 있는데, 이는 정상적인 입력이 들어갔는지 확인한다. (1 == 정상, 그 외 == 비정상) -> printf에도 존재함
	//printf("나이는 %d 입니다.\n", age);

	//if (ret == 1)
	//{
	//	printf("정상");
	//	printf("리턴값은 %d 입니다.", ret);
	//}
	//else
	//{
	//	printf("비정상");
	//	printf("리턴값은 %d 입니다.", ret);
	//}

	//int age;
	//double height;
	//printf("나이와 키를 입력하시오 : ");
	//scanf("%d%lf", &age, &height); // 메모리 아끼기 위해 변수 선언 X
	//printf("나이는 %d살, 키는 %.1lfcm입니다\n", age, height); // double형은 %ㅣf를 사용한다. 

	//char grade;
	//char name[20];

	//printf("학점 입력 : ");
	//scanf("%c", &grade);
	//printf("이름 입력 : ");
	//scanf("%s", name);
	//printf("%s의 학점은 %c 입니다.\n", name, grade);

	//char name[128];
	//scanf("%s", name);//배열의 이름은 첫 변수의 주소이다. 
	

	// %(나머지) 연산 잘 쓰기!
	
	//double apple, apple1;
	//int banana, banana1;
	//int orange;

	//apple = 5.0 / 2.0;
	//banana = 5 / 2;
	//orange = 5 % 2;
	//apple1 = 5. / 2; //소수점을 찍으면 int 보다 큰 자료형인 float로 읽는다.
	//banana1 = 5.0 / 2.0;

	//printf("apple : %.1lf\n", apple);
	//printf("banana : %d\n", banana);
	//printf("orange : %d\n", orange);
	//printf("apple1 : %.1lf\n", apple1);
	//printf("banana1 : %d\n", banana1);

	//int a = 5.0 / 2;
	//int b = 5 / 2.0;

	//double a1 = 5.0 / 2;
	//double b1 = 5 / 2.0;

	//printf("a : %d\n", a);
	//printf("b : %d\n", b);
	//printf("a1 : %d\n", a1); //변수의 자료형에 주의해서 형식지정자 사용. 
	//printf("b1: %d\n\n", b1);
	//
	//printf("a : %f\n", a);
	//printf("b : %f\n", b);
	//printf("a1 : %f\n", a1);
	//printf("b1: %f\n", b1);

	//int a = 5;
	//int b = 2;

	////a++; //a = a + 1, 후위형 증감연산자. (연산과정을 모두 한 후 더한다)
	////++a; // 전위형 증감연산자. (먼저 더하고, 연산을 실행한다)

	//printf("%d\n", ++b); // 증감연산자는 변수에 영향을 미친다. (일반 연산은 영향 X)
	//printf("%d\n", b);

	//int a = 5, b = 5;
	//int pre, post;

	//printf("초기값 a = %d, b = %d\n", a, b);

	//pre = (++a) * 3;
	//post = (b++) * 3; // b++ 가장 마지막에 연산됨

	//printf("현재값 a = %d, b = %d\n", a, b);
	//printf("전위형 : (++a) * 3 = %d, 후위형 : (b++) * 3 = %d\n", pre, post);
	//

	//int a = 5;
	//int b = 2;

	//printf("%d\n", a > b);// 참이면 1, 거짓이면 0 출력.
	//printf("%d\n", a >= b);// 참이면 1, 거짓이면 0 출력.
	//printf("%d\n", a <= b);// 참이면 1, 거짓이면 0 출력.
	//printf("%d\n", a < b);// 참이면 1, 거짓이면 0 출력.
	//printf("%d\n", a == b);// 참이면 1, 거짓이면 0 출력.
	//printf("%d\n", a != b);// 참이면 1, 거짓이면 0 출력.

	// && || !

	/*double a = 4.0, b = 1.2;

	printf("%0.1lf + %0.1lf = %.1lf\n", a, b, a + b);
	printf("%0.1lf - %0.1lf = %.1lf\n", a, b, a - b);
	printf("%0.1lf * %0.1lf = %.1lf\n", a, b, a * b);
	printf("%0.1lf / %0.1lf = %.1lf\n", a, b, a / b);*/

	/*int a, b, tot;
	double avg;

	printf("두 과목의 점수 : ");
	scanf(" %d %d", &a, &b);
	tot = a + b;
	avg = tot / 2.;

	printf("평균 : %0.1lf\n", avg);*/

	/*float Kor = 3., eng = 5., mat = 4., credits;
	float kScore = 3.8f, eScore=4.4, mScore=3.9, grade;

	credits = Kor + eng + mat;

	grade = (Kor * kScore + eng * eScore + mat * mScore) / credits;

	int out = (credits >= 10) && (grade > 4.0);

	printf("%d\n", out);*/

/*
	Q1. 인간 수명이 100년이라고 가정하고 
	담배 한 개피를 피우면 수명이 3시간 40분 단축된다고 한다.
	어떤 사람이 성인 (20살로 가정)이 된 이후
	N년간 하루에 M개피씩 담배를 피웠다면
	수명은 얼마나 단축되었고 몇 살 까지 살 수 있는가?

	ex) N = 20, M = 3
	결과>
		줄어든 수명 : 00일 00시 00분
		기대 수명 : 00살 00일 00시 00분
*/
	
	const unsigned int Year_To_Day = 365;
	const unsigned int Day_To_Hour = 24;
	const unsigned int Hour_To_Min = 60;
	
	unsigned int N, M;								   // N년간 하루에 M개피씩 담배를 피웠다면
	unsigned int Decreased_Life_Min;				  //줄어든 수명을 분으로 환산
	unsigned int D_year, D_min, D_hour, D_day;		 // 분으로 환산한 줄어든 수명을 년, 일, 시간, 분으로 표현
	unsigned int Expect_Life_Min;					//기대 수명을 분으로 환산
	unsigned int Ex_year, Ex_day, Ex_hour, Ex_min; // 분으로 환산한 기대 수명을 년, 일, 시간, 분으로 표현
	
	
	// N, M값 입력
	printf("하루에 핀 담배 수 : ");
	scanf("%d", &M);
	printf("담패를 핀 년수 : ");
	scanf("%d", &N);
	
	
	//줄어든 수명 = (3*60+40)*M*365*N
	Decreased_Life_Min = ((3 * Hour_To_Min) + 40) * M * Year_To_Day * N;
	D_min = (Decreased_Life_Min % 60);
	D_hour = ((Decreased_Life_Min / 60) % 24);
	D_day = ((Decreased_Life_Min / (24 * 60)) % 365);
	D_year = (Decreased_Life_Min / (365 * 60 * 24));
	
	
	//기대 수명 = 100*365*24*60 - (3*60+40)*M*365*N
	Expect_Life_Min = (100 * Year_To_Day * Day_To_Hour * Hour_To_Min) - ((3 * Hour_To_Min + 40) * M * Year_To_Day * N);
	Ex_min = (Expect_Life_Min % 60);
	Ex_hour = ((Expect_Life_Min / 60) % 24);
	Ex_day = ((Expect_Life_Min / (60 * 24)) % 365);
	Ex_year = (Expect_Life_Min / (365 * 60 * 24));
	
	
	printf("줄어든 수명 : %d살  %d일  %d시  %d분\n", D_year, D_day, D_hour, D_min);
	printf("기대 수명 : %d살  %d일  %d시  %d분\n", Ex_year, Ex_day, Ex_hour, Ex_min);
	
return 0;
}