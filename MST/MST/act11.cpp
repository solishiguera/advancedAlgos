//
//  act11.cpp
//  MST
//
//  Created by Diego Solis on 10/22/21.
//

#include <stdio.h>
#include <iostream>
#include <climits>
#include <queue>

#define MAX 21

using namespace std;

struct Nodo{
    int niv;
    int costoAcum;
    int costoPos;
    int verticeAnterior;
    int verticeActual;
    bool visitados[MAX];
    bool operator<(const Nodo &otro) const{ // priority queue tenga la prioridad de menor costo posible
        return costoPos>=otro.costoPos;
    }
};

void iniciaMat(int matAdj[MAX][MAX]){
    for(int i=0; i<MAX; i++){
        matAdj[i][i]=0;
        for(int j=i+1; j<MAX; j++){
            matAdj[i][j] = matAdj[j][i] = INT_MAX;
        }
    }
}

void leerArcos(int matAdj[MAX][MAX], int m){
    int c;
    char a, b;
    for(int i=0; i<m; i++){
        cin >> a >> b >> c;
        matAdj[a-'A'][b-'A'] = matAdj[b-'A'][a-'A']=c;
    }
}

void calculaCostoPosible(Nodo &nodoActual, int matAdj[MAX][MAX], int n){
    nodoActual.costoPos = nodoActual.costoAcum;
    int costoObtenido;
    for (int i=1; i<=n; i++){
        costoObtenido = INT_MAX;
        // No he visitado al nodo i
        if (!nodoActual.visitados[i] || i == nodoActual.verticeActual) {
            // no lo he visitado
            if(!nodoActual.visitados[i]){
                for (int j=1; j<=n; j++){
                    if (i != j && (!nodoActual.visitados[j] || j == 1)){
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
            } else { // soy el último visitado
                for (int j=1; j<=n; j++){
                    if (!nodoActual.visitados[j]) {
                        costoObtenido = min(costoObtenido, matAdj[i][j]);
                    }
                }
            }
            nodoActual.costoPos += costoObtenido;
        }
    }
}

int tsp(int matAdj[MAX][MAX], int n){
    int costoOptimo = INT_MAX;
    Nodo raiz;
    raiz.niv = 0;
    raiz.costoAcum = 0;
    raiz.verticeActual = 1;
    raiz.verticeAnterior = 0;
    raiz.visitados[1] = true; // garantizar que todos los demas tengan false
    calculaCostoPosible(raiz, matAdj, n);
    priority_queue<Nodo> pq;
    pq.push(raiz);
    while (!pq.empty()) {
        raiz = pq.top();
        pq.pop();
        int vAct = raiz.verticeActual;
        if(raiz.costoPos < costoOptimo) {
            for (int i = 0; i <= n; i++) {
                if (!raiz.visitados[i] && matAdj[i][vAct] != INT_MAX) { // Revisar esto !!!
                    Nodo tmp = raiz;
                    tmp.niv += 1;
                    tmp.costoAcum += matAdj[i][vAct];
                    tmp.verticeActual = 1;
                    tmp.verticeAnterior = 0;
                    tmp.visitados[1] = true; // garantizar que todos los demas tengan false
                    
                    if (tmp.niv == n) {
                        if (matAdj[vAct][1] != INT_MAX) {
                            int costoReal = tmp.costoAcum + matAdj[vAct][1];
                            costoOptimo = min(costoReal, costoOptimo);
                        }
                    } else {
                        calculaCostoPosible(tmp, matAdj, n);
                        if (tmp.costoPos < costoOptimo) {
                            pq.push(tmp);
                        }
                    }
                }
            }
        }
    }
    
    return costoOptimo;
}

int main(){
    // n = cantidad de nodos
    // m = cantidad de arcos
    int n, m;
    cin >> n >> m;
    int matAdj[MAX][MAX]; // asumimos que es base 1 A=1, B=2, C=3...
    iniciaMat(matAdj);
    leerArcos(matAdj, m);
    (tsp(matAdj, n) != INT_MAX) ? cout << tsp(matAdj, n) << endl : cout << "INF" << endl;
}
