#ifndef NODE_H
#define NODE_H

#include <string>
#include "Player.h"

using namespace std;

class Node
{
public:
    Node *next;
    Player *data;

    Node();
    Node(Player *data);
    Node(Player *data, Node *next);

    string toString();
};

#endif
