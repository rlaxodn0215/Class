#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h> //string �Լ� �̿�

int main()
{
	//unsigned char	alphabet; // 0 ~ 255
	//unsigned int	year, month;
	//float	pi;
	//double	doublePI;

	//alphabet = 'a'; // ""�� ���ڿ��� ���´�.
	//year = 2023;
	//pi = 3.14f;
	//doublePI = 3.14;
	//month = 4;
	//year = month;

	//int a;
	//int b, c;
	//double da; // ���� ����, �� ���� �ʱ�ȭ
	//char ch;

	//a = 10;
	//b = a;
	//c = a + 20;
	//da = 3.5;
	//ch = 'A';

	//printf("���� a�� �� : %d\n", a);
	//printf("���� b�� �� : %d\n", b);
	//printf("���� c�� �� : %d\n", c);
	//printf("���� da�� �� : %.1f\n", da);
	//printf("���� ch�� �� : %c\n", ch);

	//char ch1 = 'A';
	//char ch2 = 65;

	//printf("���� %c�� �ƽ�Ű �ڵ� �� : %d\n", ch1, ch1);
	//printf("�ƽ�Ű �ڵ� ���� %d�� ���� : %c\n", ch2, ch2);

	//short sh = 1000;

	//if (sh > 32767)
	//	printf("short ũ�� �̻��� �� �Դϴ�..."); // �� �ʰ��� ���! -> ����ó�� �ʼ�!!

	//printf("%d\n", sizeof(sh));

	// ������ �� �ʰ��� �ʰ��� ����ŭ �ٸ� �����Ϳ� ����
	//

	//float ft = 1.234567890123456789;
	//double db = 1.234567890123456789;

	//printf("float�� ������ ��	: %.20f\n", ft);
	//printf("double�� ������ ��	: %.20f\n", db);

	//float a = 0.12f;
	//a *=10;
	//printf("%.20f\n", a); // (! = 1.2) �Ǽ��� �ڷ����� �Ǵ��� �� ���� ����

	/*int a;
	a += 1;
	printf("%d\n", a);*/

	//char name[4+1] = "hong";//\0
	//���ڿ� ���� '\0'�� �߰��Ǿ� ���ڼ��� �ϳ� ���Ѱ��� �迭�� �ִ´�. -> �迭 �����ʹ� ���۰��� �����ϱ� ������ ������ ���� �־�� �Ѵ�. 

	//name = "gil"; -> �ȵ�
	//printf("%s \n", name);

	//char name[128];

	//strcpy(name, "hong"); // strcpy_s(name,128, "hong");
	//
	//printf("%s \n", name);

	//const int age = 25; // ������ ���ȭ (����X)

	/*int nnumber = 0;
	int inumber = 0;
	char ca = 'c';
	char strname[128];
	char sname[128];
	float fnumber = 0.0f;
	double dnumber = 0.0;*/

	//������ �и��ϰ� �ϴ� ������ ���ϱ� (�� ������!)

	/*int Kor = 70, Eng = 80, Mat = 90;
	int total = 0;

	total = Kor + Eng + Mat;
	printf("���� : %d, ���� : %d, ���� : %d \n", Kor, Eng, Mat);
	printf("���� : %d \n", total);*/

	//int age;
	//printf("���̸� �Է��Ͻÿ� : ");
	//int ret = scanf("%d", &age); 
	////�ּҰ��� �̿��Ѵ�./ ���ϰ��� �ִµ�, �̴� �������� �Է��� ������ Ȯ���Ѵ�. (1 == ����, �� �� == ������) -> printf���� ������
	//printf("���̴� %d �Դϴ�.\n", age);

	//if (ret == 1)
	//{
	//	printf("����");
	//	printf("���ϰ��� %d �Դϴ�.", ret);
	//}
	//else
	//{
	//	printf("������");
	//	printf("���ϰ��� %d �Դϴ�.", ret);
	//}

	//int age;
	//double height;
	//printf("���̿� Ű�� �Է��Ͻÿ� : ");
	//scanf("%d%lf", &age, &height); // �޸� �Ƴ��� ���� ���� ���� X
	//printf("���̴� %d��, Ű�� %.1lfcm�Դϴ�\n", age, height); // double���� %��f�� ����Ѵ�. 

	//char grade;
	//char name[20];

	//printf("���� �Է� : ");
	//scanf("%c", &grade);
	//printf("�̸� �Է� : ");
	//scanf("%s", name);
	//printf("%s�� ������ %c �Դϴ�.\n", name, grade);

	//char name[128];
	//scanf("%s", name);//�迭�� �̸��� ù ������ �ּ��̴�. 
	

	// %(������) ���� �� ����!
	
	//double apple, apple1;
	//int banana, banana1;
	//int orange;

	//apple = 5.0 / 2.0;
	//banana = 5 / 2;
	//orange = 5 % 2;
	//apple1 = 5. / 2; //�Ҽ����� ������ int ���� ū �ڷ����� float�� �д´�.
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
	//printf("a1 : %d\n", a1); //������ �ڷ����� �����ؼ� ���������� ���. 
	//printf("b1: %d\n\n", b1);
	//
	//printf("a : %f\n", a);
	//printf("b : %f\n", b);
	//printf("a1 : %f\n", a1);
	//printf("b1: %f\n", b1);

	//int a = 5;
	//int b = 2;

	////a++; //a = a + 1, ������ ����������. (��������� ��� �� �� ���Ѵ�)
	////++a; // ������ ����������. (���� ���ϰ�, ������ �����Ѵ�)

	//printf("%d\n", ++b); // ���������ڴ� ������ ������ ��ģ��. (�Ϲ� ������ ���� X)
	//printf("%d\n", b);

	//int a = 5, b = 5;
	//int pre, post;

	//printf("�ʱⰪ a = %d, b = %d\n", a, b);

	//pre = (++a) * 3;
	//post = (b++) * 3; // b++ ���� �������� �����

	//printf("���簪 a = %d, b = %d\n", a, b);
	//printf("������ : (++a) * 3 = %d, ������ : (b++) * 3 = %d\n", pre, post);
	//

	//int a = 5;
	//int b = 2;

	//printf("%d\n", a > b);// ���̸� 1, �����̸� 0 ���.
	//printf("%d\n", a >= b);// ���̸� 1, �����̸� 0 ���.
	//printf("%d\n", a <= b);// ���̸� 1, �����̸� 0 ���.
	//printf("%d\n", a < b);// ���̸� 1, �����̸� 0 ���.
	//printf("%d\n", a == b);// ���̸� 1, �����̸� 0 ���.
	//printf("%d\n", a != b);// ���̸� 1, �����̸� 0 ���.

	// && || !

	/*double a = 4.0, b = 1.2;

	printf("%0.1lf + %0.1lf = %.1lf\n", a, b, a + b);
	printf("%0.1lf - %0.1lf = %.1lf\n", a, b, a - b);
	printf("%0.1lf * %0.1lf = %.1lf\n", a, b, a * b);
	printf("%0.1lf / %0.1lf = %.1lf\n", a, b, a / b);*/

	/*int a, b, tot;
	double avg;

	printf("�� ������ ���� : ");
	scanf(" %d %d", &a, &b);
	tot = a + b;
	avg = tot / 2.;

	printf("��� : %0.1lf\n", avg);*/

	/*float Kor = 3., eng = 5., mat = 4., credits;
	float kScore = 3.8f, eScore=4.4, mScore=3.9, grade;

	credits = Kor + eng + mat;

	grade = (Kor * kScore + eng * eScore + mat * mScore) / credits;

	int out = (credits >= 10) && (grade > 4.0);

	printf("%d\n", out);*/

/*
	Q1. �ΰ� ������ 100���̶�� �����ϰ� 
	��� �� ���Ǹ� �ǿ�� ������ 3�ð� 40�� ����ȴٰ� �Ѵ�.
	� ����� ���� (20��� ����)�� �� ����
	N�Ⱓ �Ϸ翡 M���Ǿ� ��踦 �ǿ��ٸ�
	������ �󸶳� ����Ǿ��� �� �� ���� �� �� �ִ°�?

	ex) N = 20, M = 3
	���>
		�پ�� ���� : 00�� 00�� 00��
		��� ���� : 00�� 00�� 00�� 00��
*/
	
	const unsigned int Year_To_Day = 365;
	const unsigned int Day_To_Hour = 24;
	const unsigned int Hour_To_Min = 60;
	
	unsigned int N, M;								   // N�Ⱓ �Ϸ翡 M���Ǿ� ��踦 �ǿ��ٸ�
	unsigned int Decreased_Life_Min;				  //�پ�� ������ ������ ȯ��
	unsigned int D_year, D_min, D_hour, D_day;		 // ������ ȯ���� �پ�� ������ ��, ��, �ð�, ������ ǥ��
	unsigned int Expect_Life_Min;					//��� ������ ������ ȯ��
	unsigned int Ex_year, Ex_day, Ex_hour, Ex_min; // ������ ȯ���� ��� ������ ��, ��, �ð�, ������ ǥ��
	
	
	// N, M�� �Է�
	printf("�Ϸ翡 �� ��� �� : ");
	scanf("%d", &M);
	printf("���и� �� ��� : ");
	scanf("%d", &N);
	
	
	//�پ�� ���� = (3*60+40)*M*365*N
	Decreased_Life_Min = ((3 * Hour_To_Min) + 40) * M * Year_To_Day * N;
	D_min = (Decreased_Life_Min % 60);
	D_hour = ((Decreased_Life_Min / 60) % 24);
	D_day = ((Decreased_Life_Min / (24 * 60)) % 365);
	D_year = (Decreased_Life_Min / (365 * 60 * 24));
	
	
	//��� ���� = 100*365*24*60 - (3*60+40)*M*365*N
	Expect_Life_Min = (100 * Year_To_Day * Day_To_Hour * Hour_To_Min) - ((3 * Hour_To_Min + 40) * M * Year_To_Day * N);
	Ex_min = (Expect_Life_Min % 60);
	Ex_hour = ((Expect_Life_Min / 60) % 24);
	Ex_day = ((Expect_Life_Min / (60 * 24)) % 365);
	Ex_year = (Expect_Life_Min / (365 * 60 * 24));
	
	
	printf("�پ�� ���� : %d��  %d��  %d��  %d��\n", D_year, D_day, D_hour, D_min);
	printf("��� ���� : %d��  %d��  %d��  %d��\n", Ex_year, Ex_day, Ex_hour, Ex_min);
	
return 0;
}