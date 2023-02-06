#include "Ant.h"


Ant::Ant() {
    this->species = "ant";
}

Ant::Ant(int x, int y) {
    this->species = "ant";
    this->x = x;
    this->y = y;
}

void Ant::Move(int direction) {
    if (direction == 0) this->x+=1;
    else if (direction == 1) this->x-=1;
    else if (direction == 2) this->y-=1;
    else if (direction == 3) this->y+=1;
}

void Ant::Breed() {
}