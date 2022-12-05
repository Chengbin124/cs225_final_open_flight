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
  - Contains the written report and the presentation video.

## Running Instructions
### Defining input data
Our program needs two data files to run: airport data and route data. The structure for each are as follows:
  - Airport data - should be a `.txt` file with each line structured like so, with strings in quotations:
    - Airport ID,Airport name,City,Country,IATA,ICAO,Latitude,Longitude,Altitude,Timezone,DST,Type,Source
    - The program only looks at the airport ID, airport name, latitude, and the longitude of each line of data, but adding NULL to unknown fields is required.
    - For descriptions of each of these data fields, see `data/Information.md`.
  - Route data - should be a `.txt` file with each line structured like so, with strings in quotations:
    - Airline,Airline ID,Source airport,Destination airport,Destination airport ID,Codeshare,Stops,Equipment
    - The program only looks at the airline, airline ID, source airport, destination airport, and the destination airport ID of each line of data, but adding NULL to unknown fields is required.
    - For descriptions of each of these data fields, see `data/Information.md`.
Because we already have an established database, there is no need for the user to input their own data for airports or routes.

### Output Locations
The program runs on the terminal, so most user interaction and output will be done in the terminal.


