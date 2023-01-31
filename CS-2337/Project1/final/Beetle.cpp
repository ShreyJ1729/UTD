#include "Beetle.h"

Beetle::Beetle() {
    this->species = "beetle";
    this->hasMoved = false;
    this->hasBreeded = true;
    this->turnsSinceBreeded = 0;
}

Beetle::Beetle(int row, int col) {
    this->species = "beetle";
    this->row = row;
    this->col = col;
    this->hasMoved = false;
    this->hasBreeded = true;
    this->turnsSinceBreeded = 0;
}

void Beetle::Move(string direction) {
    if (direction=="north") this->row --;
    if (direction=="east") this->col ++;
    if (direction=="south") this->row ++;
    if (direction=="west") this->col --;
    this->hasMoved = true;
}

void Beetle::Starve()
{
    
}

void Beetle::Breed() {
    this->hasBreeded = true;
    this->turnsSinceBreeded = 0;
}
