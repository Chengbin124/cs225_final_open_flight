# Written Report
Our team wrote a program that examines the OpenFlights dataset and determines the betweenness centrality by mapping the most significant airports.

## Output and Correctness
We used an edge-weighted directed graph to store our data. In order to test if our graph was being read and implemented correctly, we tested:
- Reading files
- Constructing the graph (Vertices and adjacencies)

### Algorithms
- Breadth-First Search (BFS)
Our BFS algorithm 

  
- Shortest path using Johnson's algorithm

  Johnson's algorithm does output the expected results, however

  We tested multiple instances of graphs to check if this algorithm worked, including:
  - 4-vertex graph: tested if the path is correct
  - 5-vertex graph: tested if the path is correct
  - 6-vertex graph: tested if the path is correct, also tested if the shortest distance is recorded correctly and if the "steps" are recorded correctly
  
- Brande's algorithm for betweenness centrality

  Our implementation of Brande's algorithm does output the expected values, however the runtime of this algorithm is slower than our expected runtime of O(|V|^2log(|V|) + |V||E|)
  

## Leading Question
We wanted to create a program that determines the betweenness centrality of a group of airports.
