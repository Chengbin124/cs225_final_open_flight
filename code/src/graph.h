#pragma once

#include <vector>
#include <utility>
#include <string>
#include <map>
#include "airport.h"
#include <iostream>
#include <fstream>
#include "color.h"
#include <queue>
#include "Image.h"
#include "StickerSheet.h"
#include <chrono>
#include <thread>
#include <algorithm>
#include <set>

using namespace std;

class Graph
{
public:

    /**
     * Use this function to load Airport data from the file. We discard the entries with missing entries.
     */
    void readFromAirports(string file);

    /**
     * Use this function to load route data from the route files. We discard the entries with unrecorded airport_id from airport files.
     */
    void readFromRoutes(string file);

    /**
     * Constructor of the graph, taking datas from two datasets.
     */
    Graph(string airports, string routes);


    /**
     * Default constructor.
     */
    Graph();

    /**
     * Implement Dijkstra's algorithm to get the shortest paths from one point.
     * @param source The start point in the graph.
     * @return The shortest paths from the start points to all points, stored in a sequence.
     * To be modified in next part so that it will find all the shortest paths.
     * In our implement, this algorithm takes O(|V|^2) time
     */
    vector<vector<int>> shortestPaths(int source);

    /**
     * Find the shortest paths from one city to another via airports.
     */
    vector<string> shortestPaths(string s1, string s2);

    /**
     * Modified the Dijkstra's algorithm to get all shortest paths from one point to all other points.
     * In this implement, we take O(|V|(log(|V|)) + (|E|)) time
     * @return The first map is the shortest distance matrix and the second map is the number of shortest paths 
     * from source to other vertices.  
     */
    std::pair<map<int, int>, map<int, int>> allShortestPaths(int source);

    /**
     * Calculate the betweenness centrality of one point.
     */
    double betweennessCentrality(string s);

    /**
     * Using BFS to traverse the graph.
     */
    vector<int> Bfs(int start) const;

    /**
     * BFS in steps
     */
    vector<int> BfsStep(int start) const;

    void printBfsStep(queue<int> queue, int counter, int color) const;

    void printLoad(unsigned current, unsigned max) const;

    /*helper function for test cases*/
    /*return the total number of vertices*/
    int verticeCount() const;

    /*return the adjacency list of an airport name*/
    vector<string> getAdjacency(string id);

    /*return the map of weight of an airpot id*/
    map<int, int> getWeight(int id);

    /*add vertices to a graph*/
    void addVertex(string name, int id);

    /*add edge to a graph*/
    void addEdge(int src, int dest);

    /*set weight to an edge*/
    void setWeight(int src, int dest, int weight);

    /**
     * Use this function to print our weights get from data to get a sense of it.
     */
    void printWeight() const;

    /**
     * Print the airports list we read from the file.
     */
    void printAirports();

    /**
     * Print the routes we read from the route file.
     */
    void printEdges() const;

    /**
     * Print the map.
     */
    void printMap() const;

private:
    vector<string> split(string s);

    /**
     * Find the corresponding airport id to the index in the graph.
     */
    map<string, int> vertices;

    // maps index to latitude and longitude
    map<int, pair<long double, long double>> airports;

    map<string, int> nameToidx;

    /**
     * Convert the vertices index to the airport name/id.
     */
    map<int, string> convert;

    /** 
     * Adjacency list of the graph: adjacency[i] is the vector of index of the vertices from i connecting to it.
     */
    vector<vector<int>> adjacency;

    /**
     * weights[i][j] represents the weight from vertex of index i to vertex of index j.
     */
    vector<map<int, int>> weights;

    /**
     * Given two logitude and latitude, we calculate the distance of it.
     */
    long double calculateDistance(pair<long double, long double> a, pair<long double, long double> b)
    {
        long double dlat = toRadians(a.second) - toRadians(b.second);

        long double dlong = toRadians(a.first) - toRadians(b.first);
        long double ans = pow(sin(dlat / 2), 2) + cos(toRadians(b.second)) * cos(this->toRadians(a.second)) * pow(sin(dlong / 2), 2);
        ans = 2.0 * asin(sqrt(ans));
        return ans * 3956;
    }

    /**
     * Helper function for calculateDistance.
     */
    long double toRadians(long double a) const
    {
        long double rad = (M_PI) / 180;
        return a * rad;
    }

    /**
     *
     */
    void countPaths(int source, int target, map<int, set<int>> &prev, int &count);
};
