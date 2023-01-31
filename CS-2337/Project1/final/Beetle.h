#ifndef BEETLE_H
#define BEETLE_H
#include "Creature.h"

class Beetle : public Creature {
    public:
        Beetle();
        Beetle(int row, int col);
        void Starve();
        void Move(string direction);
        void Breed();
};

#endif
