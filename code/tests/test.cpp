#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "graph.h"

using namespace std;

TEST_CASE("Airport distance", "[weight=1][part=1]")
{
    Airport a = {10, 20, "1", "a"};
    Airport b = {10, 30, "2", "b"};
    Airport c = {0, 40, "3", "c"};
    double a2b = 600;
    double a2c = 1305;
    double b2c = 774;
    REQUIRE(a.calculateDistance(b) == a2b);
    REQUIRE(a.calculateDistance(c) == a2c);
    REQUIRE(b.calculateDistance(c) == b2c);
}

TEST_CASE("Graph constructor", "[weight=1][part=1]")
{
    Graph g;
    g = Graph("../../data/test_airport.txt", "../../data/test_route.txt");
    // REQUIRE(g.vertices) = sample_airports.size();
}

// TEST_CASE("PUT YOUR TESTS HERE!!!", "[tag1][mytest]") {
//     // Feel free to use this to put your own test cases.
//     // Look at other test files for inspiration!
// }
