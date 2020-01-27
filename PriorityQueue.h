#ifndef __PRIORITY_QUEUE__
#define __PRIORITY_QUEUE__

#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <cmath>


struct heapNode {
    int vertex;
    int weight;
};
class PriorityQueue {
    public:
        unsigned long n_decKey;
        unsigned long long n_cassCut;
        unsigned long long n_cut;
        virtual bool IsEmpty();
        virtual void DecreaseKey(int vertex, int newWeight);
        virtual heapNode FindNode(int vertex);
        virtual heapNode ExtractMin();
};


class PriorityQueueBH : public PriorityQueue {
    public:
        PriorityQueueBH(int n, bool verbose);
        PriorityQueueBH();
        bool IsEmpty();
        heapNode ExtractMin();
        void DecreaseKey(int vertex, int newWeight);
        heapNode FindNode(int vertex);
        bool HeapValidation(int n);
    private:
        bool verbose_;
        std::vector<heapNode> heap;
        std::vector<int> position;
        void HeapifyDown();
        void HeapifyUp(int index);
};

struct fibNode {
    fibNode* parent;
    fibNode* child;
    fibNode* left;
    fibNode* right;
    bool marked;
    int degree;
    int weight;
    int vertex;
};

class PriorityQueueFH : public PriorityQueue {
    public:
        PriorityQueueFH(int n);
        PriorityQueueFH(int n, bool verbose);
        void Insert(int vertex, int weight);
        heapNode ExtractMin();
        void DecreaseKey(int vertex, int weight);
        heapNode FindNode(int vertex);
        void Visualize();
        bool IsEmpty();
        bool verbose2;
        int counter;

    private:
        bool verbose_;
        int numberOfNodes;
        void Consolidate();
        fibNode* minimum;
        fibNode* GetNode(int vertex);
        void CascadingCut(fibNode* n);
        void Cut(fibNode* c, fibNode* p);
        std::unordered_map<int, fibNode*> vertexToNodeMap;
        void FibHeapLink(fibNode* y, fibNode* x);
};
        

void PrintPriorityQueue(PriorityQueueBH& pq);

#endif
