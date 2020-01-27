#ifndef __KRUSKAL_ALGORITM__
#define __KRUSKAL_ALGORITM__

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "Graph.h"
#include "PriorityQueue.h"

class Subtree {
    public:
        Subtree(int index);
        int head;
        std::vector< int > list;
};
        

class Kruskal {
    public:
        Kruskal(Graph& graph);
        long int ComputeCostOfMST();
        Graph graph;
        Graph result;
        Graph FindMSP();
        std::vector< Subtree* > forest;
};

#endif
