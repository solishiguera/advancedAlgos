//
//  act13.cpp
//  MST
//
//  Created by Diego Solis on 10/12/21.
//

#include <stdio.h>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

#define MAX 51
/*
 Diego Solis Higuera - A00827847
 Complejidad O(N^3)
*/

void calcula(int D[MAX][MAX], int P[MAX][MAX], int d[MAX], int n){
    for(int i = 1; i <= n; i++) {
        D[i][i] = P[i][i] = 0;
    }
    
    int j, aux, men, menk = 0;
    for (int diag = 1; diag < n; diag++) {
        for (int i = 1; i <= n - diag; i++) {
            j = i + diag;
            men = INT_MAX;
            for (int k = i; k < j; k++) {
                aux = D[i][k] + D[k+1][j] + (d[j] - d[i-1]);
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
    vector<int> sol;
    int length;
    cin >> length;
    
    while(length != 0) {
        cin >> n;
        d[0] = 0;
        int i = 1;
        for (i; i <= n; i++) {
            cin >> d[i];
        }
        d[i] = length;
        n++;
        calcula(D, P, d, n);
        sol.push_back(D[1][n]);
        cin >> length;
    }
    
    for(auto it : sol) {
        cout << "The minimum cutting is " << it << "." << endl;
    }
    
}

/*
 4
 20 2 30 12 8
 
 10
 4
 4 5 7 8
 0
 RESP = 1232
 (A)x(((B)x(C))x(D))
 */

/*
 100
 3
 25 50 75
 10
 4
 4 5 7 8
 0
 */
