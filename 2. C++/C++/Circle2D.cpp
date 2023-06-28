#include "Circle2D.h"
#include<cmath>

double Circle2D::getX() const
{
    return posX;
}

double Circle2D::getY() const
{
    return posY;
}

double Circle2D::getRadius() const
{
    return radius;
}

Circle2D::Circle2D()
{
    posX = 0;
    posY = 0;
    radius = 1;
}

Circle2D::Circle2D(double x, double y, double rad)
{
    posX = x;
    posY = y;
    radius = rad;
}

const double Circle2D::getArea()
{
    return radius*radius*PI;
}

const double Circle2D::getPerimeter()
{
    return 2*radius*PI;
}

const bool Circle2D::contains(double x, double y)
{
    double  contain = (x - posX) * (x - posX) + (y - posY) * (y - posY) - radius * radius;

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

    double length = sqrt((posX - cir.posX) * (posX - cir.posX) + (posY - cir.posY) * (posY - cir.posY));

    if (length <= cir.radius-radius)
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
    double length = sqrt((posX - cir.posX) * (posX - cir.posX) + (posY - cir.posY) * (posY - cir.posY));

    if (length> abs(cir.radius - radius) && length <= cir.radius + radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}
