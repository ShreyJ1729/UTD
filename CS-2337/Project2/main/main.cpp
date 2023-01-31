#include <string>
#include <fstream>
#include <iostream>
#include "LinkList.h"
#include "Node.h"
#include "Player.h"

using namespace std;

Player *getPlayerFromRecord(string name, string record)
{
    int h = 0;
    int o = 0;
    int k = 0;
    int w = 0;
    int p = 0;
    int s = 0;

    for (unsigned long j = 0; j < record.length(); j++)
    {
        char letter = record.at((unsigned long)j);
        if (letter == 'H')
            h++;
        if (letter == 'O')
            o++;
        if (letter == 'K')
            k++;
        if (letter == 'W')
            w++;
        if (letter == 'P')
            p++;
        if (letter == 'S')
            s++;
    }

    Player *player = new Player(name, h, o, k, w, p, s);
    return player;
}

void addStatsToNode(Player *curr, Node *node)
{
    node->data->H += curr->H;
    node->data->O += curr->O;
    node->data->K += curr->K;
    node->data->W += curr->W;
    node->data->P += curr->P;
    node->data->S += curr->S;
}

int main()
{
    string infileName;
    ifstream inFile;
    LinkList list = LinkList();

    cin >> infileName;
    inFile.open(infileName);

    while (inFile.is_open() && !inFile.eof())
    {
        string name;
        string record;
        inFile >> name;
        inFile >> record;
        Player *curr = getPlayerFromRecord(name, record);
        if (list.containsName(name))
        {
            // if name already in linklist, add to that
            Node *node = list.getNodeByName(name);
            addStatsToNode(curr, node);
        }
        else
        {
            // else append new object
            list.addNode(new Node(curr));
        }
    }

    inFile.close();

    // sort list by alphabetical and output
    // list.sort("name");
    // cout << list.toString();
    list.sort("name", false);
    cout << list.toString() << endl;

    cout << "LEAGUE LEADERS" << endl;
    list.printLeagueLeaders("BATTING AVERAGE");
    list.printLeagueLeaders("ON-BASE PERCENTAGE");
    list.printLeagueLeaders("HITS");
    list.printLeagueLeaders("WALKS");
    list.printLeagueLeaders("STRIKEOUTS");
    list.printLeagueLeaders("HIT BY PITCH");

    // sort linklist by each stat using the sort function and print league leaders based on output format

}

// main function
// {
//     - prompt input filename and take input
//     - take input from file, check if name in linkedlist
//     - - if it is add to that object
//     - - if not append new object
//     - recursively sort linkedlist by alphabetical order name (merge sort)
//     - print each linkedlist object in order
//     - sort linkedlist by each stat with merge sort --> create one function where you enter parameter to sort by
//     - then print league leader based on output format
// }
