#pragma once
#define PI (3.141592)

class GeometricObject
{
private:
	double posX;
	double posY;
public:
	GeometricObject();
	GeometricObject(double x, double y);
	~GeometricObject();

	virtual const double getArea();
	virtual const double getPerimeter();
	virtual const bool contains(double x, double y);
	virtual const bool contains(const GeometricObject& geo);
	virtual const bool overlaps(const GeometricObject& geo);

	double getX() const { return posX; }
	double getY() const { return posY; }
};

class Circle2D : public GeometricObject
{
private:
	double radius;

public:
	double getRadius() const;
	Circle2D();
	Circle2D(double x, double y, double radius);

	virtual const double getArea();
	virtual const double getPerimeter();
	virtual const bool contains(double x, double y);
	virtual const bool contains(const Circle2D& cir);
	virtual const bool overlaps(const Circle2D& cir);
};

class Rectangle2D : public GeometricObject
{
private:
	double width;
	double height;

public:
	double getWidth() const;
	double getHeight() const;
	void set_Width_Height(double width, double height);

	Rectangle2D();
	Rectangle2D(double x, double y, double width, double height);

	virtual const double getArea() const;
	virtual const double getPerimeter() const;
	virtual const bool contains(double x, double y);
	virtual const bool contains(const Rectangle2D& r);
	virtual const bool overlaps(const Rectangle2D& r);

};

class MyPoint : GeometricObject
{
private:
public:
	MyPoint();
	MyPoint(double x, double y);
	double distance(const MyPoint&) const;

	friend bool contains(const MyPoint& p, const Circle2D& cir);
	friend bool contains(const MyPoint& p, const Rectangle2D& rec);

};
