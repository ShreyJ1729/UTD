#include <iostream>
#include "Fraction.h"

int main() {
    Fraction frac1 = Fraction(4, 7);
    Fraction frac2 = Fraction(8, 17);

    cin >> frac2;

    Fraction sum = frac1+frac2;
    Fraction diff = frac1-frac2;
    Fraction multiply = frac1 * frac2;
    Fraction divide = frac1 / frac2;

    cout << sum << endl;
    cout << diff << endl;
    cout << multiply << endl;
    cout << divide << endl;
    cout << (frac1>frac2) << endl;
    cout << (frac1<frac2) << endl;
    cout << (frac1==frac2) << endl;
}