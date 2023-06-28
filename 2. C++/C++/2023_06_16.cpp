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
	//	cout << ": 탁구대가 있다.\n";
	//else
	//	cout << ": 탁구대가 없다.\n";
	//player1.Name();
	//if (player1.HasTable())
	//	cout << ": 탁구대가 있다.\n";
	//else
	//	cout << ": 탁구대가 없다.\n";

	//cout << "이름: ";
	//rplayer1.Name();
	//cout << "; 랭킹: " << rplayer1.Rating() << endl;

	//RatedPlayer rplayer2(1212, player1);
	//cout << "이름: ";
	//rplayer2.Name();
	//cout << "; 랭킹: " << rplayer2.Rating() << endl;

	//baseDMA shirt("Portabwlly", 8);
	//lacksDMA balloon("red", "Blimpo", 4);
	//hasDMA map("Mercator", "Buffalo Keys", 5);

	//cout << "baseDMA 객체를 출력한다: \n";
	//cout << shirt << endl;
	//cout << "lacksDMA 객체를 출력한다: \n";
	//cout << balloon << endl;
	//cout << "hasDMA 객체를 츨력한다: \n";
	//cout << map << endl;
	//lacksDMA balloons2(balloon);
	//cout << "lacksDMA 복사결과: \n";
	//cout << balloons2 << endl;
	//hasDMA map2;
	//map2 = map;
	//cout << "hasDMA 대입결과: \n";
	//cout << map2 << endl;

	GeometricObject geo;
	MyPoint p1, p2(10, 30.5);
	Rectangle2D r1(2, 2, 5.5, 4.9), r2(4, 5, 10.5, 3.2);
	Circle2D c1(2.5, 3.5, 6);

	cout << "p1, p2의 거리: " << p1.distance(p2) << endl;

	cout << boolalpha;
	cout << "p2가 r1에 포함하는가?: " << contains(p2, r1) << endl;
	cout << "p1이 c1에 포함하는가?: " << contains(p2, c1) << endl;

	return 0;
}