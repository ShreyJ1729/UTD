#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
using namespace std;

class Fraction
{
public:
    int num;
    int denom;

    Fraction();
    Fraction(int num);
    Fraction(int num, int denom);

    Fraction operator+(const Fraction &b);
    Fraction operator-(const Fraction &b);
    Fraction operator*(const Fraction &b);
    Fraction operator/(const Fraction &b);

    bool operator>(const Fraction &b);
    bool operator<(const Fraction &b);
    bool operator==(const Fraction &b);

    friend ostream &operator<<(ostream &output, Fraction &f);
    friend istream &operator>>(istream &input, Fraction &f);

    int getNumerator();
    int getDenominator();
    void setNumerator(int num);
    void setDenominator(int denom);

    void simplify();
};

#endif