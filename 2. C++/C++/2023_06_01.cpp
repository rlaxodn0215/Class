#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>
#include<cmath>
#include<fstream> //파일 입출력 라이브러리

using namespace std;

//int sum_arr(const int* begin, const int* end);
//unsigned int c_in_str(const char* str, char ch);

//struct polar
//{
//	double distance;
//	double angle;
//};
//
//struct rect
//{
//	double x;
//	double y;
//};
//
//polar rect_to_polar(const rect* xypos);
//void show_polar(const polar* dapos);

//const int Len = 66;
//const int Divs = 6;
//void subdivided(char ar[], int low, int high, int level);

//const double* f1(const double ar[], int n);
//const double* f2(const double[], int);
//const double* f3(const double*, int);

double add(double x, double y);
double sub(double x, double y);
double calculate (double x, double y, double (*pf)(double,double));

int main()
{
	/*double x1, y1, x2, y2, x3, y3, area;

	cout << "x1, y1 : ";
	cin >> x1 >> y1;
	cout << "x2, y2 : ";
	cin >> x2 >> y2;
	cout << "x3, y3 : ";
	cin >> x3 >> y3;

	area = 0.5 * abs((x3-x1)*(y2-y1)+(x2-x1)*(y3-y1));

	cout << "면적: " << area << endl;*/


	//string password = "";

	//while (1)
	//{
	//	cout << "설정할 비밀번호를 입력하세요 : ";
	//	cin >> password;

	//	if (password.size() >= 8)
	//	{
	//		int wordcount = 0;
	//		int numcount = 0;

	//		for (int i = 0; i < password.size(); i++)
	//		{
	//			if (isdigit(password[i]))
	//			{
	//				numcount++;
	//			}

	//			else if (isalpha(password[i]))
	//			{
	//				wordcount++;
	//			}
	//		}

	//		if (wordcount + numcount == password.size() && numcount >= 2)
	//		{
	//			cout << "Valid password" << endl;
	//			break;
	//		}

	//		else
	//		{
	//			cout << "Invalid password" << endl;
	//		}
	//	}

	//	else
	//	{
	//		cout << "Invalid password" << endl;
	//	}

	//}

	//const int ArSize = 8;
	//int cookies[ArSize] = { 1,2,4,8,16,32,64,128 };

	//int sum = sum_arr(cookies, cookies + ArSize);
	//cout << "먹은 과자 수 합계: " << sum << endl;
	//sum = sum_arr(cookies, cookies + 3);
	//cout << "처음 세 사람은 과자 " << sum << "개를 먹었습니다" << endl;
	//sum = sum_arr(cookies + 4, cookies + 8);
	//cout << "마지막 네 사람은 과자 " << sum << "개를 먹었습니다" << endl;

	//char mmm[15] = "minimum";

	//char* wail="ululate"; //const 필요함

	//unsigned int ms = c_in_str(mmm, 'm');
	//unsigned int us = c_in_str(wail, 'u');
	//cout << mmm << "에는 m이" << ms << "개 들어 있습니다" << endl;
	//cout<<wail<<"에는 u가"<<us<< "개 들어 있습니다" << endl;

	/*int a, b;
	while (cin >> a >> b)
	{
		cout << "printf" << endl;
	}*/

	/*char ruler[Len];
	int i;
	for (i = 1; i < Len - 2; i++)
		ruler[i] = ' ';

		ruler[Len - 1] = '\0';
		int max = Len - 2;
		int min = 0;
		ruler[min] = ruler[max] = '|';
		cout << ruler << endl;

		for (i = 1; i <= Divs; i++)
		{
			subdivided(ruler, min, max, i);
			cout << ruler << endl;
			for (int j = 0; j < Len - 2; j++)
			{
				ruler[j] = ' ';
			}
		}
	*/

	//double av[3] = { 1112.3,1542.6,2227.9 };

	//const double* (*p1)(const double*, int) = f1;
	//auto p2 = f2;
	//cout << "함수 포인터:" << endl;
	//cout << "주소 값" << endl;
	//cout << (*p1)(av, 3) << " : " << *(*p1)(av, 3) << endl;
	//cout << p2(av, 3) << " : " << *p2(av, 3) << endl;

	//const double* (*pa[3])(const double*, int) = { f1,f2,f3 };

	//auto pb = pa;
	//cout << "\n함수 포인터를 원소로 가지는 배열: \n";
	//cout << "주소 값\n";

	//for (int i = 0; i < 3; i++)
	//{
	//	cout << pa[i](av, 3) << " : " << *pa[i](av,3) << endl;
	//}

	//cout << "\n함수 포인터를 원소로 가지는 배열: \n";
	//cout << "주소 값\n";

	//for (int i = 0; i < 3; i++)
	//{
	//	cout << pb[i](av, 3) << " : " << *pb[i](av, 3) << endl;
	//}

	double (*pf[2])(double, double) = { add,sub };

	while (1)
	{
		double x, y;
		cout << "숫자입력 : ";
		cin >> x >> y;

		cout << "두 수의 합: " << calculate(x, y, pf[0]) << endl;
		cout << "두 수의 차: " << calculate(x, y, pf[1]) << endl;
	}
	return 0;
}

double calculate(double x, double y,double (*pf)(double, double))
{
	return pf(x, y);
}

double add(double x, double y)
{
	return x + y;
}

double sub(double x, double y)
{
	return x - y;
}

//const double* f1(const double *ar, int n)
//{
//	return ar;
//}
//const double* f2(const double ar[], int)
//{
//	return ar + 1;
//
//}
//const double* f3(const double ar[], int n)
//{
//	return ar + 2;
//}

//void subdivided(char ar[], int low, int high, int level)
//{
//	if (level == 0)
//		return;
//	int mid = (high + low) / 2;
//	ar[mid] = '|';
//
//	subdivided(ar, low, mid, level - 1);
//	subdivided(ar, mid, high, level - 1);
//}

//polar rect_to_polar(const rect* xypos)
//{
//	polar answer;
//	answer.distance = sqrt(xypos->x * xypos->x + xypos->y * xypos->y);
//	answer.angle = atan2(xypos->y, xypos->x);
//
//	return answer;
//}
//void show_polar(const polar* dapos)
//{
//	const double Rad_to_deg = 57.29577951;
//
//	cout << "거리 = " << dapos->distance;
//	cout << "각도 = " << dapos->angle * Rad_to_deg;
//	cout << "도" << endl;
//}

//unsigned int c_in_str(const char* str, char ch)
//{
//	int count = 0;
//
//	while (*str)
//	{
//		if (*str == ch)
//			count++;
//		str++;
//	}
//
//	return count;
//}

//int sum_arr(const int* begin, const int* end)
//{
//	const int* pt;
//
//	int total = 0;
//	for (pt = begin; pt != end; pt++)
//	{
//		total += *pt;
//	}
//
//	return total;
//}