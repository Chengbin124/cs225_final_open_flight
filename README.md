# Open Flight
A program designed to find the shortest flights for passengers and to record the busiest airports.
![](./documents/plotted_airports.png)

## File Structure
- code
  - entry
    - `main.cpp` - The code to run the program for the user.
  - lib
    - Contains external classes to help with the development of the code.
  - src
    - `color.h` - For the graphical output of our program.
    - `graph.cpp` - The main processes of the program; read files, create the connected graph, find the shortest paths between airports using Breadth-First Search (BFS) and betweeness centrality.
  - tests
    - `test.cpp` - Contains all the test cases to check if the program is working correctly.
- data
  - `Information.md` - Describes how the data should be structured (taken from OpenFLights website).
  - `airports.dat.txt` - Airport data for the program.
  - `sample_airports.dat.txt`, `test_airport.txt` - Sample airport data for tests.
  - `routes.dat.txt` - Airline route data for the program.
  - `test_route.txt`- Sample route data for tests.
- documents
  - Contains the written report and the presentation video.

## Running Instructions
### Defining input data
Our program needs two data files to run: airport data and route data. The structure for each are as follows:
  - Airport data - should be a `.txt` file with each field in a line being separated by a comma, with strings in quotations:
    - `Airport ID,Airport name,City,Country,IATA,ICAO,Latitude,Longitude,Altitude,Timezone,DST,Type,Source`
    - The program only looks at the airport ID, airport name, latitude, and the longitude of each line of data, but adding NULL to unknown fields is required.
    - For descriptions of each of these data fields, see `data/Information.md`.
  - Route data - should be a `.txt` file with each field in a line being separated by a comma, with strings in quotations:
    - `Airline,Airline ID,Source airport,Destination airport,Destination airport ID,Codeshare,Stops,Equipment`
    - The program only looks at the airline, airline ID, source airport, destination airport, and the destination airport ID of each line of data, but adding NULL to unknown fields is required.
    - For descriptions of each of these data fields, see `data/Information.md`.

Because we already have an established database, there is no need for the user to input their own data for airports or routes.

### Output Locations and How to Use
The program runs on the terminal, so most user interaction and output will be done in the terminal. After making and running `./main`, the user will be prompted to enter their desired source airport and destination airport. The program will then output the shortest and most optimal airline route between the two airports. There will also be a graphical output to show what the route might look like.

### Test Suites
`test.cpp` is the only file that houses our test cases. To use it, the user has to `make test` and then run `./test`. The tests check on a majority of our functions, including:
  - Reading files
  - Contructing the weighted graph for airports
  - The functionality of our Breadth-First Search algorithm
  - Testing if the weights on our graph are as expected
