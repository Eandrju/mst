#include <iostream>
#include "Graph.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Wrong number of arguments\n";
    }

    int number;
    float density;

    number = std::stoi(argv[1]);
    density = std::stof(argv[2]);

    Graph graph(number, density);
    SaveGraphToFile("new_graph.txt", graph);
    std::cout << "New graph saved\n";
}
