// Shrey Joshi
// NET ID: SXJ210081

#ifndef GRAPH_H
#define GRAPH_H
#include <vector>

using namespace std;

class Graph
{
    public:
        vector<vector<int> > matrix;
        int currSize;
        int maxSize;

        Graph();
        Graph(int parameter);
        bool isEmpty();
        void createGraph(vector<vector<int> > adjMatrix);
        bool isConnected();
        void dfs(int i, vector<bool> &visited);
        bool isBipartite();
};

#endif