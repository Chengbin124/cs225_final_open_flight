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
        if (strcmp(argv[1], "routes")) {
            g->printAirports();
        } else if (strcmp(argv[1], "airports")) {
            g->printEdges();
        }
    }

    
    return 0;
}