#pragma once

class Rectangle2D
{
private:
	double posX;
	double posY;
	double width;
	double height;

public:
	double getX() const;
	double getY() const;
	double getWidth() const;
	double getHeight() const;
	void setXY(double x,double y);
	void set_Width_Height(double width,double height);

	Rectangle2D();
	Rectangle2D(double x, double y, double width, double height);

	double getArea() const;
	double getPerimeter() const;

	bool contains(double x, double y);
	bool contains(const Rectangle2D& r);
	bool overlaps(const Rectangle2D& r);

};

