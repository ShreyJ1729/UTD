// Shrey Joshi and Ian Fletchall
// NET ID: SXJ210081 and IXF210007

#include "iostream"
#include "Graph.h"
#include <queue>

using namespace std;

Graph::Graph() {
    this->currSize = 0;
    this->maxSize = 0;
}

Graph::Graph(int maxSize)
{
    this->currSize = 0;
    this->maxSize = maxSize;
}

bool Graph::isEmpty() {
    return (this->currSize == 0);
}

void Graph::createGraph(vector<vector<int> > matrix) {
    this->matrix = matrix;
    this->currSize = matrix.size();
}

bool Graph::isConnected() {
    vector<bool> visited = vector<bool>();
    // cout << this->currSize<<endl;
    for (int i = 0; i < this->currSize; i++) visited.push_back(0);
    this->dfs(0, visited);
    for (int i : visited)
    {
        if (i==0) return false;
    }
    return true;

}

void Graph::dfs(int start, vector<bool> &visited)
{
    visited[start] = true;

    for (int i = 0; i < this->matrix[start].size(); i ++)
    {
        if (this->matrix[start][i] && !visited[i])
        {
            this->dfs(i, visited);
        }
    }
}

bool Graph::isBipartite() {
    //Create a vector to hold the "colored" nodes.
    vector<int> colors = vector<int>();
    
    //Initialize the vector with a default "color."
    for (int i = 0; i < this->currSize; i ++) colors.push_back(-1);

    //Create a queue to hold nodes for a BFS.
    queue<int> nodes = queue<int>();
    nodes.push(0);
    
    //Color the starting vertex.
    colors[0] = 1;

    while(!(nodes.empty())) {
        //Dequeue the current node.
        int curr = nodes.front();
        nodes.pop();
        
        // Iterate over all the neighbors
        for (int neighbor = 0; neighbor < this->currSize; neighbor++)
        {
            if (this->matrix[curr][neighbor] == 0) continue;

            if(colors[neighbor] == -1) { //If the neighbor of the current node is colorless,
                //color the neighbor the opposite color of the current node.
                colors[neighbor] = (colors[curr]==1) ? 2 : 1;
                nodes.push(neighbor);
            } else {
                if (colors[neighbor] != -1 && colors[neighbor] == colors[curr]) {
                    return false;
                }
            }
        }
    }

    return true;
}