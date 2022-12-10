#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "graph.h"

using namespace std;

// TEST_CASE("Airport distance", "[weight=1][part=1]")
// {
//     Airport a = {10, 20, "1", "a"};
//     Airport b = {10, 30, "2", "b"};
//     Airport c = {0, 40, "3", "c"};
//     double a2b = 600;
//     double a2c = 1305;
//     double b2c = 774;
//     REQUIRE(a.calculateDistance(b) == a2b);
//     REQUIRE(a.calculateDistance(c) == a2c);
//     REQUIRE(b.calculateDistance(c) == b2c);
// }

TEST_CASE("Read files", "[weight=1][part=1]")
{
    Graph graph;
    graph.readFromAirports("../../data/test_airport.txt");
    REQUIRE(graph.verticeCount() == 10);

    graph.readFromRoutes("../../data/test_route.txt");
    REQUIRE(graph.getAdjacency("1").size() == 1);
    REQUIRE(graph.getAdjacency("1")[0] == "b");
    REQUIRE(graph.getAdjacency("5").size() == 0);
    REQUIRE(graph.getAdjacency("7").size() == 5);
    REQUIRE(graph.getAdjacency("7")[3] == "f");
}

TEST_CASE("Graph constructor", "[weight=1][part=1]")
{
    Graph graph;
    graph = Graph("../../data/test_airport.txt", "../../data/test_route.txt");

    REQUIRE(graph.verticeCount() == 10);
    REQUIRE(graph.getAdjacency("1").size() == 1);
    REQUIRE(graph.getAdjacency("1")[0] == "b");
    REQUIRE(graph.getAdjacency("5").size() == 0);
    REQUIRE(graph.getAdjacency("7").size() == 5);
    REQUIRE(graph.getAdjacency("7")[3] == "f");
}

TEST_CASE("Test BFS", "[weight=1][part=1]")
{
    Graph g;
    g.readFromAirports("../../data/test_airport.txt");
    g.readFromRoutes("../../data/test_route.txt");

    vector<int> expected1{0, 1};

    vector<int> result1 = g.BfsStep(0);

    vector<int> result2 = g.BfsStep(6);

    vector<int> expected2{6, 5, 1, 8, 3, 0};

    REQUIRE(result1.size() == expected1.size());

    REQUIRE(result2.size() == expected2.size());

    for (size_t i = 0; i < result1.size(); i++)
    {
        REQUIRE(result1[i] == expected1[i]);
    }

    for (size_t i = 0; i < result2.size(); i++)
    {
        REQUIRE(result2[i] == expected2[i]);
    }
}



TEST_CASE("Graph with 4 vertices", "[weight=1][part=2]")
{
    Graph g;
    g.addVertex("a", 0);
    g.addVertex("b", 1);
    g.addVertex("c", 2);
    g.addVertex("d", 3);
    g.addEdge(0, 1);
    g.setWeight(0, 1, 2);
    g.addEdge(0, 3);
    g.setWeight(0, 3, 3);
    g.addEdge(1, 2);
    g.setWeight(1, 2, 5);
    g.addEdge(3, 2);
    g.setWeight(3, 2, 6);

    // Test shortest path algorithm
    vector<string> ac = {"a", "b", "c"};
    REQUIRE(g.shortestPaths("a", "c") == ac);
}

TEST_CASE("Graph with 5 vertices", "[weight=1][part=2]")
{
    Graph g;
    g.addVertex("a", 0);
    g.addVertex("b", 1);
    g.addVertex("c", 2);
    g.addVertex("d", 3);
    g.addVertex("e", 4);
    g.addEdge(0, 1);
    g.setWeight(0, 1, 2);
    g.addEdge(0, 3);
    g.setWeight(0, 3, 3);
    g.addEdge(1, 2);
    g.setWeight(1, 2, 4);
    g.addEdge(3, 2);
    g.setWeight(3, 2, 6);
    g.addEdge(1, 4);
    g.setWeight(1, 4, 3);
    g.addEdge(4, 2);
    g.setWeight(4, 2, 2);


    // Test shortest path algorithm
    vector<string> ac = {"a", "b", "c"};
    REQUIRE(g.shortestPaths("a", "c") == ac);
    vector<string> bc = {"b", "c"};
    REQUIRE(g.shortestPaths("b", "c") == bc);
}

TEST_CASE("Graph with 6 vertices", "[weight=1][part=2]")
{
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

    // Test shortest path algorithm
    vector<string> af = {"a", "d", "f"};
    REQUIRE(g.shortestPaths("a", "f") == af);
    vector<string> df = {"d", "f"};
    REQUIRE(g.shortestPaths("d", "f") == df);
    vector<string> dc = {"d","f", "c"};
    REQUIRE(g.shortestPaths("d","c") == dc);

    // Test allShortestPaths
    map<int, int> distance = {{2,4}, {4,2}, {0,-1}, {3,-1}, {1,0},{5,-1}};
    REQUIRE(g.allShortestPaths(1).first == distance);
    map<int, int> number = {{2,2}, {4,1}};
    REQUIRE(g.allShortestPaths(1).second == number);

    map<int, int> distance2 = {{2,4},{5,2},{0,-1},{1,-1},{4,-1}, {3,0}};
    REQUIRE(g.allShortestPaths(3).first == distance2);
    map<int, int> number2 = {{2,1}, {5,1}};
    REQUIRE(g.allShortestPaths(3).second == number2);

    // Test Betweenness Centrality
    REQUIRE(g.betweennessCentrality("c") == 0);
    REQUIRE(g.betweennessCentrality("e") == double(1.0/3 + 1.0/2));
    REQUIRE(g.betweennessCentrality("f") == double(1.0 + 1.0/3));
}
// TEST_CASE("PUT YOUR TESTS HERE!!!", "[tag1][mytest]") {
//     // Feel free to use this to put your own test cases.
//     // Look at other test files for inspiration!
// }

/*****
TEST_CASE("Get Weight", "[weight=1][part=2]")
{
    Graph graph;
    graph.readFromAirports("../../data/test_airport.txt");
    graph.readFromRoutes("../../data/test_route.txt");
    REQUIRE(graph.getWeight(7)[6] >= graph.getWeight(8)[6]);
    REQUIRE(graph.getWeight(10)[6] * 3 == graph.getWeight(6)[10] * 2);
    REQUIRE(graph.getWeight(1)[2] == graph.getWeight(2)[1]);
}

****/