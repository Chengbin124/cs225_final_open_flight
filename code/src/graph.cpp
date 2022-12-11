#include "graph.h"
#include <typeinfo>
#include <map>
#include <stack>
#include <cmath>
#include <queue>
#include <functional>
#include <limits.h>

using namespace std;

void Graph::readFromAirports(string file)
{
    ifstream input;
    input.open(file);
    if (!input.is_open())
    {
        cout << "file error" << endl;
    }
    string line;
    int i = 0;
    while (getline(input, line))
    {
        vector<string> info = split(line);
        if (info.size() < 14)
        {
            vertices[info[0]] = i;
            convert[i] = info[1];
            nameToidx[info[1]] = i;
            pair<long double, long double> a(stold(info[6]), stold(info[7]));
            airports[i] = a;
            i++;
        }
    }
}

void Graph::readFromRoutes(string file)
{
    ifstream input;
    input.open(file);
    if (!input.is_open())
    {
        cout << "file error" << endl;
    }
    string line;

    for (unsigned k = 0; k < vertices.size(); k++)
    {
        vector<int> v;
        adjacency.push_back(v);
        weights.push_back(map<int, int>());
    }

    input.clear();
    input.seekg(0);
    while (getline(input, line))
    {
        vector<string> info = split(line);
        string sourceID = info[3];
        string destID = info[5];
        if (vertices.find(sourceID) != vertices.end() && vertices.find(destID) != vertices.end())
        {
            adjacency[vertices[sourceID]].push_back(vertices[destID]);
        }
    }
    for (unsigned i = 0; i < vertices.size(); i++) {
        for (auto j: adjacency.at(i)) {
            if (weights[i].find(j) == weights[i].end()) {
                weights[i][j] = 1;
            } else {
                weights[i][j] += 1;
            }
        }
    }
    for (unsigned i = 0; i < vertices.size(); i++) {
        for (auto ele : weights.at(i)) {
            weights[i][ele.first] = round(calculateDistance(airports[i], airports[ele.first]) / ele.second);
        }
    }
}

Graph::Graph(string airports, string routes)
{
    readFromAirports(airports);
    readFromRoutes(routes);
}
Graph::Graph()
{
}

vector<vector<int>> Graph::shortestPaths(int source)
{
    vector<vector<int>> shortestPathList;
    vector<int> distance;
    vector<int> prev;
    std::map<int, bool> Q;
    for (unsigned i = 0; i < vertices.size(); i++)
    {
        distance.push_back(-1);
        prev.push_back(-1);
        Q[i] = true;
    }
    distance[source] = 0;
    while (true)
    {
        int k = -1;
        for (unsigned i = 0; i < vertices.size(); i++)
        {
            if (Q[i] && (k >= 0) && (distance[i] < distance[k]) && distance[i] >= 0)
            {
                k = i;
            }
            else if ((k <= 0) && Q[i] && distance[i] >= 0)
            {
                k = i;
            }
        }
        if (k == -1)
        {
            break;
        }
        Q[k] = false;
        for (auto j : adjacency[k])
        {
            if (Q[j])
            {
                int alt = distance[k] + weights[k][j];
                if (alt < distance[j] || distance[j] == -1)
                {
                    distance[j] = alt;
                    prev[j] = k;
                }
            }
        }
    }
    int target = 0;
    for (unsigned i = 0; i < vertices.size(); i++)
    {
        vector<int> shortestPath;
        int u = target;
        if (prev[u] != -1 || u == source)
        {
            while (u != -1)
            {
                if (shortestPath.empty())
                {
                    shortestPath.push_back(u);
                }
                else
                {
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

vector<string> Graph::shortestPaths(string s1, string s2)
{
    vector<int> paths = shortestPaths(vertices[s1]).at(vertices[s2]);

    vector<string> returnPath;
    for (auto i : paths)
    {
        string s = convert[i];
        returnPath.push_back(s);
    }
    return returnPath;
}

std::pair<map<int, int>, map<int, int>> Graph::allShortestPaths(int source)
{
    map<int, int> numshortestPath;
    map<int, int> distance;
    map<int, set<int>> prev;
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int,int>> > Q;
    for (unsigned i = 0; i < vertices.size(); i++)
    {
        distance[i] = INT_MAX;
    }
    distance[source] = 0;
    Q.push(make_pair(0, source));
    while (!Q.empty())
    {
        int k = Q.top().second;
        Q.pop();
        for (auto j : adjacency[k])
        {
                int alt = distance[k] + weights[k][j];
                if (alt < distance[j])
                {
                    distance[j] = alt;
                    set<int> prevSet;
                    prevSet.insert(k);
                    prev[j] = prevSet;
                    Q.push(make_pair(distance[j], j));

                } else if (alt == distance[j] && distance[j] != INT_MAX) {
                        prev[j].insert(k);
                }
                    
        }
    }

    int target = 0;
    for (unsigned i = 0; i < vertices.size(); i++)
    {
        int u = target;
        if (prev.find(u) != prev.end())
        {
            int count = 0;
            countPaths(source, u, prev, count);
            if (count > 0 ){
                numshortestPath[u] = count;
            }
        }
        target++;
    }
    return std::pair<map<int, int>, map<int, int>>(distance, numshortestPath);
}

void Graph::countPaths(int source, int target, map<int, set<int>> &prev, int &count)
{
    if (target == source)
    {
        count++;
        return;
    }


    for (auto prevNode : prev[target])
    {
        if (prevNode == target) {
            break;
        }
        countPaths(source, prevNode, prev, count);
    }
}

double Graph::betweennessCentrality(string s)
{
    if (nameToidx.find(s) == nameToidx.end()) {
        cout<<"Your airport does not exsits"<<endl;
        return -1;
    }
    int indx = nameToidx[s];
    double bc = 0.0;
    std::pair<map<int, int>, map<int, int>> asp = allShortestPaths(indx); 
    for (int i = 0; i < verticeCount(); i++)
    {
        if (i == 1500) {
            cout<< "Loading.... 25 percent done! "<<endl;
        }
        if (i == 3000) {
            cout<<"Loading.... 50 percent done! "<<endl;
        }
        if (i == 4500) {
            cout<<"Loading.... 75 percent done! "<<endl;
        }
        if (i == 6700) {
            cout<<"Loading.... Almost done! "<<endl;
        }
        if (i != indx)
        {
            std::pair<map<int, int>, map<int, int>> asp2 = allShortestPaths(i);
            for (auto pairNum : asp2.second)
            {
                int j = pairNum.first;
                if (indx != j && asp2.second.find(indx) != asp2.second.end() && asp.second.find(j) != asp.second.end())
                {
                    if (((asp.first[j] + asp2.first[indx]) == asp2.first[j]) && asp.first[j] != INT_MAX)
                    {
                        bc += double(asp.second[j] * asp2.second[indx]) / double(pairNum.second);
                    }
                }
            }
        }
    }
    return bc;
}

vector<string> Graph::split(string s)
{
    vector<string> toReturn;
    string current;
    for (unsigned i = 0; i < s.size(); i++)
    {
        if (s[i] == ',')
        {
            toReturn.push_back(current);
            current.clear();
        }
        else
        {
            if (s[i] != '\"')
            {
                current.push_back(s[i]);
            }
        }
    }
    return toReturn;
}

vector<int> Graph::Bfs(int start) const
{
    vector<int> traversal;
    std::map<int, bool> visited;
    queue<int> queue;
    queue.push(start);
    visited[start] = true;
    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();
        traversal.push_back(current);
        for (int i : adjacency.at(current))
        {
            if (visited.find(i) == visited.end())
            {
                queue.push(i);
                visited[i] = true;
            }
        }
    }
    return traversal;
}

vector<int> Graph::BfsStep(int start) const
{
    vector<int> traversal;
    std::map<int, bool> visited;
    queue<int> queue;
    queue.push(start);
    visited[start] = true;
    int counter;
    unsigned end = Bfs(start).size();
    printBfsStep(queue, 1, 0);
    printLoad(traversal.size(), end);
    while (!queue.empty())
    {
        printBfsStep(queue, 1, 1);
        int current = queue.front();
        queue.pop();
        traversal.push_back(current);
        printLoad(traversal.size(), end);
        for (int i : adjacency.at(current))
        {
            if (visited.find(i) == visited.end())
            {
                queue.push(i);
                visited[i] = true;
                counter++;
            }
            if (counter != 0)
            {
                printBfsStep(queue, counter, 0);
                printLoad(traversal.size(), end);
                counter = 0;
            }
        }
    }
    return traversal;
}

void Graph::printBfsStep(queue<int> q, int counter, int color) const
{
    stack<int> st;
    Color::Modifier red(Color::RED);
    Color::Modifier green(Color::GREEN);
    Color::Modifier blue(Color::BLUE);
    Color::Modifier def(Color::DEFAULT);
    while (!q.empty())
    {
        st.push(q.front());
        q.pop();
    }
    int i = 0;
    counter = abs(counter);
    while (!st.empty())
    {
        if (color == 1 && st.size() == 1)
        {
            cout << red << convert.at(st.top());
        }
        else if (i < counter && color == 0)
        {
            cout << green << convert.at(st.top());
            i++;
        }
        else
        {
            cout << blue << convert.at(st.top());
        }
        st.pop();
        if (!st.empty())
        {
            cout << ", ";
        }
    }
    cout << def << endl;
}

void Graph::printLoad(unsigned current, unsigned max) const
{
    double dcurrent = (double)current;
    unsigned progress = (dcurrent / max) * 100;
    Color::Modifier green(Color::GREEN);
    Color::Modifier blue(Color::BLUE);
    Color::Modifier def(Color::DEFAULT);
    cout << green << "[";
    for (unsigned i = 0; i < 100; i++)
    {
        if (i < progress)
        {
            cout << "=";
        }
        else if (i == progress)
        {
            cout << ">";
        }
        else
        {
            cout << " ";
        }
    }
    cout << "] " << blue << progress << green << " %" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    for (int i = 0; i < 100; i++)
    {
        cout << def << endl;
    }
}

void Graph::printAirports()
    {
        int counter = 0;
        map<int, string>::iterator it;
        for (it = convert.begin(); it != convert.end(); it++)
        {
            cout << it->second << endl;
            counter++;
        }
        cout << counter << " " << vertices.size() << endl;
    }

void Graph::printEdges() const {
        int count = 0;

        for (int i = 0; i < verticeCount(); i++)
        {
            if (adjacency.at(i).size() >= 1)
            {
                cout << "Airport " << convert.at(i) << " has flight to ";
                for (unsigned j = 0; j < adjacency.at(i).size(); j++)
                {
                    cout << convert.at(adjacency.at(i)[j]) << ", ";
                    count++;
                }
                cout << endl;
            }
        }
        cout << count << endl;

}

void Graph::printWeight() const {
    for (unsigned i = 0; i <vertices.size(); i++) {
        for (auto ele : weights.at(i)) {
            cout<<convert.at(i) << " To " << convert.at(ele.first) << " has weights " << ele.second<<endl;
        }
    }
}

void Graph::printMap() const {
        Image worldMap;
        worldMap.readFromFile("../map.png");
        Image dot;
        dot.readFromFile("../dot.png");
        dot.scale(3, 3);
        StickerSheet *airportMap = new StickerSheet(worldMap, airports.size());
        int middleX = worldMap.width() / 2;
        int middleY = worldMap.height() / 2;
        int xcord;
        int ycord;
        double radius = worldMap.width() / (2 * 3.14);
        for (unsigned i = 0; i < airports.size() * 95 / 100; i++)
        {
            if (airports.find(i) != airports.end())
            {
                long double latRad = toRadians(airports.at(i).first);
                if (tan((3.14 / 4) + (latRad / 2)) < 0)
                {
                    continue;
                }
                double mercN = log(tan((3.14 / 4) + (latRad / 2))) * radius;
                long double longRad = toRadians(airports.at(i).second + 180);
                double x = longRad * radius;
                double y = worldMap.height() / 2 - mercN;
                airportMap->addSticker(dot, (int)x, (int)y);
                cout << convert.at(i) << endl;
            }
        }
        Image output = airportMap->render();
        output.writeToFile("../myImage.png");
        cout << "printed map" << endl;
        delete (airportMap);
    }


int Graph::verticeCount() const
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

map<int, int> Graph::getWeight(int id)
{
    return weights[id];
}

void Graph::addVertex(string name, int id)
{
    vertices[name] = id;
    convert[id] = name;
    nameToidx[name] = id;
    adjacency.push_back(vector<int>());
    weights.push_back(map<int, int>());
}

void Graph::addEdge(int src, int dest)
{
    adjacency[src].push_back(dest);
}

void Graph::setWeight(int src, int dest, int weight)
{
    weights[src][dest] = weight;
}

long double Graph::calculateDistance(pair<long double, long double> a, pair<long double, long double> b)
{
    long double dlat = toRadians(a.second) - toRadians(b.second);
    long double dlong = toRadians(a.first) - toRadians(b.first);
    long double ans = pow(sin(dlat / 2), 2) + cos(toRadians(b.second)) * cos(this->toRadians(a.second)) * pow(sin(dlong / 2), 2);
    ans = 2.0 * asin(sqrt(ans));
    return ans * 3956;
}

long double Graph::toRadians(long double a) const
{
    long double rad = (M_PI) / 180;
    return a * rad;
}
