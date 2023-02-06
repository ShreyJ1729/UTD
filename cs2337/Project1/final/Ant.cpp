#include "Ant.h"

Ant::Ant() {
    this->species = "ant";
    this->hasMoved = false;
    this->hasBreeded = true;
}

Ant::Ant(int row, int col) {
    this->species = "ant";
    this->row = row;
    this->col = col;
    this->hasMoved = false;
    this->hasBreeded = true;
}

void Ant::Move(string direction) {
    if (direction=="north") this->row --;
    if (direction=="east") this->col ++;
    if (direction=="south") this->row ++;
    if (direction=="west") this->col --;
    this->hasMoved = true;
}

void Ant::Breed() {
    this->hasBreeded = true;
}
