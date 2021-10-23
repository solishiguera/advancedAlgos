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
    bool operator<(const Nodo &otro) const{ // para que la priority queue tenga la prioridad
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
    for(int i=1; i<=n; i++){
        costoObtenido = INT_MAX;
        //No he visitado al nodo i
        if(!nodoActual.visitados[i] || i == nodoActual.verticeActual){
            //no lo he visitado
            if(!nodoActual.visitados[i]){
                for(int j=1; j<=n; j++){
                    if( i != j && (!nodoActual.visitados[j] || j == 1)){
                        costoObtenido = min(costoObtenido, matAdj[i-1][j-1]);
                    }
                }
            } else {  //soy el ultimo visitado
                for(int j=1; j<=n; j++){
                    if(!nodoActual.visitados[j]){
                        costoObtenido = min(costoObtenido, matAdj[i-1][j-1]);
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
    raiz.visitados[1] = true; //garantizar que todos los demas tengan false
    calculaCostoPosible(raiz, matAdj, n);
    priority_queue<Nodo> pq;
    pq.push(raiz);
    while (!pq.empty()){
        // Try here
    }
    return costoOptimo;
}

void printMat(int matAdj[MAX][MAX], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<matAdj[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int main(){
    //n = cantidad de nodos
    //m = cantidad de arcos
    int n, m;
    cin >> n >> m;
    int matAdj[MAX][MAX];//asumimos que es base 1 (A=1, B=2, C=3...)
    iniciaMat(matAdj);
    leerArcos(matAdj, m);
    printMat(matAdj,n);
    cout << tsp(matAdj, n) << endl;

}
