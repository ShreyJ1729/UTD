// Shrey Joshi
// NET ID: SXJ210081

#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.h"
#include <sstream>

using namespace std;

vector<int> split(string str)
{
    vector<int> ret = vector<int>();
    stringstream iss( str );
    int number;
    while ( iss >> number ) ret.push_back( number );
    return ret;
}

int main()
{
    ifstream inFile;
    string infilename;
    cin >> infilename;

    inFile.open(infilename);

    int numVertices;
    inFile >> numVertices;
    getline(inFile, infilename);

    Graph *graph = new Graph();
    graph->maxSize = numVertices;
    vector<vector<int> > matrix = vector<vector<int> >();
    for (int i = 0; i < numVertices; i++)
    {
        vector<int> row = vector<int>();
        for (int j = 0; j < numVertices; j++)
        {
            row.push_back(0);
        }
        matrix.push_back(row);
    }

    for (int vertex = 0; vertex < numVertices; vertex++)
    {
        string line;
        getline(inFile, line);

        vector<int> lineSplit = split(line);
        int source;
        for (int i = 0; i < lineSplit.size(); i++)
        {
            int num = lineSplit[i] - 1;
            if (i == 0)
            {
                source = num;
            }
            else
            {
                matrix[source][num] = 1;
            }
        }
    }

    graph->createGraph(matrix);

    // for (int i = 0; i < numVertices; i++)
    // {
    //     for (int j = 0; j < numVertices; j++)
    //     {
    //         cout << matrix.at(i).at(j);
    //     }
    //     cout << endl;
    // }

    cout << (graph->isConnected() ? "connected" : "not connected") << endl;


    cout << (graph->isBipartite() ? "bipartite" : "not bipartite") << endl;
}