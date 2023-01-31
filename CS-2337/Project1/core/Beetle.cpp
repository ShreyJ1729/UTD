#include "Beetle.h"

Beetle::Beetle() {
    this->species = "beetle";
}

Beetle::Beetle(int x, int y) {
    this->species = "beetle";
    this->x = x;
    this->y = y;
}

void Beetle::Move(int direction) {
    if (direction == 0) this->x+=1;
    else if (direction == 1) this->x-=1;
    else if (direction == 2) this->y-=1;
    else if (direction == 3) this->y+=1;
}

void Beetle::Breed() {
    int b = 1;
}

void Beetle::Starve() {
    int c = 1;
}