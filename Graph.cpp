#include "Graph.h"

Graph::Graph() {
}

Graph::Graph(int numberOfVertices, float density) { 
    this->InitializeRandomGraph(numberOfVertices, density); 
}


void LoadGraphFromFile(Graph& g, std::string& file) {
    std::fstream f;
    f.open(file);
    int numberOfVertices;
    while(f.peek() != EOF) {
        std::vector<std::string> parameters = GetNextLineAndSplitIt(f);
        std::vector<int> edge;

        for (std::string param: parameters) {
            edge.push_back(std::stoi(param)); 
        }

        g.AddEdge(edge);
    }
    f.close();
};


bool SaveGraphToFile(std::string file, Graph& graph) {
    std::ofstream f;
    std::cout << "----------\n";
    std::cout << "Saving graph to a file." << std::endl;
    f.open(file);
    for (int i = 0; i < graph.NumberOfEdges(); i++) {
        f << graph.edgeList[i][0];
        f << ',';
        f << graph.edgeList[i][1];
        f << ',';
        f << graph.edgeList[i][2];
        f << '\n';
    }
    f.close();
    std::cout << "Graph saved." << std::endl;
    return true;
};


std::vector<std::string> GetNextLineAndSplitIt(std::istream& str)
{
    std::vector<std::string> result;
    std::string line; std::getline(str, line);
    std::stringstream lineStream(line);
    std::string cell;

    while(std::getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }

    return result;
};


void Graph::InitializeRandomGraph(int numberOfVertices, float density) {
    int a;
    a = time(NULL);
//    a = 1573940266;
//    a = 1574072774;
    srand(a);
    //srand(0);
    std::cout << "seed: " << a << std::endl;
    float foo;
    int value;
    int edgeCounter = 0;

    for (int i = 0; i< numberOfVertices; i++) {
        for (int j = i; j < numberOfVertices; j++) {
            if (i == j) continue;
            foo = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if (foo < density) {
                value = rand() % 10000;
                std::vector<int> edge;
                edge.push_back(i);
                edge.push_back(j);
                edge.push_back(value);
                this->AddEdge(edge);
            }
        }
    }
    std::cout << "----------\n";
    std::cout << "Initialized random graph with:\n";
    std::cout << "    - " << this->NumberOfVertices() << " vertices\n";
    std::cout << "    - " << this->NumberOfEdges() << " edges\n";
}

void Graph::AddEdge(std::vector<int> edge) {
    this->edgeList.push_back(edge);
    this->vertexSet.insert(edge[0]);
    this->vertexSet.insert(edge[1]);

}

int Graph::NumberOfEdges() {
    return this->edgeList.size();
}

int Graph::NumberOfVertices() {
    return this->vertexSet.size();
}

void PrintGraphEdges(Graph& graph) {
    for (auto e : graph.edgeList) 
        std::cout<< e[0] << " - " << e[1] << "  " << e[2] << std::endl;
}

