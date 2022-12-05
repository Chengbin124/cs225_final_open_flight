# cs225_open_flight
A program designed to find the shortest flights for passengers.


## File Structure
- code
  - entry
    - `main.cpp` - The code to run the program for the user.
  - lib
    - Contains external classes to help with the development of the code.
  - src
    - `airport.cpp` - Creates an airport object, and calculates the distance between two airports.
    - `color.h` - For the graphical output of our program.
    - `graph.cpp` - The main processes of the program; read files, create the connected graph, find the shortest paths between airports using BFS and betweeness centrality.
  - tests
    - `test.cpp` - Contains all the test cases to check if the program is working correctly.
- data
  - `Information.md` - Describes how the data should be structured (taken from OpenFLights website).
  - `airports.dat.txt` - Airport data for the program.
  - `sample_airports.dat.txt`, `test_airport.txt` - Sample airport data for tests.
  - `routes.dat.txt` - Airline route data for the program.
  - `test_route.txt`- Sample route data for tests.
- documents
  - Further documentation for our project (project contract, proposal, etc.)
