//
//  act12.cpp
//  MST
//
//  Created by Diego Solis on 10/19/21.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cmath>

using namespace std;
  
typedef  pair<double, double> iPair;


// Complejidad Prim O(V^2)

struct Point {
    double x, y;
    Point(double x, double y) {
        this-> x  = x;
        this-> y = y;
    }
    
    double getDistance(Point b);
};

double Point::getDistance(Point b) {
    // Calcular distancia entre puntos
    return sqrt(pow(this->y - b.y, 2) + pow(this->x - b.x, 2));
}

struct Graph {
    int V, E, costMSTKruskal, costMSTPrim, costMSTKrustal;
    vector< pair<double, pair<double, double>> > edges;
    vector<vector<pair<double, double>>> adjList;
    vector<pair<double, double>> selectedEdgesP; // Arcos seleccionados de prim
  
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        adjList.resize(V);
        costMSTPrim = 0;
    }
  
    void addEdge(double u, double v, double w) {
        edges.push_back({w, {u, v}});
        adjList[u].push_back({v,w});
    }
    
    void print();
    
    void load();
    
    void primMST();
};

void Graph::load(){
    
    vector<Point> points;
    double x, y;
    for (double i = 0; i < V; i++) {
        cin >> x >> y;
        points.push_back(Point(x,y));
    }
    
    for (double i = 0; i < points.size(); i++) {
        for (double j = i+1; j <= points.size()-1; j++) {
            double dist = points[i].getDistance(points[j]);
            addEdge(i, j, dist);
        }
    }
    
  
}


void Graph::primMST(){
// Aquí va tu código
    double selectedSource = 0;
    costMSTPrim = 0;
    unordered_set<double> selected;
    unordered_set<double> missing;
    selected.insert(0);
    for (double i = 1; i < V; i++) {
        missing.insert(i);
    }
    
    double connected = V-1;
    double minCost, selVertex;
    while (connected > 0) {
        minCost = INT_MAX;
        for(auto it1 : selected) { // Para cada vertice del set selected
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


int main() {
    int n;
    cin >> n;
    Graph g(n, (n*(n-1))/2);
    
    g.load();
    g.print();
    g.primMST();
    cout << "Costo Total del MST(prim) es: " << g.costMSTPrim<<endl;
    
    return 0;
}

/*
3
1.0 1.0
2.0 2.0
2.0 4.0
*/
