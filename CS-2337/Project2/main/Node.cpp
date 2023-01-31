#include "Node.h"
#include "Player.h"

Node::Node()
{
    this->data = nullptr;
    this->next = nullptr;
}

Node::Node(Player *data)
{
    this->data = data;
    this->next = nullptr;
}

Node::Node(Player *data, Node *next)
{
    this->data = data;
    this->next = next;
}

string Node::toString()
{
    string result = this->data->name + "\t" + to_string(this->data->getAtBats()) + "\t" + to_string(this->data->H) + "\t" + to_string(this->data->W) + "\t" + to_string(this->data->K) + "\t" + to_string(this->data->P) + "\t" + to_string(this->data->S) + "\t" + to_string(this->data->getBattingAverage()).substr(0, 5) + "\t" + to_string(this->data->getOnBasePercentage()).substr(0, 5) + "\n";

    return result;
}

bool Node::operator<(const Node &node) const
{
    return (this->data->name < node.data->name);
}


// Player name
// o At-bats
// o Hits
// o Walks
// o Strikeouts
// o Hits by pitch
// o Sacrifices
// o Batting average
// o On-base percentage
// o Write a newline after the on-base percentage (there is no tab before the newline)
