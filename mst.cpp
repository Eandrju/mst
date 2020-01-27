#include <iostream>
#include <string>
#include <vector>
#include "Prim.h"
#include "Kruskal.h"
#include "Graph.h"
#include <chrono>
#include "PriorityQueue.h"


int main(int argc, char **argv){
    std::string type;
    std::string graph_path = "new_graph.txt";
    if (argc == 2) {
        type = argv[1];
    }
    else if (argc== 3) {
        type = argv[1];
        graph_path = argv[2];
    }
    else {
        std::cout << "Wrong number of arguments!" << std::endl;
        return 1;
    }

    Graph graph, result1, result2, result3, result4;
    LoadGraphFromFile(graph, graph_path);
    std::chrono::duration<double> e1, e2;
    std::ofstream output;
    
    std::cout << "number of vertecies: " << graph.NumberOfVertices();
    std::cout << "number of edges: " << graph.NumberOfEdges() << "\n";

    long int cost;

    if (type == "adj") {
        auto start1 = std::chrono::high_resolution_clock::now();
        PrimAdjMat algorithm(graph);
        auto start2 = std::chrono::high_resolution_clock::now();
        result1 = algorithm.FindMSP();
        auto end = std::chrono::high_resolution_clock::now();
        e1 = end - start1;
        e2 = end - start2;
        cost = algorithm.ComputeCostOfMST();

        std::cout << "---------------\n";
        std::cout << "Prim Algorithm with Adjacency Matrix\n";
        std::cout << "It took me: " << e2.count() << " seconds. The cost is: " << cost << "\n";
        std::cout << "With init it took me: " << e1.count() << " seconds.\n";
        std::cout << "Graph: v: " << result1.NumberOfVertices() << " e: " << result1.NumberOfEdges() <<"\n";
        
    }
    else if (type == "bin"){
        auto start1 = std::chrono::high_resolution_clock::now();
        PrimPQ algorithm2(graph, "binary");
        auto start2 = std::chrono::high_resolution_clock::now();
        result2 = algorithm2.FindMSP();
        auto end = std::chrono::high_resolution_clock::now();
        e1 = end - start1;
        e2 = end - start2;
        cost = algorithm2.ComputeCostOfMST();

        std::cout << "---------------\n";
        std::cout << "Prim Algorithm with Priority Queue - Binary Heap\n";
        std::cout << "It took me: " << e2.count() << " seconds. The cost is: " << cost << "\n";
        std::cout << "With init it took me: " << e1.count() << " seconds.\n";
        std::cout << "Graph: v: " << result2.NumberOfVertices() << " e: " << result2.NumberOfEdges() <<"\n";
    }
    else if (type == "fib") {
        auto start1 = std::chrono::high_resolution_clock::now();
        PrimPQ algorithm3(graph, "fibonachi");
        auto start2 = std::chrono::high_resolution_clock::now();
        result3 = algorithm3.FindMSP();
        auto end = std::chrono::high_resolution_clock::now();
        e1 = end - start1;
        e2 = end - start2;
        cost = algorithm3.ComputeCostOfMST();

        std::cout << "---------------\n";
        std::cout << "Prim Algorithm with Priority Queue - Fibonachi Heap\n";
        std::cout << "It took me: " << e2.count() << " seconds. The cost is: " << cost << "\n";
        std::cout << "With init it took me: " << e1.count() << " seconds.\n";
        std::cout << "Graph: v: " << result3.NumberOfVertices() << " e: " << result3.NumberOfEdges() <<"\n";

    }
    else if (type == "kru") {
        auto start1 = std::chrono::high_resolution_clock::now();
        Kruskal krus(graph);
        auto start2 = std::chrono::high_resolution_clock::now();
        result4 = krus.FindMSP();
        auto end = std::chrono::high_resolution_clock::now();
        e1 = end - start1;
        e2 = end - start2;
        cost = krus.ComputeCostOfMST();

        std::cout << "---------------\n";
        std::cout << "Kruskal Algorithm\n";
        std::cout << "It took me: " << e2.count() << " seconds. The cost is: " << cost << "\n";
        std::cout << "With init it took me: " << e1.count() << " seconds.\n";
        std::cout << "Graph: v: " << result3.NumberOfVertices() << " e: " << result3.NumberOfEdges() <<"\n";
    }


    output.open("score.txt");
    output << std::fixed << e2.count() << " " << e1.count() << "\n";
    output.close();

}
