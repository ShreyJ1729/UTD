#include "Term.h"

Payload::Payload() {}

Payload::Payload(Fraction coefficient, int exponent) {
    this->coefficient = coefficient;
    this->exponent = exponent;
}
