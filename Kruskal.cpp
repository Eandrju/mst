#include "Kruskal.h"

using namespace std;

Subtree::Subtree(int index) {
    head = index;
    list.push_back(head);
}

bool mycomparator (std::vector<int> i,std::vector<int> j) { return (i[2]<j[2]); }

Kruskal::Kruskal(Graph& graph_) {
    graph = graph_;
    std::sort (graph.edgeList.begin(), graph.edgeList.end(), mycomparator);
    for (int i = 0; i < graph.NumberOfVertices(); i++) {
        Subtree *sub = new Subtree(i);
        forest.push_back(sub);
    }
}

Graph Kruskal::FindMSP() {
    for (int i = 0; i < graph.NumberOfEdges(); i++) {
        if (result.NumberOfEdges() == graph.NumberOfVertices() - 1) break;
        int a, b, cost;
        a = graph.edgeList[i][0];
        b = graph.edgeList[i][1];
        cost = graph.edgeList[i][2];

        int ahead, bhead;
        ahead = forest[a]->head;
        bhead = forest[b]->head;

        if (ahead == bhead)
            continue;

        if (ahead > bhead) {
            for (auto j: forest[ahead]->list) 
                forest[j]->head = bhead;
            forest[bhead]->list.insert(forest[bhead]->list.end(), 
                                  forest[ahead]->list.begin(),
                                  forest[ahead]->list.end());
        } else {
            for (auto j: forest[bhead]->list) 
                forest[j]->head = ahead;
            forest[ahead]->list.insert(forest[ahead]->list.end(), 
                                  forest[bhead]->list.begin(),
                                  forest[bhead]->list.end());
        }
        std::vector<int> edge{a, b, cost};
        result.AddEdge(edge);
    }
    return result;
}

long int Kruskal::ComputeCostOfMST() {
    long int cost = 0;
    for( auto edge: this->result.edgeList) {
        cost += edge[2];
    }
    return cost;
}
