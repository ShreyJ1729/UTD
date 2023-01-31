#include "LinkList.h"

LinkList::LinkList() {
    this->root = nullptr;
}

LinkList::LinkList(Node *root) {
    this->root = root;
}

void LinkList::addNode(Node *toAdd)
{
    if (this->root)
    {
        Node *node = this->root;

        while (node)
        {
            if (node->next == nullptr)
            {
                node->next = toAdd;
                toAdd->next = nullptr;
            }
            node = node->next;
        }
    }
    else
    {
        this->root = toAdd;
    }
}
