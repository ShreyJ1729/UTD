#ifndef LIST_H
#define LIST_H

#include <string>
#include "Node.h"
#include "Player.h"
#include "vector"

using namespace std;

struct LeagueLeaderData
{
    bool firstExists;
    bool secondExists;
    bool thirdExists;
    double firstData;
    vector<string> firstNames;
    double secondData;
    vector<string> secondNames;
    double thirdData;
    vector<string> thirdNames;
};

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
    void sort(string sortType, bool reverse);
    void printLeagueLeaders(string leaderType);
    LeagueLeaderData getLeagueLeaderData(string leaderType);
    vector<Node> getVector();
    vector<Node> getVectorReadOnly();
};

#endif
