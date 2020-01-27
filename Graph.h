#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <ctime>
#include <cstdlib>


class Graph {
    public:
        Graph();
        Graph(int numberOfVertices, float density);

        std::vector< std::vector<int> > edgeList;
        std::set<int> vertexSet;
        void AddEdge(std::vector<int> edge);

        int NumberOfVertices();
        int NumberOfEdges();
        void InitializeRandomGraph(int numberOfVertices, float density);
};        

void LoadGraphFromFile(Graph& g, std::string& file);
bool SaveGraphToFile(std::string file, Graph& graph);
void PrintGraphEdges(Graph& graph);
std::vector<std::string> GetNextLineAndSplitIt(std::istream& str);

#endif
