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
        if (strcmp(argv[1], "airports") == 0) {
            g->printAirports();
        } else if (strcmp(argv[1], "routes") == 0) {
            g->printEdges();
        } else if (strcmp(argv[1], "weights") == 0) {
            g->printWeight();
        }
        else if( strcmp(argv[1], "bfs") == 0){
            g -> BfsStep(0);
        }
        else if(strcmp(argv[1],"map") == 0){
            g -> printMap();
        }
    }


    cout<<"Calculating betweenness centrality might take about twenty minutes."<<endl;
    
    //cout<<g->betweennessCentrality("Hamad International Airport")  << endl;
    

    cout<<g->betweennessCentrality("Handan Airport")  << endl;


    return 0;
}