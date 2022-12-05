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

TEST_CASE("Test BFS", "[weight=1][part=1]") {
    Graph g;
    g.readFromAirports("../../data/test_airport.txt");
    g.readFromRoutes("../../data/test_route.txt");

    vector<int> expected1{0, 1};

    vector<int> result1 = g.BfsStep(0);

    vector<int> result2 = g.BfsStep(6);

    vector<int> expected2{6,5,1,8,3,0};

    REQUIRE(result1.size() == expected1.size());

    REQUIRE(result2.size() == expected2.size());

    for (size_t i = 0; i < result1.size(); i++) {
        REQUIRE(result1[i] == expected1[i]);
    }

    for (size_t i = 0; i < result2.size(); i++) {
        REQUIRE(result2[i] == expected2[i]);
    }
}

// TEST_CASE("PUT YOUR TESTS HERE!!!", "[tag1][mytest]") {
//     // Feel free to use this to put your own test cases.
//     // Look at other test files for inspiration!
// }
