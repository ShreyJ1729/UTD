#ifndef ANT_H
#define ANT_H
#include "Creature.h"

class Ant : public Creature {
    public:
        Ant();
        Ant(int x, int y);
        void Move(int direction);
        void Breed();
};

#endif