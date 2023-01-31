#ifndef NODE_H
#define NODE_H
#include "Term.h"
#include <iostream>

class Node
{
public:
    Payload data;
    Node *left;
    Node *right;

    Node()
    {
        this->left = nullptr;
        this->right = nullptr;
    }
    Node(Payload payload)
    {
        this->data = payload;
        this->left = nullptr;
        this->right = nullptr;
    }
};

#endif
