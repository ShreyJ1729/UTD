#ifndef ANT_H
#define ANT_H
#include "Creature.h"

using namespace std;

class Ant : public Creature
{
public:
    Ant();
    Ant(int row, int col);
    void Move(string direction);
    void Breed();
};

#endif
