#ifndef LIST_H
#define LIST_H

#include <string>
#include "Node.h"
#include "Player.h"

using namespace std;

class LinkList
{
public:
    Node *head;

    LinkList();
    LinkList(Node *head);

    string toString() const;
    bool containsName(string name);
    Node *getNodeByName(string name);
    void addNode(Node *node);
};

#endif
