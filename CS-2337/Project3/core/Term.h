#ifndef TERM_H
#define TERM_H

struct Fraction
{
public:
    int num;
    int denum;
    Fraction(){};
    Fraction(int num)
    {
        this->num = num;
        this->denum = 1;
    }
    Fraction(int num, int denum)
    {
        this->num = num;
        this->denum = denum;
    }
};

class Payload
{
public:
    Fraction coefficient;
    int exponent;

    Payload();
    Payload(Fraction coefficient, int exponent);
};

#endif
