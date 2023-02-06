#include <iomanip>
#include <algorithm>
#include <iostream>
#include <vector>
#include "LinkList.h"

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
        result += node->toString();
        node = node->next;
    }

    return result;
}

bool LinkList::containsName(string name)
{
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
    cout << "ran containsName" << endl;
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

struct sort_by_name
{
    inline bool operator()(const Node &node1, const Node &node2)
    {
        return (node1.data->name < node2.data->name);
    }
};

struct sort_by_ba
{
    inline bool operator()(const Node &node1, const Node &node2)
    {
        return (node1.data->getBattingAverage() < node2.data->getBattingAverage());
    }
};

struct sort_by_obp
{
    inline bool operator()(const Node &node1, const Node &node2)
    {
        return (node1.data->getOnBasePercentage() < node2.data->getOnBasePercentage());
    }
};

struct sort_by_hits
{
    inline bool operator()(const Node &node1, const Node &node2)
    {
        return (node1.data->H < node2.data->H);
    }
};

struct sort_by_walks
{
    inline bool operator()(const Node &node1, const Node &node2)
    {
        return (node1.data->W < node2.data->W);
    }
};

struct sort_by_strikeouts
{
    inline bool operator()(const Node &node1, const Node &node2)
    {
        return (node1.data->K < node2.data->K);
    }
};

struct sort_by_hbp
{
    inline bool operator()(const Node &node1, const Node &node2)
    {
        return (node1.data->P < node2.data->P);
    }
};

vector<Node> LinkList::getVector()
{
    Node *node = this->head;
    vector<Node> arr;

    while (node)
    {
        arr.push_back(*node);
        node = node->next;
    }

    return arr;
}


void LinkList::sort(string sortType, bool reverse)
{
    vector<Node> arr = this->getVector();
    for (unsigned long i = 0; i < arr.size(); i ++)
    {
        arr.at((unsigned long)i).next = nullptr;
    }

    if (sortType == "name")
        std::sort(arr.begin(), arr.end(), sort_by_name());
    else if (sortType == "BATTING AVERAGE")
        std::sort(arr.begin(), arr.end(), sort_by_ba());
    else if (sortType == "ON-BASE PERCENTAGE")
        std::sort(arr.begin(), arr.end(), sort_by_obp());
    else if (sortType == "HITS")
        std::sort(arr.begin(), arr.end(), sort_by_hits());
    else if (sortType == "WALKS")
        std::sort(arr.begin(), arr.end(), sort_by_walks());
    else if (sortType == "STRIKEOUTS")
        std::sort(arr.rbegin(), arr.rend(), sort_by_strikeouts());
    else if (sortType == "HIT BY PITCH")
        std::sort(arr.begin(), arr.end(), sort_by_hbp());

    if (reverse)
        std::reverse(arr.begin(), arr.end());

    Node *node = this->head;

    for (unsigned long i = 0; i < arr.size() - 1; i++)
    {
        *node = arr.at((unsigned long)i);
        node->next = new Node();
        node = node->next;
    }

    *node = arr.at(arr.size() - 1);
}

double getLeagueData(Node node, string leaderType)
{
    if (leaderType == "BATTING AVERAGE")
        return node.data->getBattingAverage();
    if (leaderType == "ON-BASE PERCENTAGE")
        return node.data->getOnBasePercentage();
    if (leaderType == "HITS")
        return node.data->H;
    if (leaderType == "WALKS")
        return node.data->W;
    if (leaderType == "STRIKEOUTS")
        return node.data->K;
    if (leaderType == "HIT BY PITCH")
        return node.data->P;

    cout << "INVALID INPUT TO getLeagueDataType()" << endl;
    return 0.0;
}

LeagueLeaderData LinkList::getLeagueLeaderData(string leaderType)
{
    LeagueLeaderData data = {};

    vector<Node> arr = this->getVector();

    data.firstData = getLeagueData(arr.at(0), leaderType);
    data.firstNames.push_back(arr.at(0).data->name);
    data.firstExists = true;

    for (unsigned long i = 1; i < arr.size(); i++)
    {
        Node curr = arr.at((unsigned long)i);
        double currData = getLeagueData(curr, leaderType);
        if (currData == data.firstData)
        {
            data.firstNames.push_back(curr.data->name);
        }
        else if (!data.secondExists || currData == data.secondData)
        {
            if (data.firstNames.size()==3) break;
            data.secondData = currData;
            data.secondNames.push_back(curr.data->name);
            data.secondExists = true;
        }
        else if (!data.thirdExists || currData == data.thirdData)
        {
            if (data.secondNames.size() + data.firstNames.size() >= 3) break;
            data.thirdData = currData;
            data.thirdNames.push_back(curr.data->name);
            data.thirdExists = true;
        }
    }

    // get first place data --> create vector for names/ties
    // check len of vector. if >=3, return
    // if ==2, get second place data --> create vector for names/ties
    // check len of vector. if ==2 return
    // if not get third place data --> return name.

    return data;
}

void LinkList::printLeagueLeaders(string leaderType)
{
    LeagueLeaderData data;
    this->sort(leaderType, true);
    data = this->getLeagueLeaderData(leaderType);
    
    cout << leaderType << endl;
    if (leaderType == "BATTING AVERAGE" || leaderType == "ON-BASE PERCENTAGE")
        cout << std::fixed << std::showpoint << std::setprecision(3) << data.firstData << "\t";
    else
        cout << std::noshowpoint << std::setprecision(0) << data.firstData << "\t";
    
    for (unsigned long i = 0; i < data.firstNames.size(); i++)
    {
        std::sort(data.firstNames.begin(), data.firstNames.end());
        cout << data.firstNames.at((unsigned long)i);
        if (i != data.firstNames.size() - 1)
            cout << ", ";
        else
            cout << endl;
    }
    if (data.secondExists)
    {
        std::sort(data.secondNames.begin(), data.secondNames.end());
        cout << data.secondData << "\t";
        for (unsigned long i = 0; i < data.secondNames.size(); i++)
        {
            cout << data.secondNames.at((unsigned long)i);
            if ((unsigned long)i != data.secondNames.size() - 1)
                cout << ", ";
            else
                cout << endl;
        }
    }
    if (data.thirdExists)
    {
        std::sort(data.thirdNames.begin(), data.thirdNames.end());
        cout << data.thirdData << "\t";
        for (unsigned long i = 0; i < data.thirdNames.size(); i++)
        {
            cout << data.thirdNames.at((unsigned long)i);
            if ((unsigned long)i != data.thirdNames.size() - 1)
                cout << ", ";
            else
                cout << endl;
        }
    }
    cout << endl;
}




  // data.firstData = getLeagueData(arr.at(0), leaderType);
    // data.firstNames.push_back(arr.at(0).data->name);
    // data.firstExists = true;

    // if (arr.size() == 1) return data;

    // // checking if tie with 1/2nd place
    // data.secondData = getLeagueData(arr.at(1), leaderType);
    // if (data.secondData == data.firstData)
    // {
    //     // if 1/2 tie
    //     data.firstNames.push_back(arr.at(1).data->name);

    //     if (arr.size() == 2) return data;

    //     //checking if 3-way tie

    //     data.thirdData = getLeagueData(arr.at(2), leaderType);

    // }

    // other approache
