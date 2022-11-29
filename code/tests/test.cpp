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

TEST_CASE("Graph constructor", "[weight=1][part=1]")
{
    Graph graph;
    graph = Graph("../../data/test_airport.txt", "../../data/test_route.txt");
    int airports = graph.verticeCount();
    REQUIRE(airports == 10);
    // Airport a = {10, 100, "1", "a"};
    // Airport e = {50, 140, "5", "e"};
    // Airport g = {-20, 20, "7", "g"};

    REQUIRE(graph.getAdjacency("1").size() == 1);
    REQUIRE(graph.getAdjacency("1")[0] == "2");
    REQUIRE(graph.getAdjacency("5").size() == 0);
    REQUIRE(graph.getAdjacency("7").size() == 5);
    REQUIRE(graph.getAdjacency("7")[3] == "6");
}

// TEST_CASE("PUT YOUR TESTS HERE!!!", "[tag1][mytest]") {
//     // Feel free to use this to put your own test cases.
//     // Look at other test files for inspiration!
// }
