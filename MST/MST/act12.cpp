#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cmath>

using namespace std;

/*
 Diego Solis Higuera - A00827847
 Complejidad Prim O(V^2)
 */

struct Point {
    float x, y;
    Point(float x, float y) {
        this-> x  = x;
        this-> y = y;
    }
    
    float getDistance(Point b);
};

float Point::getDistance(Point b) {
    // Calcular distancia entre puntos
    return sqrt(pow(this->y - b.y, 2) + pow(this->x - b.x, 2));
}

struct Graph {
    int V, E; float costMSTPrim;
    vector< pair<float, pair<float, float>> > edges;
    vector<vector<pair<float, float>>> adjList;
    vector<pair<float, float>> selectedEdgesP; // Arcos seleccionados de prim
  
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        adjList.resize(V);
        costMSTPrim = 0;
    }
  
    void addEdge(float u, float v, float w) {
        edges.push_back({w, {u, v}});
        adjList[u].push_back({v,w});
    }
    
    void print();
    
    void load();
    
    void primMST();
};

void Graph::load(){
    
    vector<Point> points;
    float x, y;
    for (float i = 0; i < V; i++) {
        cin >> x >> y;
        points.push_back(Point(x,y));
    }
    
    for (float i = 0; i < points.size(); i++) {
        for (float j = i+1; j <= points.size()-1; j++) {
            float dist = points[i].getDistance(points[j]);
            addEdge(i, j, dist);
        }
    }
    
  
}


void Graph::primMST(){
// Aquí va tu código
    float selectedSource = 0;
    costMSTPrim = 0;
    unordered_set<float> selected;
    unordered_set<float> missing;
    selected.insert(0);
    for (float i = 1; i < V; i++) {
        missing.insert(i);
    }
    
    float connected = V-1;
    float minCost, selVertex;
    while (connected > 0) {
        minCost = INT_MAX;
        for(float it1 : selected) { // Para cada vertice del set selected
            for(auto it2=adjList[it1].begin(); it2 != adjList[it1].end(); it2++) {
                if (missing.find((*it2).first) != missing.end() && (*it2).second < minCost) {
                    minCost = (*it2).second;
                    selVertex = (*it2).first;
                }
            }
        }
        
        costMSTPrim += minCost;
        selected.insert(selVertex);
        missing.erase(selVertex);
        selectedEdgesP.push_back({selectedSource, selVertex});
        connected--;
    }
    
}

void Graph::print(){
    cout << "Adjacent List:" << endl;
    for (int i=0; i<V; i++){
        cout << " " << i << ": ";
        for (int j=0; j<adjList[i].size(); j++){
            cout << "(" << adjList[i][j].first << "," << adjList[i][j].second << ") ";
        }
        cout << endl;
    }
}

float roundNum(float num) {
    float tmp = (int) (num * 100 + .5);
    return (float) tmp / 100;
}

int main() {
    int n;
    cin >> n;
    Graph g(n, (n*(n-1))/2);
    
    g.load();
    //g.print();
    g.primMST();
    cout << roundNum(g.costMSTPrim) <<endl;
    
    return 0;
}

/*
3
1.0 1.0
2.0 2.0
2.0 4.0
*/
