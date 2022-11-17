#include "graph.h"

#include <iostream>

using namespace std;

int main() {
    cout << "Add our codes here!" << endl;
    Graph* g = new Graph();
    g -> readFromAirports("../../data/airports.dat.txt");
    
    return 0;
}