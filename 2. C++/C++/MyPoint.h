#pragma once
#include "Circle2D.h"
#include "Rectangle2D.h"

class MyPoint
{
private:
	double posX;
	double posY;
public:
	MyPoint();
	MyPoint(double x, double y);
	double getX() const;
	double getY() const;
	double distance(const MyPoint&) const;

	friend bool contains(const MyPoint& p, const Circle2D& cir);
	friend bool contains(const MyPoint& p, const Rectangle2D& rec);

};

