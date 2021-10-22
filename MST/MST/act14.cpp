//
//  act14.cpp
//  MST
//
//  Created by Diego Solis on 10/22/21.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/*
 Diego Solis Higuera - A00827847
 Complejidad: O(|V|^2 |E|)
 */

struct Edge{
    int v;
    long long flow;
    long long C;
    int rev ;
};


class Graph{
    int V;
    int *level ;
    vector< Edge > *adj;
public :
    Graph(int V){
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }

    void addEdge(int u, int v, long long C){
        int tam = (int) adj[v].size();
        Edge a{v, 0, C, tam};
        tam = (int) adj[u].size();
        Edge b{u, 0, 0, tam};
        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }
    bool BFS(int s, int t);
    long long sendFlow(int s, long long flow, int t, int ptr[]);
    long long DinicMaxflow(int s, int t);
};

bool Graph::BFS(int s, int t){
    for (int i = 0 ; i < V ; i++)
        level[i] = -1;
    level[s] = 0;
    queue< int > q;
    q.push(s);

    vector<Edge>::iterator i ;
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for (i = adj[u].begin(); i != adj[u].end(); i++){
            Edge &e = *i;
            if (level[e.v] < 0  && e.flow < e.C){
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
    }
    return level[t] < 0 ? false : true ;
}

long long Graph::sendFlow(int u, long long flow, int t, int start[]){
    // Sink reached
    if (u == t){
        return flow;
    }
    for (  ; start[u] < adj[u].size(); start[u]++){
        Edge &e = adj[u][start[u]];
        if (level[e.v] == level[u]+1 && e.flow < e.C){
            long long curr_flow = min(flow, e.C - e.flow);
            //int curr_flow = flow < (e.C - e.flow) ? flow : (e.C - e.flow);
            long long temp_flow = sendFlow(e.v, curr_flow, t, start);
            if (temp_flow > 0){
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

long long Graph::DinicMaxflow(int s, int t){
    // Corner case
    if (s == t)
        return -1;

    long long total = 0;
    while (BFS(s, t) == true){
        int *start = new int[V+1] {0};
        while (long long flow = sendFlow(s, INT_MAX, t, start)){
            total += flow;
        }
    }
    return total;
}

int main(){
    int n, m, a, b;
    long long c;
    cin >> n >> m;
    Graph g(n);
    for (int i=0; i<m; i++){
        cin >> a >> b >> c;
        g.addEdge(a-1, b-1, c);
    }
    
    cout << "The maximum speed is " << g.DinicMaxflow(0, n - 1) << "." << endl;
    return 0;
}
/*
7 11
1 7
1 2 10
1 3 15
1 4 20
2 3  5
2 5 10
3 4 10
3 5 12
4 5 10
4 6 10
5 7 50
6 7 10


4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3
*/
