#include "graph.h"
#include <typeinfo>
#include <map>
#include <stack>

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
            vertices[info[0]] = i;
            convert[i] = info[1];
            i++;
            pair<long double, long double> a(stold(info[6]),stold(info[7]));
            airports[i] = a;
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

    for(unsigned k = 0; k < vertices.size();k++){
        vector<int> v;
        adjacency.push_back(v);
    }

    input.clear();
    input.seekg(0);
    while(getline(input, line)){
        vector<string> info = split(line);
        string sourceID = info[3];
        string destID = info[5];
        if (vertices.find(sourceID) != vertices.end() && vertices.find(destID) != vertices.end()) {
            adjacency[vertices[sourceID]].push_back(vertices[destID]);
        }
        
        //std::cout<<sourceID<<std::endl;
        /****
        if(sourceID == it->first.getID()){
            int destIndex = IDtoIndex(destID);
            if(destIndex != -1){
                v.push_back(destIndex);
            }
        }
        i++;
        if(i == max){
            for(unsigned p = 0; p < v.size();p++){
                if(IDtoIndex(it->first.getID()) < (int)adjacency.size()){
                    adjacency[IDtoIndex(it->first.getID())].push_back(v[p]);
                }
            }
            adjacency[IDtoIndex(it->first.getID())].erase(adjacency[IDtoIndex(it->first.getID())].begin());
            v.clear();
            printEdges(IDtoIndex(it->first.getID()));
            if(it == vertices.end()){
                break;
            }
            it++;
            v.push_back(IDtoIndex(it->first.getID()));
            i = 0;
            input.clear();
            input.seekg(0);
        }
        *****/
    }
    //printEdges();
}


Graph::Graph(string airports, string routes) {
    /* To be implement */
    readFromAirports(airports);
    readFromRoutes(routes);
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
        queue.pop();
        traversal.push_back(current);
        for (int i : adjacency.at(current)) {
            if (visited.find(i) == visited.end()) {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
    return traversal;
}

vector<int> Graph::BfsStep(int start) const {
    vector<int> traversal;
    std::map<int, bool> visited;
    queue<int> queue;
    queue.push(start);
    visited[start] = true;
    int counter;
    unsigned end = Bfs(start).size();
    printBfsStep(queue,1,0);
    printLoad(traversal.size(),end);
    while (!queue.empty()) {
        printBfsStep(queue,1,1);
        int current = queue.front();
        queue.pop();
        traversal.push_back(current);
        printLoad(traversal.size(),end);
        for (int i : adjacency.at(current)) {
            if (visited.find(i) == visited.end()) {
                queue.push(i);
                visited[i] = true;
                counter++;
            }
            if(counter != 0){
                printBfsStep(queue,counter,0);
                printLoad(traversal.size(),end);
                counter = 0;
            }
        }
    }
    return traversal;
}

//Helper function for printing out each step in BFS, 0 = green, 1 = red
void Graph::printBfsStep(queue<int> q, int counter, int color) const {
    stack<int> st;
    Color::Modifier red(Color::RED);
    Color::Modifier green(Color::GREEN);
    Color::Modifier blue(Color::BLUE);
    Color::Modifier def(Color::DEFAULT);
    while(!q.empty()){
        st.push(q.front());
        q.pop();
    }
    int i = 0;
    counter = abs(counter);
    while(!st.empty()){
        if(color == 1 && st.size() == 1){
            cout << red << convert.at(st.top());
        }
        else if(i < counter && color == 0){
            cout << green << convert.at(st.top());
            i++;
        }
        else{
            cout<< blue << convert.at(st.top());
        }
        st.pop();
        if(!st.empty()){
            cout << ", ";
        }
    }
    cout << def << endl;
}

void Graph::printLoad(unsigned current, unsigned max) const {
    double dcurrent = (double)current;
    unsigned progress = (dcurrent/max)*100;
    Color::Modifier green(Color::GREEN);
    Color::Modifier blue(Color::BLUE);
    Color::Modifier def(Color::DEFAULT);
    cout<< green << "[";
    for(unsigned i = 0; i < 100; i++){
        if(i < progress){
            cout << "=";
        }
        else if(i == progress){
            cout << ">";
        }
        else{
            cout << " ";
        }
    }
    cout << "] " << blue << progress << green << " %"<< endl;
    this_thread::sleep_for(chrono::seconds(1));
    for(int i =0; i < 100; i++){
        cout << def  << endl;
    }
}

/*helper function for test cases*/
int Graph::verticeCount()
{
    return vertices.size();
}

vector<string> Graph::getAdjacency(string id)
{
    int idx = vertices[id];
    vector<string> adj;
    for (int i : adjacency[idx])
    {
        adj.push_back(convert[i]);
    }
    return adj;
}