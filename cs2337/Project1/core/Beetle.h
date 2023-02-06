#ifndef BEETLE_H
#define BEETLE_H
#include "Creature.h"

class Beetle: public Creature {
    public:
        int turns_since_eaten;
        Beetle();
        Beetle(int x, int y);
        void Breed();
        void Move(int direction);
        void Starve();
};

#endif