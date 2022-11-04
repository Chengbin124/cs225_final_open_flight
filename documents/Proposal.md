## Leading Question 

This project's objective is to examine the OpenFlights dataset and determine betweenness centrality by mapping the most significant airports. 

Airports will be mapped as vertices, and flights between airports will be drawn as directed edges. The distance between airports will be calculated using the latitude and longitude.

The number of connected components at each airport will be determined by traversing using BFS (Breadth First Search). The weight of the nodes will be determined by the combination of distance and the number of flights passing through. The Johnson’s algorithm will be used to figure out the shortest path, and calculate the betweenness centralities of each vertex in the graph. Finally, based on the betweenness centralities we get for each airport, we could draw a conclusion which airport is the most important one.

## Dataset Acquisition

The data will be collected from OpenFlights, an open source data set containing airports, train stations, and ferry terminals. We will be using the routes dataset which is composed of directional routes from one airport to another. We will also be using the airport search dataset for the longitude and latitude of each airport. As the dataset is very large, we will be considering mainly the airports mentioned in the routes dataset.


## Data Format

The dataset is expressed as a sequence of the airline, airline ID, source airport, source airport ID, destination airport, destination airport ID, codeshare, stops, and equipment, all separated by commas. For the sake of this project, we will only be using the airline ID, source airport ID, and destination airport ID from the dataset. The dataset is composed of 67663 routes between 3321 airports and 508 airlines. As the dataset is smaller compared to some other datasets, we are planning on using all of the data in the set. If the dataset proves to be too large, we can use a subset of the dataset which would be all the routes that have happened within a month.

From the airport search database, we will be using the longitude and latitude of each airport that is in the set of the routes database. The longitude and latitude will be parsed from common airports in both sets and stored in a node representing the airport. As there are fewer airports in the routes database, we will only be taking a subset of the airports in the airport search database. We can identify the same airport in both datasets by looking at the airport ID.

## Data Correction

The data will be parsed through a for loop going through each line of the data, using the split method to separate each piece of data into an array which will have specific spots used for the algorithms and when the data structure is created. In the dataset, if a certain element is missing, there will still be commas between each piece of information for each route, so by splitting each line by commas, the resulting array will always have the same size. Since we are only using the airline ID’s, source airport ID’s, and destination airport ID’s, we get the data at spots 1, 3, and 5 of the array for construction of the data structure. If any of these spots are missing, we can throw out that entry. We can check for missing entries or erroneous entries by comparing the size of the resulting array to the size it should be if each element was present and split correctly. If we detect these faulty entries, we will not add it to the data structure. Since we will need the information of every airline in order to find the betweenness centrality, we will not be discounting statistically outliers such as airlines that only have one route pointing to it.

In order to correct the airport search dataset, we will check if the longitude and latitude are in bounds. We will also check if the airports have the same longitude and latitude, only leaving one airport if they do.



## Data Storage

We will be storing the data in an edge-weighted directed graph. An edge-weighted directed graph is a set of nodes that point or direct to other nodes. Each directed edge will have a number, or weight attached to it. In the context of our project, the nodes will be the airports and the weights will be the distance between the airports divided by the number of routes. This type of dataset will be the most efficient to use with the space complexity being O(|V|^2). As for auxiliary datasets, we will be using an array to retrieve the data from the database because the data will be in a comma separated value format. An array would make it easier to create the directed graph. 


## Algorithm

We will use **Johnson’s Algorithm** to calculate the shortest path from one airport to another and to calculate the **betweenness centrality** of an airport. According to our data, we have more than 10000 airports but only 60000 routes, which indicates that our graph is a sparse graph. In this case Johnson’s Algorithm would be more efficient.

Our graph will be **edge-weighed directed** graph. We will use airports as our nodes, and whether there are routes from one airport to the other as a directed edge from one node to the other. The weight of each edge is calculated by the distance between two airports divided by how many routes from one to the other. Our algorithm supports loops, so we don’t need to worry about the loop cases.

For the first part, we will implement Johnson's algorithm: taking two nodes in the graph and calculating the shortest path from the first node to the second. We also modified the algorithm a little bit, so that we could store one of the shortest paths. The run time of this part is O(|V|^2log(|V|) + |V||E|).

For the second part, We need to calculate the betweenness centrality. We need to use the results from the first part to calculate the number of shortest paths from one airport to the other and from a to b through c. So we will modify our Johnson’s Algorithm again so that it could store this information. The run time of this part is O(|V|^2log(|V|) + |V||E|).

If we have more time, we can try using **Brande’s algorithm** to calculate the betweenness centrality. The runtime of this algorithm is also O(|V|^2log(|V|) + |V||E|).


## Timeline

11/4/22	Complete team contract, project proposal, Github repo

11/11/22	Data acquisition and correction, successful load data, basic graph formation

11/18/22	Finish traversal and shortest path algorithm

11/25/22	Finish betweenness centrality

12/5/22	Final debug, finish report, final presentation

