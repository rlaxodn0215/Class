#include "Rectangle2D.h"
#include<cmath>

double Rectangle2D::getX() const
{
    return posX;
}

double Rectangle2D::getY() const
{
    return posY;
}

double Rectangle2D::getWidth() const
{
    return width;
}

double Rectangle2D::getHeight() const
{
    return height;
}

void Rectangle2D::setXY(double x, double y)
{
    posX = x;
    posY = y;
}

void Rectangle2D::set_Width_Height(double w, double h)
{
    width = w;
    height = h;
}

Rectangle2D::Rectangle2D()
{
    posX = 0;
    posY = 0;
    width = 1;
    height = 1;
}

Rectangle2D::Rectangle2D(double x, double y, double w, double h)
{
    posX = x;
    posY = y;
    width = w;
    height = h;
}

double Rectangle2D::getArea() const
{
    return (width*height);
}

double Rectangle2D::getPerimeter() const
{
    return 2*(width+height);
}

bool Rectangle2D::contains(double x, double y)
{
    if ((x >= posX - width / 2 && x <= posX + width / 2) && (y >= posY - height / 2 && y <= posY + height / 2))
    {
        return true;
    }

    else
    {
        return false;
    }

}

bool Rectangle2D::contains(const Rectangle2D& r)
{

    if ((r.width - width) / 2 >= abs(r.posX - posX) && (r.height - height) / 2 >= abs(r.posY - posY))
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool Rectangle2D::overlaps(const Rectangle2D& r)
{
    if ((r.width + width) / 2 >= abs(r.posX - posX) && (r.height + height) / 2 >= abs(r.posY - posY))
    {
        return true;
    }

    else
    {
        return false;
    }
}
