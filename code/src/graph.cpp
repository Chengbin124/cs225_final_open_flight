#include "graph.h"
#include <typeinfo>
#include <map>
#include <queue>

using namespace std;

void Graph::readFromAirports(string file) {
    /* To be implement */
    ifstream input;
    input.open(file);
    if(!input.is_open()){
        cout << "file error" << endl;
    }
    string line;
    int i = 0;
    while(getline(input, line)){
        vector<string> info = split(line);
        if(info.size() < 14){
            Airport* current = new Airport(stod(info[6]),stod(info[7]),info[0],info[1]);
            vertices.insert({pair<const Airport,int>(*current,i)});
            i++;
        }
        // else{
        //     cout << "type error" << endl;
        // }
    }
    //print test
    //printAirports();
}

void Graph::readFromRoutes(string file) {
    /* To be implement */
        ifstream input;
    input.open(file);
    if(!input.is_open()){
        cout << "file error" << endl;
    }
    string line;
    int i = 0;
    auto it = vertices.begin();
    vector<int> v;
    v.push_back(IDtoIndex(it->first.getID()));
    int max = 0;
    while(getline(input,line)){
        max++;
    }
    input.clear();
    input.seekg(0);
    while(getline(input, line)){
        vector<string> info = split(line);
        string sourceID = info[3];
        string destID = info[5];
        if(sourceID == it->first.getID()){
            int destIndex = IDtoIndex(destID);
            if(destIndex != -1){
                v.push_back(destIndex);
            }
        }
        i++;
        if(i == max){
            adjacency.push_back(v);
            v.clear();
            it++;
            v.push_back(IDtoIndex(it->first.getID()));
            i = 0;
            input.clear();
            input.seekg(0);
            printEdges();
        }
    }
}

Graph::Graph(string airports, string routes) {
    /* To be implement */
}
Graph::Graph(){

}

vector<vector<int>> Graph::shortestPaths(int source) {
    /* To be implement */
    vector<vector<int>> shortestPathList;
    vector<int> distance;
    vector<int> prev;
    std::map<int, bool> Q;
    for (unsigned i = 0; i<vertices.size(); i++) {
        distance[i] = -1;
        prev[i] = -1;
        Q[i] = true;
    }
    distance[source] = 0;
    while (true) {
        int k = -1;
        for (unsigned i = 0; i < vertices.size(); i++) {
            if (Q[i] && (k >= 0) && (distance[i] < distance[k]) && distance[i] >= 0) {
                k = i;
            } else if ((k <= 0) && Q[i] && distance[i] >= 0) {
                k = i;
            }
        }
        if (k == -1) {
            break;
        }
        Q[k] = false;
        for (auto j: adjacency[k]) {
            if (Q[j]) {
                int alt = distance[k] + weights[k][j];
                if (alt < distance[j] || distance[j] == -1) {
                    distance[j] = alt;
                    prev[j] = k;
                }
            }
        }
    }
    int target = 0;
    for (unsigned i = 0; i < vertices.size(); i++) {
        vector<int> shortestPath;
        int u = target;
        if (prev[u] != -1 || u == source) {
            while(u != -1) {
                if (shortestPath.empty()) {
                    shortestPath.push_back(u);
                } else {
                    shortestPath.insert(shortestPath.begin(), u);
                }
                u = prev[u];
            }
        }
        shortestPathList.push_back(shortestPath);
        target++;
    }
    return shortestPathList;
}

vector<string> Graph::shortestPaths(string s1, string s2) {
    /* To be implement */
    return vector<string>() ;
}

map<int, vector<vector<int>>> Graph::allShortestPaths(int source) {
    /* To be implement */
    return map<int, vector<vector<int>>>();
}

int Graph::countShortestPaths(string s1, string s2) {
    /* To be implement */
    return 0;
}

int Graph::countShortestPaths(string s1, string s2, string s3) {
    /* To be implement */
    return 0;
}

double Graph::betweennessCentrality(string s) {
    /* To be implement */
    return 0.0;
}

vector<string> Graph::split(string s){
    vector<string> toReturn;
    string current;
    for(unsigned i =0; i < s.size(); i++){
        if(s[i] == ','){
            toReturn.push_back(current);
            current.clear();
        }
        else{
            if(s[i] != '\"'){
            current.push_back(s[i]);
            }
        }
    }
    return toReturn;
}


vector<int> Graph::Bfs(int start) const {
    vector<int> traversal;
    std::map<int, bool> visited;
    queue<int> queue;
    queue.push(start);
    visited[start] = true;
    while (!queue.empty()) {
        int current = queue.front();
        traversal.push_back(current);
        for (int i : adjacency.at(current)) {
            if (visited.find(i) != visited.end()) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
    return traversal;
}