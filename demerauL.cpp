#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

//Costo sustitución
int costo_sub(char a, char b) {
    if ( a == b ) return 0;
    return 2;
}

//Costo de inserción
int costo_ins(char b) {
    int costo = 1;
    //Implementación
    return 1;
}

//Costo de eliminación
int costo_del(char a) {
    int costo = 1;
    //Implementación
    return 1;
}

//Costo de transposición
//s1[m-1] es la letra de la derecha y s2[n-1] es la letra de la izquierda antes de la transposición
int costo_trans(char a, char b) {
    return 1;
}

int editDist(string s1, string s2,int m,int n) {
    int a = m - 1;
    int b = n - 1;
    if ( m == 0) return n;
    if ( n == 0) return m;
    if ( s1[a] == s2[b] ) return editDist(s1,s2,a,b);
    
    // Transposición
    int transposicion = INT_MAX;
    if ( m > 1 && n > 1 && s1[a] == s2[b - 1] && s1[a - 1] == s2[b] ) {
        transposicion = editDist(s1,s2,m-2,n-2) + costo_trans(s1[m-1],s2[n-1]);
    }
    int sustitucion = editDist(s1,s2,m-1,n-1) + costo_sub(s1[m],s2[n]);

    int insercion = editDist(s1,s2,m,n-1) + costo_ins(s2[n]);
    int eliminacion = editDist(s1,s2,m-1,n) + costo_del(s1[m]);

    return min(min(sustitucion,insercion),min(eliminacion,transposicion));

    
}



int main() {
    //test  
    string s1 = "cap";
    string s2 = "cas";
    cout << editDist(s1,s2,s1.length(),s2.length()) << endl;

    return 0;
}