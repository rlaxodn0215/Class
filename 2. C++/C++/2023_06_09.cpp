#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<stdlib.h>
#include"cVector3.h"

using namespace std;

void main()
{

	cVector3 u(-1,3,2);
	cVector3 v(3,-4,1);

	cout << u << endl << v << endl;

	cout << "u + v = " << u + v << endl;
	cout << "u - v = " << u - v << endl;
	cout << "3u + 2v = " << 3*u + 2*v << endl;
	cout << "-2*u + v = " <<-2*u + v<< endl;

	cout << "Normalize u : " << u.Normalize() << endl;
	cout << "Normalize v : " << v.Normalize() << endl;
	cout << endl;

	cVector3 u1(1, 1, 1);
	cVector3 v1(2, 3, 4);
	cout << u1 << endl << v1 << endl;
	cout << "Angle u,v : " << u1.Angle(v1) << endl;
	cout << endl;

	cVector3 u2(1, 1, 0);
	cVector3 v2(-2, 2, 0);
	cout << u2 << endl << v2 << endl;
	cout << "Angle u,v : " << u2.Angle(v2) << endl;
	cout << endl;

	cVector3 u3(-1, -1, -1);
	cVector3 v3(3, 1, 0);
	cout << u3 << endl << v3 << endl;
	cout << "Angle u,v : " << u3.Angle(v3) << endl;
	cout << endl;

	cVector3 A(0, 0, 0);
	cVector3 B(0, 1, 3);
	cVector3 C(5, 1, 0);

	cVector3 AB = B - A;
	cVector3 AC = C - A;

	cout << "¹ý¼± º¤ÅÍ: " << AB.Cross(AC) << endl;
	cout << endl;


}