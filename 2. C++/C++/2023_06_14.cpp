#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include"Rectangle2D.h"
#include"Circle2D.h"
#include"MyPoint.h"
#include"strngbad.h"

using namespace std;

//void callme1(StringBad&);
//void callme2(StringBad);

int main()
{
	/*Rectangle2D r1(2, 2, 5.5, 4.9), r2(4, 5, 10.5, 3.2), r3(3, 5, 2.3, 5.4);

	cout << "r1�� ����: " << r1.getArea() << endl;
	cout << "r1�� �ѷ�: " << r1.getPerimeter() << endl;
	cout << boolalpha;
	cout << "r1.contains(r2): " << r1.contains(r2) << endl;
	cout << "r1.overlaps(r3): " << r1.overlaps(r3) << endl;*/

	//{
	//	cout << "���� ����� �����Ѵ�" << endl;
	//	StringBad headline1("Celery Stalks at Midnught");
	//	StringBad headline2("Lettuce Prey");
	//	StringBad sports("Spinach Leaves Bowl for Dollars");
	//	cout << "headline1: " << headline1 << endl;
	//	cout << "headline2: " << headline2 << endl;
	//	cout << "sports: " << sports << endl;
	//	callme1(headline1);
	//	cout << "headline1: " << headline1 << endl;
	//	callme2(headline2);
	//	cout << "headline2: " << headline2 << endl;
	//	cout << "�ϳ��� ��ü�� �ٸ� ��ü�� ����" << endl;
	//	StringBad knot;
	//	knot = headline1;
	//	cout << "knot: " << knot << endl;
	//	cout << "�� ����� �������´�" << endl;

	//}

	//cout << "main()�� ��\n";

	MyPoint p1, p2(10,30.5);
	Rectangle2D r1(2, 2, 5.5, 4.9), r2(4, 5, 10.5, 3.2);
	Circle2D c1(2.5, 3.5, 6);

	cout << "p1, p2�� �Ÿ�: " << p1.distance(p2) << endl;

	cout << boolalpha;
	cout << "p2�� r1�� �����ϴ°�?: " << contains(p2, r1) << endl;
	cout << "p1�� c1�� �����ϴ°�?: " << contains(p2, c1) << endl;

	return 0;
}

//void callme1(StringBad& rsb)
//{
//	cout << "������ ���޵� StringBad: \n";
//	cout << "    \"" << rsb << "\"\n";
//}
//
//void callme2(StringBad sb)
//{
//	cout << "������ ���޵� StringBad: \n";
//	cout << "    \"" << sb << "\"\n";
//}