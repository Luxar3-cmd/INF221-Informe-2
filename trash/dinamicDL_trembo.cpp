#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "../matrix_methods.h"

using namespace std;
#define matrix vector<vector<int> >

int min (int a, int b, int c) {
    return min(min(a,b),c);
}

unordered_map<char,int> initializeMap() {
    unordered_map<char,int> CP;

    //Letras mayusculas
    for ( char c = 'A'; c <= 'Z'; ++c) {
        CP[c] = 0;
    }
    //Letras minusculas
    for ( char c = 'a'; c <= 'z'; ++c) {
        CP[c] = 0;
    }
    //Números
    for ( char c = '0'; c <= '9'; ++c) {
        CP[c] = 0;
    }

    return CP;
}

int dynamicDL(string p, string s) {
    int length_p = p.length(), length_s = s.length(),  CS;
    
    matrix memo(length_p + 1, vector<int>(length_s + 1,0)); //C

    unordered_map<char,int> CP = initializeMap();
    
    //Inicialización de filas y columnas.
    for (int i = 0; i < length_p + 1; i++) {memo[i][0] = i;}
    for (int j = 0; j < length_s + 1; j++) {memo[0][j] = j;}

    for (int i = 1; i < length_p + 1; i++){
        CS = 0;
        for ( int j = 1; j < length_s + 1; j++) {
            int d = (p[i-1] == s[j-1]) ? 0 : 1; // Si los caracteres son iguales d = 0, si no, d = 1.
            //Cálculo del costo basico: Inserción, eliminación o sustitucion
            memo[i][j] = min(memo[i-1][j]+ 1 ,memo[i][j-1] + 1 , memo[i-1][j-1] + d);

            int i_prime = CP[s[j-1]];
            int j_prime = CS; //Última vez que p[i] aparecio
            
            if ( i_prime > 0 && j_prime > 0) {
                memo[i][j] = min(memo[i][j],memo[i_prime-1][j_prime-1] + (i - i_prime - 1) + (j -j_prime -1) + 1);
            }

            if (p[i-1]==s[j-1]) {
                CS = j;
            }
        }

        if ( CP.find(p[i-1]) != CP.end()) {
            CP[p[i-1]] = i;
        }
    }
    
    return memo[length_p][length_s];
}

int main() {
    string p = "resroh";
    string s = "hosre";
    cout << dynamicDL(p,s) << endl;
    return 0;
}