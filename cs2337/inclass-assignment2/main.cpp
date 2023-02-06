// Name: Shrey Joshu & Rebeca Itzel Rios Rios
// ID: SXJ210081 & RXR200072

#include <iostream>
#include <fstream>
#include "Rectangle.h"
using namespace std;

int main()
{
    double height;
    double width;

    // object created by the overloaded constructor
    Rectangle rectOne(10.0, 5.0);

    // object is created by the copy contructor
    Rectangle rectCopy(4.0, 11.0);
    Rectangle rectTwo = rectCopy;

    // change height and width using mutator
    rectOne.setHeight(height);
    rectOne.setWidth(width);

    // print out
    cout << rectOne + rectTwo << endl;
    cout << rectOne - rectTwo << endl;
    cout << ++rectOne << endl;
    cout << rectOne++ << endl;
    cout << (rectOne < rectTwo) << endl;
    cout << (rectOne > rectTwo) << endl;
    cout << (rectOne.getWidth() * rectOne.getHeight()) << endl;
    cout << (rectTwo.getWidth() * rectTwo.getHeight()) << endl;
}