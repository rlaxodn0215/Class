#include "Move.h"
#include<iostream>

using namespace std;


Move::Move(double a, double b)
{
	x = a;
	y = b;
}
void Move::showmove()const
{
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
}
Move Move::add(const Move& m) const
{
	Move temp;
	temp.x = x+ m.x;
	temp.y = y+ m.y;
	return temp;
}
void Move::reset(double a, double b)
{
	x = a;
	y = b;
}