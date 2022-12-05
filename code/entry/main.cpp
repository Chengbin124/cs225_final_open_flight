#include "graph.h"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Add our codes here!" << endl;
    Graph* g = new Graph();
    g -> readFromAirports("../../data/airports.dat.txt");
    g -> readFromRoutes("../../data/routes.dat.txt");
    if (argc > 1) {
        if (strcmp(argv[1], "routes") == 0) {
            g->printAirports();
        } else if (strcmp(argv[1], "airports") == 0) {
            g->printEdges();
        }
        else if( strcmp(argv[1], "bfs") == 0){
            g -> BfsStep(0);
        }
    }

    
    return 0;
}