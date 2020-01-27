#ifndef __PRIM_ALGORITM__
#define __PRIM_ALGORITM__

#include <iostream>
#include <vector>
#include <limits>
#include "Graph.h"
#include "PriorityQueue.h"

class Prim {
    public:
        Prim(Graph& graph);
        long int ComputeCostOfMST();
        Graph graph;
        Graph result;
};

class PrimAdjMat : public Prim {
    public:
        PrimAdjMat(Graph& graph);
        Graph FindMSP();
        std::vector< std::vector<int> > adjacencyMatrix;
        void ConvertGraphToAdjMat(Graph& graph);
        Graph ConvertAdjMatToGraph();
    private:
        std::vector<int> cost;
        std::vector<bool> isVertexInMST;
        std::vector<int> parentOfVertex;
};

class PrimPQ : public Prim {
    public:
        PrimPQ(Graph& graph, std::string type);
        Graph FindMSP();
        std::vector< std::vector< std::pair<int, int> > > adjacencyList;
        void ConvertGraphToAdjList(Graph& graph);
        PriorityQueue *pq;
        std::vector<int> parentOfVertex;
};



#endif
