#include "graph.h"

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
        Airport* current = new Airport(stod(info[6]),stod(info[7]),info[0],info[1]);
        vertices.insert({pair<const Airport,int>(*current,i)});
        i++;
    }
}

void Graph::readFromRoutes(string file) {
    /* To be implement */
}

Graph::Graph(string airports, string routes) {
    /* To be implement */
}

vector<vector<int>> Graph::shortestPaths(int source) {
    /* To be implement */
    return vector<vector<int>>() ;
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
            current.push_back(s[i]);
        }
    }
    return toReturn;
}