#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>
#include"GeometricObject.h"

using namespace std;

int main()
{


	//TableTennisPlayer player1("Tara", "Boomda", false);
	//RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
	//rplayer1.Name();
	//if (rplayer1.HasTable())
	//	cout << ": Ź���밡 �ִ�.\n";
	//else
	//	cout << ": Ź���밡 ����.\n";
	//player1.Name();
	//if (player1.HasTable())
	//	cout << ": Ź���밡 �ִ�.\n";
	//else
	//	cout << ": Ź���밡 ����.\n";

	//cout << "�̸�: ";
	//rplayer1.Name();
	//cout << "; ��ŷ: " << rplayer1.Rating() << endl;

	//RatedPlayer rplayer2(1212, player1);
	//cout << "�̸�: ";
	//rplayer2.Name();
	//cout << "; ��ŷ: " << rplayer2.Rating() << endl;

	//baseDMA shirt("Portabwlly", 8);
	//lacksDMA balloon("red", "Blimpo", 4);
	//hasDMA map("Mercator", "Buffalo Keys", 5);

	//cout << "baseDMA ��ü�� ����Ѵ�: \n";
	//cout << shirt << endl;
	//cout << "lacksDMA ��ü�� ����Ѵ�: \n";
	//cout << balloon << endl;
	//cout << "hasDMA ��ü�� �����Ѵ�: \n";
	//cout << map << endl;
	//lacksDMA balloons2(balloon);
	//cout << "lacksDMA ������: \n";
	//cout << balloons2 << endl;
	//hasDMA map2;
	//map2 = map;
	//cout << "hasDMA ���԰��: \n";
	//cout << map2 << endl;

	GeometricObject geo;
	MyPoint p1, p2(10, 30.5);
	Rectangle2D r1(2, 2, 5.5, 4.9), r2(4, 5, 10.5, 3.2);
	Circle2D c1(2.5, 3.5, 6);

	cout << "p1, p2�� �Ÿ�: " << p1.distance(p2) << endl;

	cout << boolalpha;
	cout << "p2�� r1�� �����ϴ°�?: " << contains(p2, r1) << endl;
	cout << "p1�� c1�� �����ϴ°�?: " << contains(p2, c1) << endl;

	return 0;
}