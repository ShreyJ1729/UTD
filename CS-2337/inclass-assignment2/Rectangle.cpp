// Shrey Joshi & 

#include <cmath>
#include <iostream>
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle(double width, double height)
{
    this->width = width;
    this->height = height;
}

Rectangle::Rectangle()
{
    this->width = 0.0;
    this->height = 0.0;
}

Rectangle::Rectangle(Rectangle &r)
{
    this->width = r.width;
    this->height = r.height;
}

double Rectangle::getWidth()
{
    return this->width;
}

double Rectangle::getHeight()
{
    return this->height;
}

void Rectangle::setWidth(double newWidth)
{
    this->width = newWidth;
}

void Rectangle::setHeight(double newHeight)
{
    this->height = newHeight;
}

Rectangle Rectangle::operator+(const Rectangle &r)
{
    Rectangle rect;
    rect.setWidth(this->width + r.width);
    rect.setHeight(this->height + r.height);
    return rect;
}

Rectangle Rectangle::operator-(const Rectangle &r)
{
    Rectangle rect;
    rect.setWidth(fmax(this->width - r.width, 0));
    rect.setHeight(fmax(this->height + r.height, 0));
    return rect;
}

Rectangle Rectangle::operator++()
{

    this->width++;
    this->height++;
    return *this;
}

Rectangle Rectangle::operator++(int)
{

    Rectangle temp = *this;
    ++*this;
    return temp;
}

bool Rectangle::operator>(const Rectangle &r)
{

    return (this->width * this->height > r.width * r.height);
}

bool Rectangle::operator<(const Rectangle &r){

    return (this->width * this->height < r.width * r.height);

}

ostream &operator<<(ostream &out, const Rectangle &r)
{
    out << "width: " << r.width << " height: " << r.height;
    return out;
}