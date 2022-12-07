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
#include <set>

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
    std::pair<map<int, int>, map<int, int>> allShortestPaths(int source);

    /**
     * Calculate the betweenness centrality of one point.
     */
    double betweennessCentrality(string s);

    /**
     * Using BFS to traverse the graph.
     */
    vector<int> Bfs(int start) const;

    vector<int> BfsStep(int start) const;

    void printBfsStep(queue<int> queue, int counter, int color) const;

    void printLoad(unsigned current, unsigned max) const;

    /*helper function for test cases*/
    /*return the total number of vertices*/
    int verticeCount();

    /*return the adjacency list of an airport name*/
    vector<string> getAdjacency(string id);

    /*return the map of weight of an airpot id*/
    map<int, int> getWeight(int id);

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
    void printMap() const{
        Image worldMap;
        worldMap.readFromFile("../map.png");
        Image dot;
        dot.readFromFile("../dot.png");
        dot.scale(3,3);
        StickerSheet* airportMap = new StickerSheet(worldMap,airports.size());
        //map<int, pair<long double, long double>>::iterator it;
        int middleX = worldMap.width()/2;
        int middleY = worldMap.height()/2;
        int xcord;
        int ycord;
        double radius = worldMap.width()/(2*3.14);
        for(unsigned i = 0; i < 1500/*airports.size()*/; i++){
            if(airports.find(i) != airports.end()){
                
                // double x = (airports.at(i).second+180)*(worldMap.width()/360);
                long double latRad = toRadians(airports.at(i).first);
                double mercN = log(tan((3.14/4)+(latRad/2))) * radius;
                // double y     = (worldMap.height()/2)-(worldMap.width()*mercN/(2*3.14));
                long double longRad = toRadians(airports.at(i).second + 180);
                double x = longRad * radius;
                double y = worldMap.height()/2 - mercN; 
                //double x = cos(latRad) * cos(longRad) * middleX + middleX;
                //double y = cos(latRad) * sin(longRad) * middleY + middleY;
                airportMap -> addSticker(dot, (int)x, (int)y);
                cout << convert.at(i) << endl;
            }
        }
        Image output = airportMap->render();
        output.writeToFile("../myImage.png");
        cout << "printed map" << endl;
        delete(airportMap);
    }

private:
    vector<string> split(string s);

    /**
     * Find the corresponding airport id to the index in the graph.
     */
    map<string, int> vertices;

    // maps index to latitude and longitude
    map<int, pair<long double, long double>> airports;

    /**
     * Convert the vertices index to the airport name.
     */
    map<int, string> convert;

    vector<vector<int>> adjacency;

    vector<map<int, int>> weights;
    long double calculateDistance(pair<long double, long double> a, pair<long double, long double> b)
    {
        long double dlat = toRadians(a.second) - toRadians(b.second);
        long double dlong = toRadians(a.first) - toRadians(b.first);
        long double ans = pow(sin(dlat / 2), 2) + cos(toRadians(b.second)) * cos(this->toRadians(a.second)) * pow(sin(dlong / 2), 2);
        ans = 2 * asin(sqrt(ans));
        return ans * 3956;
    }
    long double toRadians(long double a) const
    {
        long double rad = (M_PI) / 180;
        return a * rad;
    }

    void countPaths(int source, int target, map<int, set<int>>& prev, int& count);
};
