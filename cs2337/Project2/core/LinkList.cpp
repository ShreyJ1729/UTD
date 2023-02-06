#include <iostream>
#include "LinkList.h"
#include "Node.h"

using namespace std;

LinkList::LinkList()
{
    this->head = nullptr;
}

LinkList::LinkList(Node *head)
{
    this->head = head;
}

string LinkList::toString() const
{
    string result = "";

    Node *node = this->head;

    while (node)
    {
        result += node->toString() + "\n";
        node = node->next;
    }

    return result;
}

bool LinkList::containsName(string name)
{
    cout << "running containsName"<<endl;
    Node *node = this->head;

    while (node)
    {
        if (node->data->name == name)
        {
            return true;
        }

        node = node->next;
    }

    return false;
    cout << "ran containsName"<<endl;
}

Node *LinkList::getNodeByName(string name)
{
    Node *node = this->head;

    while (node)
    {
        if (node->data->name == name)
        {
            return node;
        }
        node = node->next;
    }

    return nullptr;
}

void LinkList::addNode(Node *toAdd)
{
    if (this->head)
    {
        Node *node = this->head;

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
        this->head = toAdd;
    }
}
