#pragma once

#include <vector>
#include <string>
#include <map>
#include "airport.h"
#include <iostream>
#include <fstream>

using namespace std;

class Graph
{
public:
    void readFromAirports(string file);

    void readFromRoutes(string file);

    /**
     * Constructor of the graph, taking datas from two datasets.
     */
    Graph(string airports, string routes);

    Graph();

    /**
     * Implement Dijkstra's algorithm to get the shortest paths from one point.
     * @param source The start point in the graph.
     * @return The shortest paths from the start points to all points, stored in a sequence.
     * To be modified in next part so that it will find all the shortest paths.
     */
    vector<vector<int>> shortestPaths(int source);

    /**
     * Find the shortest paths from one city to another via airports.
     */
    vector<string> shortestPaths(string s1, string s2);

    /**
     * Modified the Dijkstra's algorithm to get all shortest paths from one point to all other points.
     */
    map<int, vector<vector<int>>> allShortestPaths(int source);

    /**
     * Calaculate the number of shortest paths from s1 to s2.
     */
    int countShortestPaths(string s1, string s2);

    /**
     * Calculate the number of shortest paths from s1 to s2, going through s3.
     */
    int countShortestPaths(string s1, string s2, string s3);

    /**
     * Calculate the betweenness centrality of one point.
     */
    double betweennessCentrality(string s);

    /**
     * Using BFS to traverse the graph.
     */
    vector<int> Bfs(int start) const;

    /*helper function for test cases*/
    /*return the total number of vertices*/
    int verticeCount();

    /*return the adjacency list of an airport name*/
    vector<string> getAdjacency(string id);

private:
    vector<string> split(string s);
    void printAirports()
    {
        int counter = 0;
        map<int, string>::iterator it;
        for (it = convert.begin(); it != convert.end(); it++)
        {
            cout << it->second << endl;
            counter++;
        }
        cout << counter << " " << vertices.size() << endl;
    }
    void printEdges() const
    {
        int count = 0;

        for (unsigned i = 0; i < vertices.size(); i++)
        {
            if (adjacency.at(i).size() > 1)
            {
                cout << "Airport " << convert.at(i) << " has flight to ";
                for (unsigned j = 0; j < adjacency.at(i).size(); j++)
                {
                    cout << convert.at(adjacency.at(i)[j]) << ", ";
                    count++;
                }
                cout << endl;
            }
        }
        cout << count << endl;
    }
    /**
     * Find the corresponding airport id to the index in the graph.
     */
    map<string, int> vertices;

    map<int, Airport> airports;

    /**
     * Convert the vertices index to the airport name.
     */
    map<int, string> convert;

    vector<vector<int>> adjacency;


    vector<map<int, int>> weights;
};
