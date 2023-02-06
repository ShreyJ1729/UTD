#include <iostream>
#include <string>
#include <fstream>
#include <numeric>
#include "Creature.h"
#include "Ant.h"
#include "Beetle.h"

using namespace std;

/*
________________________________________________________________________________________________________
                                    GENERAL HELPER FUNCTIONS
________________________________________________________________________________________________________
*/

// returns true/false if the grid cell is empty, contains an ant, or contains a beetle
bool inBounds(int row, int col) { return (row > -1 && row < 10 && col > -1 && col < 10); }
bool isEmpty(Creature *c) { return !c; }
bool isAnt(Creature *c) { return !isEmpty(c) && c->species == "ant"; }
bool isBeetle(Creature *c) { return !isEmpty(c) && c->species == "beetle"; }

// read in data from input file to populate the grid
void readInFile(string fileName, Creature *grid[10][10])
{
    ifstream inFile;
    inFile.open(fileName);
    string line;
    for (int row = 0; row < 10; row++)
    {
        getline(inFile, line);

        for (int col = 0; col < 10; col++)
        {
            char c = line.at(col);
            if (c == 'a')
                grid[row][col] = new Ant(row, col);
            else if (c == 'B')
                grid[row][col] = new Beetle(row, col);
            else
                grid[row][col] = nullptr;
        }
    }
    inFile.close();
}

// print grid with given ant and beetle chars
void printGrid(Creature *grid[10][10], char antChar, char beetleChar)
{
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            if (isEmpty(grid[row][col]))
                cout << " ";
            else if (isAnt(grid[row][col]))
                cout << antChar;
            else
                cout << beetleChar;
        }
        cout << endl;
    }
}

void populateDistances(int distances[4], Creature *targets[4], Creature *source)
{
    distances[0] = !isEmpty(targets[0]) ? source->row - targets[0]->row : 10; // N
    distances[1] = !isEmpty(targets[1]) ? targets[1]->col - source->col : 10; // E
    distances[2] = !isEmpty(targets[2]) ? targets[2]->row - source->row : 10; // S
    distances[3] = !isEmpty(targets[3]) ? source->col - targets[3]->col : 10; // W
}

/*
________________________________________________________________________________________________________
                                    MOVE BEETLES FUNCTIONS
________________________________________________________________________________________________________
*/

// get closest ant north to the passed in beetle
Creature *getClosestNorthAnt(Creature *grid[10][10], Creature *b)
{
    for (int row = b->row; row > -1; row--)
    {
        if (isAnt(grid[row][b->col]))
            return grid[row][b->col];
    }
    return nullptr;
}

Creature *getClosestEastAnt(Creature *grid[10][10], Creature *b)
{
    for (int col = b->col; col < 10; col++)
    {
        if (isAnt(grid[b->row][col]))
            return grid[b->row][col];
    }
    return nullptr;
}

Creature *getClosestSouthAnt(Creature *grid[10][10], Creature *b)
{
    for (int row = b->row; row < 10; row++)
    {
        if (isAnt(grid[row][b->col]))
            return grid[row][b->col];
    }
    return nullptr;
}

Creature *getClosestWestAnt(Creature *grid[10][10], Creature *b)
{
    for (int col = b->col; col > -1; col--)
    {
        if (isAnt(grid[b->row][col]))
            return grid[b->row][col];
    }
    return nullptr;
}

void populateClosestOrthAnts(Creature *ants[4], Creature *grid[10][10], Creature *beetle)
{
    // ants array is {N, E, S, W}
    ants[0] = getClosestNorthAnt(grid, beetle);
    ants[1] = getClosestEastAnt(grid, beetle);
    ants[2] = getClosestSouthAnt(grid, beetle);
    ants[3] = getClosestWestAnt(grid, beetle);
}

string getFarthestEdge(Creature *beetle)
{
    int northDist = beetle->row;
    int eastDist = 9 - beetle->col;
    int southDist = 9 - beetle->row;
    int westDist = beetle->col;

    if (max(northDist, max(southDist, max(eastDist, westDist))) == northDist)
        return "north";
    else if (max(northDist, max(southDist, max(eastDist, westDist))) == eastDist)
        return "east";
    else if (max(northDist, max(southDist, max(eastDist, westDist))) == southDist)
        return "south";
    else /*if (max(northDist, max(southDist, max(eastDist, westDist))) == westDist)*/
        return "west";
}

// get number of adjacent ants (orth or diagonal)
int getAntNeighbors(Creature *grid[10][10], Creature *ant)
{
    // if ant is nullpointer (ant in that direction does not exist) return -1
    if (!ant)
        return -1;

    int row = ant->row;
    int col = ant->col;
    int count = 0;
    if (inBounds(row - 1, col) && isAnt(grid[row - 1][col]))
        count++; // N
    if (inBounds(row, col + 1) && isAnt(grid[row][col + 1]))
        count++; // E
    if (inBounds(row + 1, col) && isAnt(grid[row + 1][col]))
        count++; // S
    if (inBounds(row, col - 1) && isAnt(grid[row][col - 1]))
        count++; // W

    if (inBounds(row - 1, col + 1) && isAnt(grid[row - 1][col + 1]))
        count++; // NE
    if (inBounds(row + 1, col + 1) && isAnt(grid[row + 1][col + 1]))
        count++; // SE
    if (inBounds(row + 1, col - 1) && isAnt(grid[row + 1][col - 1]))
        count++; // SW
    if (inBounds(row - 1, col - 1) && isAnt(grid[row - 1][col - 1]))
        count++; // NW

    return count;
}

string getSideGivenTiedAntDistance(Creature *grid[10][10], Creature *ants[4])
{
    string side;
    // move based on most ant neighbors
    int antNeighbors[4] = {getAntNeighbors(grid, ants[0]), getAntNeighbors(grid, ants[1]), getAntNeighbors(grid, ants[2]), getAntNeighbors(grid, ants[3])};

    // count ties for ant neighbors, if none, use it, else use priority N E S W
    int maxNeighbors = max(antNeighbors[0], max(antNeighbors[1], max(antNeighbors[2], antNeighbors[3])));
    bool nTies[4] = {false, false, false, false};
    int numNTies = 0;
    // cout << "neigh: " << antNeighbors[0] << " " << antNeighbors[1] << " " << antNeighbors[2] << " " << antNeighbors[3] << endl;
    for (int i = 0; i < 4; i++)
        if (antNeighbors[i] == maxNeighbors)
        {
            numNTies++;
            nTies[i] = true;
        }

    if (numNTies == 1)
    {
        if (nTies[0])
            side = "north";
        else if (nTies[1])
            side = "east";
        else if (nTies[2])
            side = "south";
        else if (nTies[3])
            side = "west";
        // else
            // throw invalid_argument("numNTies is 1 but nTies has no true element");
    }
    else if (numNTies > 1)
    {
        // number of neighbors also tied so use N E S W priority
        if (ants[0])
            side = "north";
        else if (ants[1])
            side = "east";
        else if (ants[2])
            side = "south";
        else if (ants[3])
            side = "west";
    }
    // else
        // throw invalid_argument("numNTies < 1 which should not be possible");

    return side;
}

string getBeetleMoveSide(Creature *grid[10][10], int row, int col)
{
    Creature *beetle = grid[row][col];

    // search each direction for nearest ant --> create static array size 4 of ants
    Creature *ants[4];
    populateClosestOrthAnts(ants, grid, beetle);

    // create array of distances for N E S W nearest ant --> if no ant found distance defaults to 10
    int distances[4];
    populateDistances(distances, ants, beetle);
    int sum = distances[0] + distances[1] + distances[2] + distances[3];
    // cout << "distances: " << distances[0] << " " << distances[1] << " " << distances[2] << " " << distances[3] << endl;

    // move according to farthest edge if no orth ants
    if (sum == 40)
        return getFarthestEdge(beetle);

    // get min distance and check for number of ties
    int minDist = min(distances[0], min(distances[1], min(distances[2], distances[3])));
    bool ties[4] = {false, false, false, false};
    int numTies = 0;
    for (int i = 0; i < 4; i++)
        if (distances[i] == minDist)
        {
            numTies++;
            ties[i] = true;
        }

    if (numTies == 1) // only one closest ant
    {
        // cout << "one ant"<<endl;
        // move Beetle to closest ant
        if (ties[0])
            return "north";
        else if (ties[1])
            return "east";
        else if (ties[2])
            return "south";
        else if (ties[3])
            return "west";
        // else
            // throw invalid_argument("all elements in ties are nullptr");
    }
    else if (numTies > 1)
    {
        // cout << "ant distance tied" << endl;
        // orth ants are tied for distance, delete ants that are not tied and reprioritize
        for (int i = 0; i < 4; i++)
            if (distances[i] != minDist)
            {
                ants[i] = nullptr;
            }
        return getSideGivenTiedAntDistance(grid, ants);
    }
    // else
        // throw invalid_argument("numTies < 1, which should never happen");
}

void moveBeetle(Creature *grid[10][10], int row, int col)
{
    // cout << "running move beetle" << endl;

    string side = getBeetleMoveSide(grid, row, col);
    // cout << side << endl;
    if (side == "north" && !isBeetle(grid[row - 1][col]))
    {
        grid[row][col]->Move("north");
        grid[row - 1][col] = grid[row][col];
        grid[row][col] = nullptr;
    }
    else if (side == "east" && !isBeetle(grid[row][col + 1]))
    {
        grid[row][col]->Move("east");
        grid[row][col + 1] = grid[row][col];
        grid[row][col] = nullptr;
    }
    else if (side == "south" && !isBeetle(grid[row + 1][col]))
    {
        grid[row][col]->Move("south");
        grid[row + 1][col] = grid[row][col];
        grid[row][col] = nullptr;
    }
    else if (side == "west" && !isBeetle(grid[row][col - 1]))
    {
        grid[row][col]->Move("west");
        grid[row][col - 1] = grid[row][col];
        grid[row][col] = nullptr;
    }
}

void setBeetleHasMovedFalse(Creature *grid[10][10])
{
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isBeetle(grid[row][col]))
                grid[row][col]->hasMoved = false;
        }
    }
}

void moveBeetles(Creature *grid[10][10])
{
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isBeetle(grid[row][col]) && !grid[row][col]->hasMoved)
                moveBeetle(grid, row, col);
        }
    }

    setBeetleHasMovedFalse(grid);
}

/*
________________________________________________________________________________________________________
                                    MOVE ANTS FUNCTIONS
________________________________________________________________________________________________________
*/

// get closest beetle north to the passed in beetle
Creature *getClosestNorthBeetle(Creature *grid[10][10], Creature *b)
{
    for (int row = b->row; row > -1; row--)
    {
        if (isBeetle(grid[row][b->col]))
            return grid[row][b->col];
    }
    return nullptr;
}

Creature *getClosestEastBeetle(Creature *grid[10][10], Creature *b)
{
    for (int col = b->col; col < 10; col++)
    {
        if (isBeetle(grid[b->row][col]))
            return grid[b->row][col];
    }
    return nullptr;
}

Creature *getClosestSouthBeetle(Creature *grid[10][10], Creature *b)
{
    for (int row = b->row; row < 10; row++)
    {
        if (isBeetle(grid[row][b->col]))
            return grid[row][b->col];
    }
    return nullptr;
}

Creature *getClosestWestBeetle(Creature *grid[10][10], Creature *b)
{
    for (int col = b->col; col > -1; col--)
    {
        if (isBeetle(grid[b->row][col]))
            return grid[b->row][col];
    }
    return nullptr;
}

void populateClosestOrthBeetles(Creature *beetles[4], Creature *grid[10][10], Creature *ant)
{
    // beetles array is {N, E, S, W}
    beetles[0] = getClosestNorthBeetle(grid, ant);
    beetles[1] = getClosestEastBeetle(grid, ant);
    beetles[2] = getClosestSouthBeetle(grid, ant);
    beetles[3] = getClosestWestBeetle(grid, ant);
}

string getAntMoveSide(Creature *grid[10][10], int row, int col)
{
    Creature *ant = grid[row][col];

    // search each direction for nearest beetle --> create static array size 4 of beetles
    Creature *beetles[4];
    populateClosestOrthBeetles(beetles, grid, ant);
    int numOrthBeetles = !!beetles[0] + !!beetles[1] + !!beetles[2] + !!beetles[3];
    // cout << numOrthBeetles << endl;

    // create array of distances for N E S W nearest ant --> if no ant found distance defaults to 10
    int distances[4];
    populateDistances(distances, beetles, ant);
    int north = distances[0];
    int east = distances[1];
    int south = distances[2];
    int west = distances[3];

    // cout << "distances: " << distances[0] << " " << distances[1] << " " << distances[2] << " " << distances[3] << endl;

    // get min distance and check for number of ties
    int maxDist = max(distances[0], max(distances[1], max(distances[2], distances[3])));
    int minDist = min(distances[0], min(distances[1], min(distances[2], distances[3])));
    bool closestTies[4] = {false, false, false, false};
    bool farthestTies[4] = {false, false, false, false};
    int numTies = 0;
    for (int i = 0; i < 4; i++)
    {
        if (distances[i] == maxDist && distances[i] < 10)
        {
            numTies++;
            farthestTies[i] = true;
        }
        if (distances[i] == minDist)
        {
            closestTies[i] = true;
        }
    }

    // no orth beetles --> no movement
    if (numOrthBeetles == 0)
        return "stay";
    else if (numOrthBeetles == 1) // only one closest beetle
    {
        // cout << "one beetle"<<endl;
        // move ant to opposite direction of beetle
        if (north < 10) // N
            return "south";
        else if (east < 10) // E
            return "west";
        else if (south < 10) // S
            return "north";
        else if (west < 10) // W
            return "east";
        // else
            // throw invalid_argument("all elements in ties are nullptr");
    }
    // if there are 2 or 3 orth beetles
    else if (numOrthBeetles == 2)
    {
        if (north < 10 && east < 10)
        {
            if (north == east)
                return "south";
            if (north > east)
                return "west";
            if (north < east)
                return "south";
        }
        if (north < 10 && south < 10)
        {
            if (north == south)
                return "east";
            if (north > south)
                return "north";
            if (north < south)
                return "south";
        }
        if (north < 10 && west < 10)
        {
            if (north == west)
                return "east";
            if (north > west)
                return "east";
            if (north < west)
                return "south";
        }
        if (east < 10 && south < 10)
        {
            if (east == south)
                return "north";
            if (east > south)
                return "north";
            if (east < south)
                return "west";
        }
        if (east < 10 && west < 10)
        {
            if (east == west)
                return "north";
            if (east > west)
                return "east";
            if (east < west)
                return "west";
        }
        if (south < 10 && west < 10)
        {
            if (south == west)
                return "north";
            if (south > west)
                return "east";
            if (south < west)
                return "north";
        }
    }
    else if (numOrthBeetles == 3)
    {
        if (closestTies[0])
            return "south";
        if (closestTies[1])
            return "west";
        if (closestTies[2])
            return "north";
        if (closestTies[3])
            return "east";
    }
    else if (numOrthBeetles == 4)
    {
        // if (numTies == 0)
            // throw new invalid_argument("numTies cannot be 0 in getAntMoveSide");
        if (numTies >= 1)
        {
            if (farthestTies[0])
                return "north";
            if (farthestTies[1])
                return "east";
            if (farthestTies[2])
                return "south";
            if (farthestTies[3])
                return "west";
        }
    }
    // else
        // throw invalid_argument("numTies < 1, which should never happen");

    // throw invalid_argument("reached end of getAntMoveSide without returning anything");
}

void moveAnt(Creature *grid[10][10], int row, int col)
{
    // cout << "running move ant" << endl;

    string side = getAntMoveSide(grid, row, col);
    // cout << side << endl;

    if (side == "north" && isEmpty(grid[row - 1][col]) && inBounds(row - 1, col))
    {
        grid[row][col]->Move("north");
        grid[row - 1][col] = grid[row][col];
        grid[row][col] = nullptr;
    }
    else if (side == "east" && isEmpty(grid[row][col + 1]) && inBounds(row, col + 1))
    {
        grid[row][col]->Move("east");
        grid[row][col + 1] = grid[row][col];
        grid[row][col] = nullptr;
    }
    else if (side == "south" && isEmpty(grid[row + 1][col]) && inBounds(row + 1, col))
    {
        grid[row][col]->Move("south");
        grid[row + 1][col] = grid[row][col];
        grid[row][col] = nullptr;
    }
    else if (side == "west" && isEmpty(grid[row][col - 1]) && inBounds(row, col - 1))
    {
        grid[row][col]->Move("west");
        grid[row][col - 1] = grid[row][col];
        grid[row][col] = nullptr;
    }
}

void setAntHasMovedFalse(Creature *grid[10][10])
{
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isAnt(grid[row][col]))
                grid[row][col]->hasMoved = false;
        }
    }
}

void moveAnts(Creature *grid[10][10])
{
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isAnt(grid[row][col]) && !grid[row][col]->hasMoved)
                moveAnt(grid, row, col);
        }
    }

    setAntHasMovedFalse(grid);
}

void starveBeetles(Creature *grid[10][10]) {}

bool freeForBreeding(Creature *grid[10][10], int row, int col)
{
    return (inBounds(row, col) && isEmpty(grid[row][col]));
}

void breedBeetle(Creature *grid[10][10], int row, int col)
{
    if (freeForBreeding(grid, row - 1, col)) // N
        grid[row - 1][col] = new Beetle(row - 1, col);
    else if (freeForBreeding(grid, row, col + 1)) // E
        grid[row][col + 1] = new Beetle(row, col + 1);
    else if (freeForBreeding(grid, row + 1, col)) // S
        grid[row + 1][col] = new Beetle(row + 1, col);
    else if (freeForBreeding(grid, row, col - 1)) // W
        grid[row][col - 1] = new Beetle(row - 1, col);
    grid[row][col]->Breed();
}

void setBeetleHasBreededFalse(Creature *grid[10][10])
{
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isBeetle(grid[row][col]))
                grid[row][col]->hasBreeded = false;
        }
    }
}

void breedBeetles(Creature *grid[10][10]) {
    // cout<<"breedig beetle"<<endl;
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isBeetle(grid[row][col]) && !grid[row][col]->hasBreeded && grid[row][col]->turnsSinceBreeded==8)
                breedBeetle(grid, row, col);
        }
    }

    setBeetleHasBreededFalse(grid);
}

void setAntHasBreededFalse(Creature *grid[10][10])
{
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isAnt(grid[row][col]))
                grid[row][col]->hasBreeded = false;
        }
    }
}

void updateBeetleTurnsSinceBreeded(Creature *grid[10][10])
{
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isBeetle(grid[row][col]))
                grid[row][col]->turnsSinceBreeded+=1;
        }
    }
}

void breedAnt(Creature *grid[10][10], int row, int col)
{
    if (freeForBreeding(grid, row - 1, col)) // N
        grid[row - 1][col] = new Ant(row - 1, col);
    else if (freeForBreeding(grid, row, col + 1)) // E
        grid[row][col + 1] = new Ant(row, col + 1);
    else if (freeForBreeding(grid, row + 1, col)) // S
        grid[row + 1][col] = new Ant(row + 1, col);
    else if (freeForBreeding(grid, row, col - 1)) // W
        grid[row][col - 1] = new Ant(row - 1, col);
    grid[row][col]->hasBreeded = true;
}

void breedAnts(Creature *grid[10][10])
{
    // cout<<"breedig ants"<<endl;
    for (int col = 0; col < 10; col++)
    {
        for (int row = 0; row < 10; row++)
        {
            if (isAnt(grid[row][col]) && !grid[row][col]->hasBreeded)
                breedAnt(grid, row, col);
        }
    }

    setAntHasBreededFalse(grid);
}

int main()
{
    string fileName;
    char antChar;
    char beetleChar;
    int turns;

    cin >> fileName;
    cin >> antChar;
    cin >> beetleChar;
    cin >> turns;

    Creature *grid[10][10];

    readInFile(fileName, grid);
    // printGrid(grid, antChar, beetleChar);
    setAntHasBreededFalse(grid);
    setBeetleHasBreededFalse(grid);
    for (int i = 1; i < turns + 1; i++)
    {
        // 1) Beetles move
        moveBeetles(grid);
        // cout << "TURN " << i << " after beetle move" << endl;
        // printGrid(grid, antChar, beetleChar);
        // 2) Ants move
        moveAnts(grid);
        // 3) Beetles starve
        starveBeetles(grid);
        // 4) Ants breed
        if (i % 3 == 0)
            breedAnts(grid);
        // 5) Beetles breed
        breedBeetles(grid);

        cout << "TURN " << i << endl;
        printGrid(grid, antChar, beetleChar);
        cout<<endl;
        
        updateBeetleTurnsSinceBreeded(grid);
    }

    return 0;
}
