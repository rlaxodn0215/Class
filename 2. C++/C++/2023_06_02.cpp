#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>
#include<cmath>
#include<fstream> //���� ����� ���̺귯��

using namespace std;

//template<typename T>
//void Swap(T& a, T& b);
//
//template<typename T>
//void Swap(T* a, T* b, int n);
//
//void Show(int a[]);
//
//const int Lim = 8;

template<typename T>
void Swap(T& a, T& b);

struct job
{
	char name[40];
	double salary;
	int floor;
};

template<>void Swap<job>(job& j1, job& j2);
void Show(job& j);

//struct circle
//{
//	double x0;
//	double y0;
//	double r;
//};
//
//void CheckInCircle(circle* round,double x,double y);

//void swapr(int& a, int& b);
//void swapp(int* p, int* q);
//void swapv(int a, int b);

//struct free_throws
//{
//	string name;
//	int made;
//	int attemps;
//	float percent;
//};
//
//void display(const free_throws& ft);
//void set_pc(free_throws& ft);
//free_throws & accumulate(free_throws& terget, const free_throws& source);

//string version1(const string& s1, const string& s2);
//const string& version2(string& s1, const string& s2);
//const string& version3(string& s1, const string& s2);

//unsigned long left(unsigned long num, unsigned ct);
//char* left(const char* str, int n = 1);

int main()
{

	//double x;
	//double y;
	//circle round;

	//while (1)
	//{
	//	cout << "r: ";
	//	cin >> round.r;
	//	cout << "x0, y0 : ";
	//	cin >> round.x0 >> round.y0;
	//	cout << "x, y : ";
	//	cin >> x >> y;

	//	CheckInCircle(&round,x,y);
	//}

	//double x1, y1, x2, y2, x3, y3, x4, y4;
	//double x, y;

	//double a, b, c, a1, b1, c1;

	//cout << "�� 4�� �Է� : ";
	//cin>> x1>> y1>> x2>> y2>> x3>> y3>> x4>> y4;

	/////ax+by=c
	//a = y2 - y1;
	//b = x1 - x2;
	//c = x1 * a + y1 * b;

	//a1 = y4 - y3;
	//b1 = x3 - x4;
	//c1 = x3 * a1 + y3 * b1;

	//double del = a * b1 - a1 * b;
	//
	//if (abs(del) <= 0.000000000001)
	//{
	//	cout << "�� ������ (����)�����ϴ�" << endl;
	//	return 0;
	//}

	//double delX = c * b1 - c1 * b;
	//double delY = a * c1 - c * a1;

	//x = delX / del;
	//y = delY / del;

	//cout << "�������� (" << x << "," << y << ") �̴�." << endl;

	/*int rats = 101;
	int& rodents = rats;

	cout << "rats = " << rats;
	cout << ", rodents = " << rodents << endl;

	cout << "rats address = " << &rats;
	cout << ", rodents address = " << &rodents << endl;

	int bunnies = 50;
	rodents = bunnies;
	cout << "bunnies = " << bunnies;
	cout << ", rats = " << rats;
	cout << ", rodents = " << rodents << endl;

	cout << "bunnies address = " << &bunnies;
	cout<<", rodents address = " << &rodents << endl;*/

	//int wallet1 = 3000;
	//int wallet2 = 3500;

	//cout << "����1 = " << wallet1 << "��";
	//cout << ", ����2 = " << wallet2 << "��" << endl;

	//cout << "������ �̿��Ͽ� ������� ��ȯ" << endl;
	//swapr(wallet1, wallet2);
	//cout << "����1 = " << wallet1 << "��";
	//cout << ", ����2 = " << wallet2 << "��" << endl;

	//cout << "�����͸� �̿��Ͽ� ������� ��ȯ" << endl;
	//swapp(&wallet1, &wallet2);
	//cout << "����1 = " << wallet1 << "��";
	//cout << ", ����2 = " << wallet2 << "��" << endl;

	//cout << "���� �̿��Ͽ� ���� ���� �õ�" << endl;
	//swapv(wallet1, wallet2);
	//cout << "����1 = " << wallet1 << "��";
	//cout << ", ����2 = " << wallet2 << "��" << endl;

	//free_throws one = { "Ifelsa Branch",13,14 };
	//free_throws two = { "Andor Knott",10,16 };
	//free_throws three = { "Minnie Max",7,9 };
	//free_throws four = { "Wily Looper",5,9 };
	//free_throws five = { "Long Long",6,14 };
	//free_throws team = { "Throwgoods",0,0 };

	//free_throws dup;
	//set_pc(one);
	//display(one);
	//accumulate(team, one);
	//display(team);

	//display(accumulate(team, two));
	//accumulate(accumulate(team, three), four);
	//display(team);

	//dup = accumulate(team, five);
	//cout << "team ���: "<<endl;
	//display(team);
	//cout << "�������� dup ���: " << endl;
	//display(dup);
	//set_pc(four);

	//accumulate(dup, five) = four;
	//cout << "���� ������ �ִ� ���� ���� dup ���: " << endl;
	//display(dup);

//string input;
//string copy;
//string result;
//
//cout << "���ڿ��� �Է��ϼ���: ";
//getline(cin, input);
//copy = input;
//cout << "�Է��� ���ڿ�: " << input << endl;
//result = version1(input, "***");
//cout << "�ٲ� ���ڿ�: " << result << endl;
//cout << "���� ���ڿ�: " << input << endl;
//
//result = version2(input, "###");
//cout << "�ٲ� ���ڿ�: " << result << endl;
//cout << "���� ���ڿ�: " << input << endl;
//
//cout << "���� ���ڿ� �缳��" << endl;
//input = copy;
//result = version3(input, "@@@");
//cout << "�ٲ� ���ڿ�: " << result << endl;
//cout << "���� ���ڿ�: " << input << endl;

	
	/*char* trip = "Hawaii!!";
	unsigned long n =12345678;
	int i;
	char* temp;
	for (i = 1; i < 10; i++)
	{
		cout << left(n, i) << endl;
		temp = left(trip, i);
		cout << temp << endl;
		delete[] temp;
	}*/

	//int i = 10, j = 20;
	//cout << "i, j = " << i << ", " << j << endl;
	//cout << "�����Ϸ��� ������ int�� ��ȯ�⸦ ����ϸ�" << endl;
	//Swap(i, j);
	//cout << "���� i, j = " << i << ", " << j << endl;

	//int d1[Lim] = { 0,7,0,4,1,7,7,6 };
	//int d2[Lim] = { 0,6,2,0,1,9,6,9 };
	//cout << "���� �迭" << endl;
	//Show(d1);
	//Show(d2);
	//Swap(d1, d2, Lim);
	//cout << "��ȯ�� �迭" << endl;
	//Show(d1);
	//Show(d2);

	cout.precision(2);
	cout.setf(ios::fixed, ios::floatfield);
	int i = 10,j = 20;
	cout << "i, j = " << i << ", " << j << endl;
	cout << "�����Ϸ��� ������ int�� ��ȯ�⸦ ����ϸ�" << endl;
	Swap(i, j);
	cout << "���� i,j = " << i << ", " << j << endl;

	job sue = { "Susan Yaffee",7300.60,7 };
	job sidney = { "Sidney Taffeee",78060.72,9 };

	cout << "job ��ȯ ��" << endl;
	Show(sue);
	Show(sidney);
	Swap(sue, sidney);
	cout << "job ��ȯ ��" << endl;
	Show(sue);
	Show(sidney);

	return 0;
}

template<typename T>
void Swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template<>void Swap<job>(job& j1, job& j2)
{
	double t1;
	int t2;
	t1 = j1.salary;
	j1.salary = j2.salary;
	j2.salary = t1;
	t2 = j2.floor;
	j1.floor = j2.floor;
	j2.floor = t2;
}
void Show(job& j);
//template<typename T>
//void Swap(T& a, T& b)
//{
//	T temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//template<typename T>
//void Swap(T a[], T b[], int n)
//{
//	T temp;
//	for (int i = 0; i < n; i++)
//	{
//		temp = a[i];
//		a[i] = b[i];
//		b[i] = temp;
//	}
//}
//
//void Show(int a[])
//{
//	cout << a[0] << a[1] << "/";
//	cout << a[2] << a[3] << "/";
//	for (int i = 4; i < Lim; i++)
//		cout << a[i];
//	cout << endl;
//}


//unsigned long left(unsigned long num, unsigned ct)
//{
//	unsigned digits = 1;
//	unsigned long n = num;
//
//	if (ct == 0 || num == 0) return 0;
//
//	while (n /= 10) digits++;
//
//	if (digits > ct)
//	{
//		ct = digits - ct;
//		while (ct--) num /= 10;
//		return num;
//	}
//
//	else
//		return num;
//}
//char* left(const char* str, int n = 1)
//{
//	if (n < 0) n = 0;
//	char *p = new char[n + 1];
//
//	int i;
//	for (i = 0; i < n && str[i]; i++)
//	{
//		p[i] = str[i];
//	}
//	while (i <= n)
//	{
//		p[i++] = '\0';
//	}
//
//	return p;
//}

//string version1(const string& s1, const string& s2)
//{
//	string temp;
//	temp = s2 + s1 + s2;
//	return temp;
//}
//const string& version2(string& s1, const string& s2)
//{
//	s1 = s2 + s1 + s2;
//	return s1;
//}
//const string& version3(string& s1, const string& s2)
//{
//	string temp;
//	temp = s2 + s1 + s2;
//	return temp;
//}

//void display(const free_throws& ft)
//{
//	cout << "name: " << ft.name << endl;
//	cout << "made: " << ft.made << endl;
//	cout << "attemps: " << ft.attemps << endl;
//	cout << "percent: " << ft.percent << endl;
//}
//
//void set_pc(free_throws& ft)
//{
//	if (ft.attemps != 0)
//		ft.percent = 100.0f * float(ft.made) / float(ft.attemps);
//	else
//		ft.percent = 0;
//}
//free_throws& accumulate(free_throws& target, const free_throws& source)
//{
//	target.attemps += source.attemps;
//	target.made += source.made;
//	set_pc(target);
//	return target;
//}

//void swapr(int& a, int& b)
//{
//	int temp = a;
//	a = b;
//	b = temp;
//}
//void swapp(int* p, int* q)
//{
//	int temp = *p;
//	*p = *q;
//	*q = temp;
//}
//void swapv(int a, int b)
//{
//	int temp = a;
//	a = b;
//	b = temp;
//}

//void CheckInCircle(circle* round, double x, double y)
//{
//	if (((x - round->x0) * (x - round->x0) + (y - round->y0) * (y - round->y0))
//		<= (round->r * round->r))
//	{
//		cout<<"��("<< x<<","<< y<<")"<<"�� ������("<<round->x0<<"," << round->y0 << ")" << "�̰� ";
//		cout << "�������� " << round->r << "�� �� �ȿ� �ֽ��ϴ�." << endl;
//	}
//
//	else
//	{
//		cout << "��(" << x << "," << y << ")" << "�� ������(" << round->x0 << "," << round->y0 << ")" << "�̰� ";
//		cout << "�������� " << round->r << "�� �� �ȿ� �����ϴ�." << endl;
//	}
//}