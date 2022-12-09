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

TEST_CASE("Get Weight", "[weight=1][part=2]")
{
    Graph graph;
    graph.readFromAirports("../../data/test_airport.txt");
    graph.readFromRoutes("../../data/test_route.txt");
    REQUIRE(graph.getWeight(7)[6] >= graph.getWeight(8)[6]);
    REQUIRE(graph.getWeight(10)[6] * 3 == graph.getWeight(6)[10] * 2);
    REQUIRE(graph.getWeight(1)[2] == graph.getWeight(2)[1]);
}

TEST_CASE("Graph with 4 vertices", "[weight=1][part=2]")
{
    Graph g;
    g.addVertex("a", 1);
    g.addVertex("b", 2);
    g.addVertex("c", 3);
    g.addVertex("d", 4);
    g.addEdge(1, 2);
    g.setWeight(1, 2, 2);
    g.addEdge(1, 4);
    g.setWeight(1, 4, 3);
    g.addEdge(2, 3);
    g.setWeight(2, 3, 5);
    g.addEdge(4, 3);
    g.setWeight(4, 3, 6);

    vector<string> ac = {"a", "b", "c"};
    REQUIRE(g.shortestPaths("a", "c") == ac);
}

TEST_CASE("Graph with 5 vertices", "[weight=1][part=2]")
{
    Graph g;
    g.addVertex("a", 1);
    g.addVertex("b", 2);
    g.addVertex("c", 3);
    g.addVertex("d", 4);
    g.addVertex("e", 5);
    g.addEdge(1, 2);
    g.setWeight(1, 2, 2);
    g.addEdge(1, 4);
    g.setWeight(1, 4, 3);
    g.addEdge(2, 3);
    g.setWeight(2, 3, 4);
    g.addEdge(4, 3);
    g.setWeight(4, 3, 6);
    g.addEdge(2, 5);
    g.setWeight(2, 5, 3);
    g.addEdge(5, 3);
    g.setWeight(5, 3, 2);
    vector<string> ac = {"a", "b", "c"};
    REQUIRE(g.shortestPaths("a", "c") == ac);
    vector<string> bc = {"b", "c"};
    REQUIRE(g.shortestPaths("b", "c") == bc);
}

TEST_CASE("Graph with 6 vertices", "[weight=1][part=2]")
{
    Graph g;
    g.addVertex("a", 1);
    g.addVertex("b", 2);
    g.addVertex("c", 3);
    g.addVertex("d", 4);
    g.addVertex("e", 5);
    g.addVertex("f", 6);
    g.addEdge(1, 2);
    g.setWeight(1, 2, 2);
    g.addEdge(1, 4);
    g.setWeight(1, 4, 3);
    g.addEdge(2, 3);
    g.setWeight(2, 3, 4);
    g.addEdge(4, 3);
    g.setWeight(4, 3, 6);
    g.addEdge(2, 5);
    g.setWeight(2, 5, 3);
    g.addEdge(5, 3);
    g.setWeight(5, 3, 2);
    g.addEdge(4, 6);
    g.setWeight(4, 6, 2);
    g.addEdge(3, 6);
    g.setWeight(3, 6, 3);
    vector<string> af = {"a", "d", "f"};
    REQUIRE(g.shortestPaths("a", "f") == af);
    vector<string> df = {"d", "f"};
    REQUIRE(g.shortestPaths("d", "f") == df);
    vector<string> bf = {"b", "c", "f"};
    REQUIRE(g.shortestPaths("b", "f") == bf);
}
// TEST_CASE("PUT YOUR TESTS HERE!!!", "[tag1][mytest]") {
//     // Feel free to use this to put your own test cases.
//     // Look at other test files for inspiration!
// }
