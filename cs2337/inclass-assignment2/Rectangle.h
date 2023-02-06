#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <iostream>
using namespace std;

class Rectangle
{
public:
    double width;
    double height;

    Rectangle();
    Rectangle(double width, double height);
    Rectangle(Rectangle &r);

    double getWidth();
    double getHeight();
    void setWidth(double width);
    void setHeight(double height);

    Rectangle operator+(const Rectangle &r);
    Rectangle operator-(const Rectangle &r);
    Rectangle operator++();
    Rectangle operator++(int);

    bool operator>(const Rectangle &r);
    bool operator<(const Rectangle &r);

    friend ostream &operator<<(ostream &out, const Rectangle &r);
};

#endif