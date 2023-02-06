#ifndef CREATURE_H
#define CREATURE_H
#include <string>
class Creature {
    public:
        std::string species;
        int x;
        int y;
        virtual void Move(int direction) = 0;
        virtual void Breed() = 0;
};

#endif