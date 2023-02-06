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
    struct sort_by_name;

    Node();
    Node(Player *data);
    Node(Player *data, Node *next);
    bool operator<(const Node &node) const;

    string toString();
};

#endif
