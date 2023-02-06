#ifndef LINKLIST_H
#define LINKLIST_H

#include "Node.h"

class LinkList {
    public:
        Node *root;
        LinkList();
        LinkList(Node *toadd);
        void addNode(Node *toadd);
};

#endif