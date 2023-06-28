#include "MyPoint.h"
#include<cmath>

MyPoint::MyPoint()
{
    posX = 0;
    posY = 0;
}

MyPoint::MyPoint(double x, double y)
{
    posX = x;
    posY = y;
}

double MyPoint::getX() const
{
    return posX;
}

double MyPoint::getY() const
{
    return posY;
}

double MyPoint::distance(const MyPoint& P) const
{
    return sqrt((posX-P.posX)*(posX-P.posX)+ (posY - P.posY) * (posY - P.posY));
}

bool contains(const MyPoint & p, const Circle2D& cir)
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
