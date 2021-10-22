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

typedef  pair<float, float> iPair;

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
    int V, E; float costMSTKruskal;
    vector< pair<float, pair<float, float>> > edges;
    vector<vector<pair<float, float>>> adjList;
    vector<pair<float, float>> selectedEdgesK; // Arcos seleccionados de prim
  
    Graph(int V, int E) {
        this->V = V;
        this->E = E;
        adjList.resize(V);
        costMSTKruskal = 0;
    }
  
    void addEdge(float u, float v, float w) {
        edges.push_back({w, {u, v}});
        adjList[u].push_back({v,w});
    }
    
    void print();
    
    void load();
    
    void kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;
  
    DisjointSets(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
        for (int i = 0; i <= n; i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
  
    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
  
    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
  
        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;
  
        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
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


void Graph::kruskalMST(){
// Aquí va tu código
    costMSTKruskal = 0;
    sort(edges.begin(), edges.end());
    DisjointSets ds(V);
    
    for (auto it : edges) {
        int u = it.second.first;
        int v = it.second.second;
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if(set_u != set_v) {
            ds.merge(u, v);
            costMSTKruskal += it.first;
            selectedEdgesK.push_back({u, v});
        }
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
    //g.print();
    g.kruskalMST();
    cout.precision(2);
    cout  << fixed << g.costMSTKruskal << endl;
    
    return 0;
}

/*
3
1.0 1.0
2.0 2.0
2.0 4.0
*/
