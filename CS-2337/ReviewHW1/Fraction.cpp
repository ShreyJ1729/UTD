#include "Fraction.h"

Fraction::Fraction()
{
}

Fraction::Fraction(int num)
{
    this->num = num;
}

Fraction::Fraction(int num, int denom)
{
    this->num = num;
    this->denom = denom;
}

Fraction Fraction::operator+(const Fraction &f)
{
    int newDenom = this->denom * f.denom;
    int newNum = this->num * f.denom + f.num * this->denom;
    Fraction total = Fraction(newNum, newDenom);
    total.simplify();
    return total;
}

Fraction Fraction::operator-(const Fraction &f)
{
    int newDenom = this->denom * f.denom;
    int newNum = this->num * f.denom - f.num * this->denom;
    Fraction total = Fraction(newNum, newDenom);
    total.simplify();
    return total;
}

Fraction Fraction::operator*(const Fraction &f)
{
    int newDenom = this->denom * f.denom;
    int newNum = this->num * f.num;
    Fraction total = Fraction(newNum, newDenom);
    total.simplify();
    return total;
}

Fraction Fraction::operator/(const Fraction &f)
{
    // a/b / c/d = a/b * d/c = ad/bc
    int newNum = this->num * f.denom;
    int newDenom = this->denom * f.num;
    Fraction total = Fraction(newNum, newDenom);
    total.simplify();
    return total;
}

int Fraction::getNumerator() { return this->num; }
int Fraction::getDenominator() { return this->denom; }
void Fraction::setNumerator(int num) { this->num = num; }
void Fraction::setDenominator(int denom) { this->denom = denom; }

bool Fraction::operator>(const Fraction &f)
{
    // a/b vs c/d --> ad/bd vs cb/bd
    int commonDenom = this->denom * f.denom;
    int thisNum = this->num * f.denom;
    int fNum = f.num * this->denom;
    return (thisNum>fNum);
}

bool Fraction::operator<(const Fraction &f)
{
    int commonDenom = this->denom * f.denom;
    int thisNum = this->num * f.denom;
    int fNum = f.num * this->denom;
    return (thisNum<fNum);
}

bool Fraction::operator==(const Fraction &f)
{
    int commonDenom = this->denom * f.denom;
    int thisNum = this->num * f.denom;
    int fNum = f.num * this->denom;
    return (thisNum==fNum);
}

ostream &operator<<(ostream &output, Fraction &f)
{
    output << f.num << " / " << f.denom;
    return output;
}

istream &operator>>(istream &input, Fraction &f)
{
    int num;
    int denom;
    cout << "numerator: ";
    input >> num;
    cout << "denominator: ";
    input >> denom;
    f.setNumerator(num);
    f.setDenominator(denom);
    return input;
}

void Fraction::simplify()
{
    if (this->num == 0)
    {
        this->denom = 1;
    }
    else
    {

        int gcf = 1;
        for (int factor = 1; factor <= min(this->num, this->denom); factor++)
        {
            if (this->num % factor == 0 && this->denom % factor == 0)
            {
                gcf = factor;
            }
        }

        this->num /= gcf;
        this->denom /= gcf;
    }
}