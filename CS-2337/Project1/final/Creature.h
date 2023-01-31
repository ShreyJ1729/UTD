#ifndef CREATURE_H
#define CREATURE_H
#include <string>

using namespace std;

class Creature {
    public:
        std::string species;
        int col;
        int row;
        int turnsSinceBreeded;
        bool hasMoved;
        bool hasBreeded;
        virtual void Move(string direction) = 0;
        virtual void Breed() = 0;
};

#endif
