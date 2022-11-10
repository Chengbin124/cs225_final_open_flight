#pragma once

#include <vector>
#include <string>
#include <map>


using namespace std;

class Graph {
    public:
        void readFromAirports(string file);

        void readFromRoutes(string file);

        /** 
         * Constructor of the graph, taking datas from two datasets.
         */ 
        Graph(string airports, string routes);

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

    private:

        /**
         * Find the corresponding airport id/name to the index in the graph.
         */
        map<string, int> vertices;

        map<int, string> convert;

        vector<vector<int>> adjacency;

        vector<vector<int>> edges;
};

