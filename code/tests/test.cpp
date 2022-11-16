#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "graph.h"
#include "airport.h"

using namespace std;

TEST_CASE("Airport distance", "[weight=1][part=1]") {
    Airport a = {10,20,"1","a"}; 
    Airport b = {10,30,"2","b"};
    Airport c = {0,40,"3","c"};
    double a2b = 600;
    double a2c = 1305;
    double b2c = 774;
    REQUIRE(a.calculateDistance(b)==a2b);
    REQUIRE(a.calculateDistance(c)==a2c);
    REQUIRE(b.calculateDistance(c)==b2c);
}

// TEST_CASE("Graph constructor", "[weight=1][part=1]") {
//     cout<<"need add route file to test!"<<endl;
//     cout<<"also need function to get all airports"<<endl;
//     Graph() g;
//     g = Graph("sample_airports.dat.txt","routfile");
//     REQUIRE(g.vertices) = sample_airports.size();

// }

// TEST_CASE("PUT YOUR TESTS HERE!!!", "[tag1][mytest]") {
//     // Feel free to use this to put your own test cases.
//     // Look at other test files for inspiration!
// }
