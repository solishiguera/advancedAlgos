//
//  MEM.cpp
//  KnapsackProblem
//
//  Created by Diego Solis on 10/12/21.
//

#include <stdio.h>
#include <iostream>
#include <climits>

using namespace std;

#define MAX 51

// Complejidad O(N^3)
void calcula(int D[MAX][MAX], int P[MAX][MAX], int d[MAX], int n){
    for(int i = 1; i <= n; i++) {
        D[i][i] = P[i][i] = 0;
    }
    
    int j, aux, men, menk = 0;
    for (int diag = 1; diag <= n - 1; diag++) {
        for (int i = 1; i <= n - diag; i++) {
            j = i + diag;
            men = INT_MAX;
            for (int k = i; k < j; k++) {
                aux = D[i][k] + D[k+1][j] + d[i-1] * d[k] * d[j];
                if (aux < men) {
                    men = aux;
                    menk = k;
                }
            }
            D[i][j] = men;
            P[i][j] = menk;
        }
    }
}

void recorre(int P[MAX][MAX], int ini, int fin){
    if (P[ini][fin] != 0) {
        cout << "(";
        recorre(P, ini, P[ini][fin]);
        cout << ")x(";
        recorre(P, P[ini][fin] + 1, fin);
        cout << ")";
    } else {
        char ch = 'A' + ini - 1; // cout << "M" << ini;
        cout << ch;
    }
}

void despliega(int P[MAX][MAX], int n){
    recorre(P,1,n);
    cout << endl;
}

void despM(int D[MAX][MAX], int P[MAX][MAX], int n){
    cout << "------------"<<endl;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            cout << D[i][j] << " ";
        }
        cout << endl;
    }
    cout << "------------"<<endl;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            cout << P[i][j] << " ";
        }
        cout << endl;
    }}

int main(){
    int d[MAX]; // Las dimenciones de las matrices
    // D guarda las múltipicaciones minimas escalares desde la matriz i hasta la matriz j
    // P guarda la k que minimiza las MEM Mi...Mj
    int D[MAX][MAX], P[MAX][MAX];
    int n; // cantidad de matrices a mult.
    for (int i=0; i<MAX; i++){
        for (int j=0; j<MAX; j++){
            D[i][j] = P[i][j] = 0;
        }
    }
    cin >> n;
    for (int i=0; i<=n; i++){
        cin >> d[i];
    }

    calcula(D, P, d, n);
    cout << D[1][n]<< endl;
    despliega(P, n);
//    despM(D,P,n);
}

/*
4
20 2 30 12 8

RESP = 1232
(A)x(((B)x(C))x(D))
*/

// A  8 x 2
// B  2 x 5
// C  5 x 4
// n = 3
// d  8 2 5 4
