#pragma once
#define PI (3.141592)

class Circle2D
{
private:
	double posX;
	double posY;
	double radius;

public:
	double getX() const;
	double getY() const;
	double getRadius() const;
	Circle2D();
	Circle2D(double x, double y, double radius);
	const double getArea();
	const double getPerimeter();
	const bool contains(double x, double y);
	const bool contains(const Circle2D & cir);
	const bool overlaps(const Circle2D & cir);
};

