#include <iostream>
#include <string>
#include <fstream>
#include <numeric>
#include "Creature.h"
#include "Ant.h"
#include "Beetle.h"

using namespace std;

bool isEmpty(Creature *c) {
    return !c;
}

bool isAnt(Creature *c) {
    return !isEmpty(c) && c->species == "ant";
}

bool isBeetle(Creature *c) {
    return !isEmpty(c) && c->species == "beetle";
}

Creature *getMinOrthogonalAnt (Creature *grid[10][10], int x, int y) {
    // down, up, left, right
    Creature *ants[] = {nullptr, nullptr, nullptr, nullptr};
    int steps[] = {1, 1, 1, 1};

    // check going down
    bool foundAnt = false;
    int i = x; int j = y;
    for (i = x+1; i < 10; i++)
    {
        foundAnt = isAnt(grid[i][j]);
        if (foundAnt) break;
        steps[0]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        ants[0] = grid[i][j];
    // cout << "nearest down: " <<i<<" "<<j<< " steps: " << steps[0] << endl;
    
    // check going up
    foundAnt = false;
    i = x; j = y;
    for (i = x-1; i >= 0; i--)
    {
        foundAnt = isAnt(grid[i][j]);
        if (foundAnt) break;
        steps[1]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        ants[1] = grid[i][j];
    // cout << "nearest up: "  <<i<<" "<<j<< " steps: " << steps[1] << endl;
    

    // check going left
    foundAnt = false;
    i = x; j = y;
    for (j = y-1; j >= 0; j--)
    {
        foundAnt = isAnt(grid[i][j]);
        if (foundAnt) break;
        steps[2]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        ants[2] = grid[i][j];
    // cout << "nearest left: " <<i<<" "<<j<< " steps: " << steps[2] << endl;


    // check going right
    foundAnt = false;
    i = x; j = y;
    for (j = y+1; j < 10; j++)
    {
        foundAnt = isAnt(grid[i][j]);
        if (foundAnt) break;
        steps[3]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        ants[3] = grid[i][j];
    // cout << "nearest right: "  <<i<<" "<<j<< " steps: " << steps[3] << endl;

    // check for tie between orth distance, if it exists then pick the ant with most neighbors
    // make this a separate function later
    int minsteps = 11;
    int direction = -1;
    
    // get minimum step direction and number
    for (int index = 0; index<4; index++)
        if (ants[index] && steps[index]<minsteps) {
            minsteps = steps[index];
            direction = index;
        }
    // cout<<"MINSTEPS: "<<minsteps<<endl<<"DIRECTION: "<<direction<<endl;
    // check for ties in all directions
    bool ties[] = {false, false, false, false};
    for (int index = 0; index<4; index++)
        if (ants[index] && steps[index]==minsteps) {
            ties[index] = true;
        }
    
    int tied = 0;
    tied = accumulate(ties , ties+4, tied);
    
    // if no orth ant exists, return nullpointer so parent function can process edges
    if (tied==0)
        return nullptr;
    else //if (tied==1)
        return ants[direction];
}

Creature *getMinOrthogonalBeetle (Creature *grid[10][10], int x, int y) {

    // down, up, left, right
    Creature *beetles[] = {nullptr, nullptr, nullptr, nullptr};
    int steps[] = {1, 1, 1, 1};

    // check going down
    bool foundBeetle = false;
    int i = x; int j = y;
    for (i = x+1; i < 10; i++)
    {
        foundBeetle = isBeetle(grid[i][j]);
        if (foundBeetle) break;
        steps[0]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        beetles[0] = grid[i][j];
    // cout << "nearest down: " <<i<<" "<<j<< " steps: " << steps[0] << endl;
    
    // check going up
    foundBeetle = false;
    i = x; j = y;
    for (i = x-1; i >= 0; i--)
    {
        foundBeetle = isBeetle(grid[i][j]);
        if (foundBeetle) break;
        steps[1]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        beetles[1] = grid[i][j];
    // cout << "nearest up: "  <<i<<" "<<j<< " steps: " << steps[1] << endl;
    

    // check going left
    foundBeetle = false;
    i = x; j = y;
    for (j = y-1; j >= 0; j--)
    {
        foundBeetle = isBeetle(grid[i][j]);
        if (foundBeetle) break;
        steps[2]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        beetles[2] = grid[i][j];
    // cout << "nearest left: " <<i<<" "<<j<< " steps: " << steps[2] << endl;


    // check going right
    foundBeetle = false;
    i = x; j = y;
    for (j = y+1; j < 10; j++)
    {
        foundBeetle = isBeetle(grid[i][j]);
        if (foundBeetle) break;
        steps[3]++;
    }
    if (i>=0 && i<=9 and j>=0 and j<=9)
        beetles[3] = grid[i][j];
    // cout << "nearest right: "  <<i<<" "<<j<< " steps: " << steps[3] << endl;

    // check for tie between orth distance, if it exists then pick the ant with most neighbors
    // make this a separate function later
    int minsteps = 11;
    int direction = -1;

    
    // get minimum step direction and number
    for (int index = 0; index<4; index++)
        if (beetles[index] && steps[index]<minsteps) {
            minsteps = steps[index];
            direction = index;
        }
    // cout<<"MINSTEPS: "<<minsteps<<endl<<"DIRECTION: "<<direction<<endl;
    // check for ties in all directions
    bool ties[] = {false, false, false, false};
    for (int index = 0; index<4; index++)
        if (beetles[index] && steps[index]==minsteps) {
            ties[index] = true;
        }
    
    int tied = 0;
    tied = accumulate(ties , ties+4, tied);

    // if no orth ant exists, return nullpointer so parent function can process edges
    if (tied==0)
        return nullptr;
    else //if (tied==1)
        return beetles[direction];
}

void moveBeetles(Creature *grid[10][10]) {
    Creature *newgrid[10][10];
    std::copy(&grid[0][0], &grid[0][0]+10*10,&newgrid[0][0]);

    // iterate top to down, the left to right
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (!isBeetle(grid[i][j])) continue;
            // cout << "processing: " << i << " " << j << endl;
            // check all directions to get minimum orthogonal ant
            Creature *minOrthAnt = getMinOrthogonalAnt(grid, i, j);
            // directions are 0, 1, 2, 3 = down, up, left, right
            int direction = -1;
                if (minOrthAnt->x > grid[i][j]->x)
                    direction = 0;
                else if (minOrthAnt->x < grid[i][j]->x)
                    direction = 1;
                else if (minOrthAnt->y < grid[i][j]->y)
                    direction = 2;
                else if ((minOrthAnt->y > grid[i][j]->y))
                    direction = 3;
                // cout<<minOrthAnt->x<<" "<<minOrthAnt->y<<endl;

            // cout << "DIRECTION TO GO: " << direction << endl;

            newgrid[i][j]->Move(direction);
            if (direction==0) newgrid[i+1][j] = newgrid[i][j];
            else if (direction==1) newgrid[i-1][j] = newgrid[i][j];
            else if (direction==2) newgrid[i][j-1] = newgrid[i][j];
            else if (direction==3) newgrid[i][j+1] = newgrid[i][j];
            newgrid[i][j] = nullptr;
        }
    }
    std::copy(&newgrid[0][0], &newgrid[0][0]+10*10,&grid[0][0]);
}

void moveAnts(Creature *grid[10][10]) {
Creature *newgrid[10][10];
    std::copy(&grid[0][0], &grid[0][0]+10*10,&newgrid[0][0]);

    // iterate top to down, the left to right
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (!isAnt(grid[i][j])) continue;
            // cout << "processing: " << i << " " << j << endl;
            // check all directions to get minimum orthogonal ant
            Creature *minOrthBeetle = getMinOrthogonalBeetle(grid, i, j);
            // directions are 0, 1, 2, 3 = down, up, left, right
            int direction = -1;
            if (minOrthBeetle)
            {
                if (minOrthBeetle->x > grid[i][j]->x)
                    direction = 1;
                else if (minOrthBeetle->x < grid[i][j]->x)
                    direction = 0;
                else if (minOrthBeetle->y < grid[i][j]->y)
                    direction = 3;
                else if ((minOrthBeetle->y > grid[i][j]->y))
                    direction = 2;
                // cout<<minOrthBeetle->x<<" "<<minOrthBeetle->y<<endl;
            }

            // cout << "DIRECTION TO GO: " << direction << endl;

            if (direction==0) {
                if (isAnt(newgrid[i+1][j]) || i+1>9) direction = -1;
                else {
                    newgrid[i][j]->Move(direction);
                    newgrid[i+1][j] = newgrid[i][j];
                }
            }
            else if (direction==1) {
                if (isAnt(newgrid[i-1][j]) ||i-1<0) direction = -1;
                else {
                    newgrid[i][j]->Move(direction);
                    newgrid[i-1][j] = newgrid[i][j];
                }
            }
            else if (direction==2) {
                if (isAnt(newgrid[i][j-1]) ||j-1<0) direction = -1;
                else {
                    newgrid[i][j]->Move(direction);
                    newgrid[i][j-1] = newgrid[i][j];
                }
            }
            else if (direction==3) {
                if (isAnt(newgrid[i][j+1]) || j+1>9) direction = -1;
                else {
                    newgrid[i][j]->Move(direction);
                    newgrid[i][j+1] = newgrid[i][j];
                }
            }

            if (direction!=-1) newgrid[i][j] = nullptr;
        }
    }
    std::copy(&newgrid[0][0], &newgrid[0][0]+10*10,&grid[0][0]);
}

void breedAnts(Creature *grid[10][10]) {
    Creature *newgrid[10][10];
    std::copy(&grid[0][0], &grid[0][0]+10*10,&newgrid[0][0]);
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (!isAnt(grid[i][j])) continue;
            if (i-1>=0 && isEmpty(newgrid[i-1][j])) {
                // breed north
                newgrid[i-1][j] = new Ant(i, j);
            } else if (j+1>=0 && isEmpty(newgrid[i][j+1])) {
                // breed right
                newgrid[i][j+1] = new Ant(i, j);
            } else if (i+1<=9 && isEmpty(newgrid[i+1][j])) {
                // breed south
                newgrid[i+1][j] = new Ant(i, j);
            } else if (j-1>=0 && isEmpty(newgrid[i][j-1])) {
                // breed left
                newgrid[i][j-1] = new Ant(i, j);
            }
        }
    }
    std::copy(&newgrid[0][0], &newgrid[0][0]+10*10,&grid[0][0]);
}

void printGrid(Creature *grid[10][10], char antChar, char beetleChar)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (isEmpty(grid[i][j]))
                cout << " ";
            else if (isAnt(grid[i][j]))
                cout << antChar;
            else
                cout << beetleChar;
        }
        cout << endl;
    }
    cout<<endl;
}

int main()
{
    string fileName;
    char antChar;
    char beetleChar;
    int turns;
    ifstream inFile;

    cin >> fileName;
    cin >> antChar;
    cin >> beetleChar;
    cin >> turns;
    inFile.open(fileName);

    string line;
    Creature *grid[10][10];

    for (int i = 0; i < 10; i++)
    {
        getline(inFile, line);

        for (int j = 0; j < 10; j++)
        {
            char c = line[j];
            if (c == 'a')
                grid[i][j] = new Ant(i, j);
            else if (c == 'B')
                grid[i][j] = new Beetle(i, j);
            else
                grid[i][j] = nullptr;
        }
    }

    // printGrid(grid, antChar, beetleChar);

    for (int i = 1; i < turns+1; i++)
    {
        // 1) Beetles move
        moveBeetles(grid);
        // 2) Ants move
        moveAnts(grid);
        // 3) Beetles starve
        // starveBeetles();
        // 4) Ants breed
        if (i%3==0) {
            cout<<"BEFORE BREED"<<endl;
            printGrid(grid, antChar, beetleChar);
            breedAnts(grid);
        }
        // 5) Beetles breed
        // breedBeetles();
        cout << "TURN " << i << endl;
        printGrid(grid, antChar, beetleChar);
    }
}