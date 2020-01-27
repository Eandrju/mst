#include "Prim.h"


long int Prim::ComputeCostOfMST() {
    long int cost = 0;
    for( auto edge: this->result.edgeList) {
        cost += edge[2];
    }
    return cost;
}

Prim::Prim(Graph& graph) {
    this->graph = graph;
}


PrimAdjMat::PrimAdjMat(Graph& graph) 
    : Prim(graph) {
    this->ConvertGraphToAdjMat(graph);
    for (int i = 0; i < graph.NumberOfVertices(); i++) {
        this->isVertexInMST.push_back(false);
        this->cost.push_back(INT32_MAX);
        this->parentOfVertex.push_back(-1);
    }
};


void PrimAdjMat::ConvertGraphToAdjMat(Graph& graph) {

    for (int i = 0; i < graph.NumberOfVertices(); i++) {
        std::vector<int> row;
        for (int j = 0; j < graph.NumberOfVertices(); j++) {
            row.push_back(-1);
        }
        this->adjacencyMatrix.push_back(row);
    }

    int x, y;
    for (auto edge: graph.edgeList) {
        x = static_cast <int> (edge[0]);
        y = static_cast <int> (edge[1]);
        this->adjacencyMatrix[y][x] = edge[2];
        this->adjacencyMatrix[x][y] = edge[2];
    }
};



Graph PrimAdjMat::FindMSP() {
    this->cost[0] = 0;
    int minKey, minCost, parent, edgeCost;
        
    for (int i = 0; i < this->graph.NumberOfVertices(); i++) {
    
        minCost = INT32_MAX;

        //finding minimum vertex 
        for (int j = 0; j < this->graph.NumberOfVertices(); j++) {
            if (!this->isVertexInMST[j] && this->cost[j] < minCost) {
                minKey = j;
                minCost = this->cost[j];
            }
        }

        this->isVertexInMST[minKey] = true;
    
        parent = this->parentOfVertex[minKey];
   
        if (parent != -1) {

            std::vector<int> edge;
            edge.push_back( static_cast<int> (parent));
            edge.push_back( static_cast<int> (minKey));
            edge.push_back( this->adjacencyMatrix[parent][minKey]);
            
            this->result.AddEdge(edge);
        }
    
        // updating costs to vertices
        for (int j = 0; j < this->graph.NumberOfVertices(); j++) {
            edgeCost = this->adjacencyMatrix[j][minKey];
            if (edgeCost != -1 && !this->isVertexInMST[j]) {
                if (edgeCost < this->cost[j]) {
                    this->parentOfVertex[j] = minKey;
                    this->cost[j] = edgeCost;
                }
            }
        }
    }

    return this->result;
};


PrimPQ::PrimPQ(Graph& graph, std::string type) 
    : Prim(graph) {
    this->adjacencyList.resize(graph.NumberOfVertices());
    this->ConvertGraphToAdjList(graph);
    for (int i = 0; i <graph.NumberOfVertices(); i++) {
        this->parentOfVertex.push_back(-1);
    }
    if (type == "fibonachi") 
        this->pq = new PriorityQueueFH(graph.NumberOfVertices(), false);
    else
        this->pq = new PriorityQueueBH(graph.NumberOfVertices(), false);
};

void PrimPQ::ConvertGraphToAdjList(Graph& graph) {
    int x, y;
    for (auto edge: graph.edgeList) {
        x = static_cast <int> (edge[0]);
        y = static_cast <int> (edge[1]);
        std::pair<int, int> foo(x, edge[2]);
        std::pair<int, int> buzz(y, edge[2]);
        this->adjacencyList[y].push_back(foo);
        this->adjacencyList[x].push_back(buzz);
    }
}  

Graph PrimPQ::FindMSP() {
    int parent;
    this->pq->DecreaseKey(0, 0);

    while (!this->pq->IsEmpty()) {
        heapNode minimum;
        minimum = pq->ExtractMin();
        parent = this->parentOfVertex[minimum.vertex];

        if (parent != -1) {
            std::vector<int> edge;
            edge.push_back( static_cast<int> (parent));
            edge.push_back( static_cast<int> (minimum.vertex));
            edge.push_back( static_cast<int> (minimum.weight));

            this->result.AddEdge(edge);
        }
        
        //updating costs of vertices
        int index;
        for (auto v: this->adjacencyList[minimum.vertex]) {
            heapNode n;
            n = this->pq->FindNode(v.first);
            if (n.vertex != -1) {
                if (v.second < n.weight) {
                    this->pq->DecreaseKey(v.first, v.second);
                    this->parentOfVertex[v.first] = minimum.vertex;
                }
            }
        }


           // index = this->pq.position[v.first];
           // if (index != -1 ) {
           //     if (v.second < this->pq.heap[index].weight) {
           //         this->pq.DecreaseKey(v.first, v.second);
           //         this->parentOfVertex[v.first] = minimum.vertex;
           //     }
           // }
      //  }
    }
    return this->result;
}

