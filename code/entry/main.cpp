#include "graph.h"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    /***
    cout << "Add our codes here!" << endl;
    Graph* g = new Graph();
    g -> readFromAirports("../../data/airports.dat.txt");
    g -> readFromRoutes("../../data/routes.dat.txt");
    ****/
Graph g;
    g.addVertex("a", 0);
    g.addVertex("b", 1);
    g.addVertex("c", 2);
    g.addVertex("d", 3);
    g.addVertex("e", 4);
    g.addVertex("f", 5);
    g.addEdge(0, 1);
    g.setWeight(0, 1, 2);
    g.addEdge(0, 3);
    g.setWeight(0, 3, 2);
    g.addEdge(1, 2);
    g.setWeight(1, 2, 4);
    g.addEdge(3, 2);
    g.setWeight(3, 2, 6);
    g.addEdge(1, 4);
    g.setWeight(1, 4, 2);
    g.addEdge(4, 2);
    g.setWeight(4, 2, 2);
    g.addEdge(3, 5);
    g.setWeight(3, 5, 2);
    g.addEdge(5, 2);
    g.setWeight(5, 2, 2);


    g.betweennessCentrality("e");
    /*****
    if (argc > 1) {
        if (strcmp(argv[1], "routes") == 0) {
            g->printAirports();
        } else if (strcmp(argv[1], "airports") == 0) {
            g->printEdges();
        }
        else if( strcmp(argv[1], "bfs") == 0){
            g -> BfsStep(0);
        }
        else if(strcmp(argv[1],"map") == 0){
            g -> printMap();
        }
    }
    ******/

    
    return 0;
}