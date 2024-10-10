#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

//Costo sustitución
int costo_sub(char a, char b) {
    int costo = 1;
    // Implementación
    return 1;
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
int costo_trans(char a, char b) {
    return 2;
}

int editDist(string s1, string s2,int m,int n) {
    if ( m == 0) return n;
    if ( n == 0) return m;
    if ( s1[m-1] == s2[n-1] ) return editDist(s1,s2,m-1,n-1);
    int sustitucion = editDist(s1,s2,m-1,n-1) + costo_sub(s1[m],s2[n]);
    int insercion = editDist(s1,s2,m,n-1) + costo_ins(s2[n]);
    int eliminacion = editDist(s1,s2,m-1,n) + costo_del(s1[m]);
    return min(sustitucion,min(insercion,eliminacion));
}



int main() {
    //test  
    string s1 = "execution";
    string s2 = "intention";
    cout << editDist(s1,s2,s1.length(),s2.length()) << endl;

    return 0;
}