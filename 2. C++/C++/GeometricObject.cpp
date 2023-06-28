#include "GeometricObject.h"
#include<cmath>

//GeometricObject
GeometricObject::GeometricObject():posX(0),posY(0)
{
}

GeometricObject::GeometricObject(double x, double y): posX(x),posY(y)
{
}

GeometricObject::~GeometricObject()
{
}

const double GeometricObject::getArea()
{
    return NULL;
}

const double GeometricObject::getPerimeter()
{
    return NULL;
}

const bool GeometricObject::contains(double x, double y)
{
    return NULL;
}

const bool GeometricObject::contains(const GeometricObject& geo)
{
    return NULL;
}

const bool GeometricObject::overlaps(const GeometricObject& geo)
{
    return NULL;
}


//Circle2D
double Circle2D::getRadius() const
{
    return radius;
}

Circle2D::Circle2D() : GeometricObject()
{
    radius = 1;
}

Circle2D::Circle2D(double x, double y, double rad): GeometricObject(x,y)
{
    radius = rad;
}

const double Circle2D::getArea()
{
    return (radius * radius * PI);
}

const double Circle2D::getPerimeter()
{
    return (2 * radius * PI);
}

const bool Circle2D::contains(double x, double y)
{
    double  contain = (x - getX()) * (x - getX()) + (y - getY()) * (y - getY()) - radius * radius;

    if (contain <= 0)
    {
        return true;
    }

    else
    {
        return false;
    }

}

const bool Circle2D::contains(const Circle2D& cir)
{

    double length = sqrt((getX() - cir.getX()) * (getX() - cir.getX()) + (getY() - cir.getY()) * (getY() - cir.getY()));

    if (length <= cir.radius - radius)
    {
        return true;
    }

    else
    {
        return false;
    }
}

const bool Circle2D::overlaps(const Circle2D& cir)
{
    double length = sqrt((getX() - cir.getX()) * (getX() - cir.getX()) + (getY() - cir.getY()) * (getY() - cir.getY()));

    if (length > abs(cir.radius - radius) && length <= cir.radius + radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Rectangle2D
double Rectangle2D::getWidth() const
{
    return width;
}

double Rectangle2D::getHeight() const
{
    return height;
}


void Rectangle2D::set_Width_Height(double w, double h)
{
    width = w;
    height = h;
}

Rectangle2D::Rectangle2D() : GeometricObject()
{
    width = 1;
    height = 1;
}

Rectangle2D::Rectangle2D(double x, double y, double w, double h): GeometricObject(x,y)
{
    width = w;
    height = h;
}

const double Rectangle2D::getArea() const
{
    return (width * height);
}

const double Rectangle2D::getPerimeter() const
{
    return 2 * (width + height);
}

const bool Rectangle2D::contains(double x, double y)
{
    if ((x >= getX() - width / 2 && x <= getX() + width / 2) && (y >= getY() - height / 2 && y <= getY() + height / 2))
    {
        return true;
    }

    else
    {
        return false;
    }

}

const bool Rectangle2D::contains(const Rectangle2D& r)
{

    if ((r.width - width) / 2 >= abs(r.getX() - getX()) && (r.height - height) / 2 >= abs(r.getY() - getY()))
    {
        return true;
    }

    else
    {
        return false;
    }
}

const bool Rectangle2D::overlaps(const Rectangle2D& r)
{
    if ((r.width + width) / 2 >= abs(r.getX() - getX()) && (r.height + height) / 2 >= abs(r.getY() - getY()))
    {
        return true;
    }

    else
    {
        return false;
    }
}


//MyPoint2D
MyPoint::MyPoint(): GeometricObject()
{
}

MyPoint::MyPoint(double x, double y):GeometricObject(x,y)
{
}


double MyPoint::distance(const MyPoint& P) const
{
    return sqrt((getX() - P.getX()) * (getX() - P.getX()) + (getY() - P.getY()) * (getY() - P.getY()));
}

bool contains(const MyPoint& p, const Circle2D& cir)
{
    double  contain = (p.getX() - cir.getX()) * (p.getX() - cir.getX()) + (p.getY() - cir.getY())
        * (p.getY() - cir.getY()) - cir.getRadius() * cir.getRadius();

    if (contain <= 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool contains(const MyPoint& p, const Rectangle2D& rec)
{
    if ((p.getX() >= rec.getX() - rec.getWidth() / 2 && p.getX() <= rec.getX() + rec.getWidth() / 2) &&
        (p.getY() >= rec.getY() - rec.getHeight() / 2 && p.getY() <= rec.getY() + rec.getHeight() / 2))
    {
        return true;
    }

    else
    {
        return false;
    }
}
