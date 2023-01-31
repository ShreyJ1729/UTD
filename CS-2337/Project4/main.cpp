#include "Player.h"
#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void printPlayersInOrder(set<string> toPrint)
{
    int count = toPrint.size();
    for (auto itr = toPrint.begin(); itr != toPrint.end(); itr++)
    {
        string player = *itr;
        string team = player.substr(0, 1);
        string name = player.substr(1);
        if (team == "A")
        {
            cout << name;
            // toPrint.erase(player);
            count--;
            if (count>0) cout << ", ";
        }
    }

    for (auto itr = toPrint.begin(); itr != toPrint.end(); itr++)
    {
        string player = *itr;
        string team = player.substr(0, 1);
        string name = player.substr(1);
        if (team == "H")
        {
            cout << name;
            // toPrint.erase(player);
            count--;
            if (count>0) cout << ", ";
        }
    }
    cout << endl;
}

void printBattingAverageLeaders(map<string, Player> playerMap)
{
    map<double, vector<Player> > newMap;

    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (newMap.find(player.getBattingAverage()) == newMap.end())
        {
            newMap[player.getBattingAverage()] = vector<Player>();
        }
        newMap[player.getBattingAverage()].push_back(player);
    }

    int numPeople = 0;
    for (auto iter = newMap.rbegin(); iter != newMap.rend(); ++iter)
    {
        vector<Player> players = iter->second;
        set<string> toPrint;
        numPeople += players.size();
        cout << iter->first << "\t";
        for (int i = 0; i < players.size(); i++)
        {
            Player player = players.at(i);
            toPrint.insert(player.team + player.name);
        }
        printPlayersInOrder(toPrint);
        if (numPeople >= 3)
            break;
    }
}

void printOnBasePercentageLeaders(map<string, Player> playerMap)
{
    map<double, vector<Player> > newMap;

    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (newMap.find(player.getOnBasePercentage()) == newMap.end())
        {
            newMap[player.getOnBasePercentage()] = vector<Player>();
        }
        newMap[player.getOnBasePercentage()].push_back(player);
    }

    int numPeople = 0;
    for (auto iter = newMap.rbegin(); iter != newMap.rend(); ++iter)
    {
        vector<Player> players = iter->second;
        set<string> toPrint;
        numPeople += players.size();
        cout << iter->first << "\t";
        for (int i = 0; i < players.size(); i++)
        {
            Player player = players.at(i);
            toPrint.insert(player.team + player.name);
        }
        printPlayersInOrder(toPrint);
        if (numPeople >= 3)
            break;
    }
}

void printHitsLeaders(map<string, Player> playerMap)
{
    map<int, vector<Player> > newMap;

    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (newMap.find(player.H) == newMap.end())
        {
            newMap[player.H] = vector<Player>();
        }
        newMap[player.H].push_back(player);
    }

    int numPeople = 0;
    for (auto iter = newMap.rbegin(); iter != newMap.rend(); ++iter)
    {
        vector<Player> players = iter->second;
        set<string> toPrint;
        numPeople += players.size();
        cout << iter->first << "\t";
        for (int i = 0; i < players.size(); i++)
        {
            Player player = players.at(i);
            toPrint.insert(player.team + player.name);
        }
        printPlayersInOrder(toPrint);
        if (numPeople >= 3)
            break;
    }
}

void printWalksLeaders(map<string, Player> playerMap)
{
    map<int, vector<Player> > newMap;

    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (newMap.find(player.W) == newMap.end())
        {
            newMap[player.W] = vector<Player>();
        }
        newMap[player.W].push_back(player);
    }

    int numPeople = 0;
    for (auto iter = newMap.rbegin(); iter != newMap.rend(); ++iter)
    {
        vector<Player> players = iter->second;
        set<string> toPrint;
        numPeople += players.size();
        cout << iter->first << "\t";
        for (int i = 0; i < players.size(); i++)
        {
            Player player = players.at(i);
            toPrint.insert(player.team + player.name);
        }
        printPlayersInOrder(toPrint);
        if (numPeople >= 3)
            break;
    }
}

void printStrikeoutsLeaders(map<string, Player> playerMap)
{
    map<int, vector<Player> > newMap;

    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (newMap.find(player.K) == newMap.end())
        {
            newMap[player.K] = vector<Player>();
        }
        newMap[player.K].push_back(player);
    }

    int numPeople = 0;
    for (auto iter = newMap.begin(); iter != newMap.end(); ++iter)
    {
        vector<Player> players = iter->second;
        set<string> toPrint;
        numPeople += players.size();
        cout << iter->first << "\t";
        for (int i = 0; i < players.size(); i++)
        {
            Player player = players.at(i);
            toPrint.insert(player.team + player.name);
        }
        printPlayersInOrder(toPrint);
        if (numPeople >= 3)
            break;
    }
}
void printHitByPitchesLeaders(map<string, Player> playerMap)
{
    map<int, vector<Player> > newMap;

    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (newMap.find(player.P) == newMap.end())
        {
            newMap[player.P] = vector<Player>();
        }
        newMap[player.P].push_back(player);
    }

    int numPeople = 0;
    for (auto iter = newMap.rbegin(); iter != newMap.rend(); ++iter)
    {
        vector<Player> players = iter->second;
        set<string> toPrint;
        numPeople += players.size();
        cout << iter->first << "\t";
        for (int i = 0; i < players.size(); i++)
        {
            Player player = players.at(i);
            toPrint.insert(player.team + player.name);
        }
        printPlayersInOrder(toPrint);
        if (numPeople >= 3)
            break;
    }
}

int main()
{
    string keyfilename = "keyfile.txt";

    ifstream keyFile;

    map<string, string> hashmap;
    keyFile.open(keyfilename);
    string line;
    string currCategory = "";
    while (!keyFile.eof())
    {
        getline(keyFile, line);
        if (line != "")
        {
            if (line.at(0) == '#')
            {
                // cout << line << endl;
                line = line.substr(3, line.length() - 6);
                // cout << "-" << line << "-" << endl;
                currCategory = line;
            }
            else
            {
                hashmap[line] = currCategory;
                // cout << "adding (" << line << ") to " << currCategory << endl;
            }
        }
    }
    keyFile.close();

    string pbpfilename;
    cin >> pbpfilename;
    ifstream pbpFile;
    pbpFile.open(pbpfilename);

    map<string, Player> playerMap;
    int i = 0;
    while (!pbpFile.eof())
    {
        string team = "A";
        string name = "B";
        string action;
        pbpFile >> team;
        pbpFile >> name;
        pbpFile >> action;
        action = hashmap[action];

        Player player(name, team);
        if (playerMap.find(name) != playerMap.end())
        {
            player = playerMap.at(name);
        }

        if (action == "OUTS")
            player.O++;
        else if (action == "STRIKEOUT")
            player.K++;
        else if (action == "HITS")
            player.H++;
        else if (action == "WALK")
            player.W++;
        else if (action == "SACRIFICE")
            player.S++;
        else if (action == "HIT BY PITCH")
            player.P++;
        else if (action == "ERRORS")
            player.E++;

        // player.toString();
        playerMap[name] = player;
    }

    cout << "AWAY" << endl;
    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (player.team == "A")
        {
            player.toString();
        }
    }

    cout << endl;

    cout << "HOME" << endl;
    for (pair<string, Player> element : playerMap)
    {
        Player player = element.second;
        if (player.team == "H")
        {
            player.toString();
        }
    }

    cout << endl;

    cout << "LEAGUE LEADERS" << endl;
    cout << "BATTING AVERAGE" << endl;
    printBattingAverageLeaders(playerMap);
    cout << endl;
    cout << "ON-BASE PERCENTAGE" << endl;
    printOnBasePercentageLeaders(playerMap);
    cout << endl;
    cout << "HITS" << endl;
    printHitsLeaders(playerMap);
    cout << endl;
    cout << "WALKS" << endl;
    printWalksLeaders(playerMap);
    cout << endl;
    cout << "STRIKEOUTS" << endl;
    printStrikeoutsLeaders(playerMap);
    cout << endl;
    cout << "HIT BY PITCH" << endl;
    printHitByPitchesLeaders(playerMap);
}
