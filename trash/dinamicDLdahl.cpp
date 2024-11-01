#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include "../matrix_methods.h"
#define matrix vector<vector<int> >

using namespace std;

// Matrices de costos
matrix insert_costs, delete_costs, replace_costs, transpose_costs;

int get_char_index(char c) {
    return toupper(c) - 'A';
}

int costo_sub(char a, char b) {
    int i = get_char_index(a);
    int j = get_char_index(b);
    return replace_costs[i][j];
}

int costo_ins(char b) {
    int j = get_char_index(b);
    return insert_costs[0][j];
}

int costo_del(char a) {
    int j = get_char_index(a);
    //cout << "Para " << a << " el costo de eliminación es: " << endl;
    //cout << "Valor en j: " << j << endl;
    //cout << delete_costs[0][j] << endl;
    return delete_costs[0][j];
}

int costo_trans(char a, char b) {
    int i = get_char_index(a);
    int j = get_char_index(b);
    return transpose_costs[i][j]; // Costo de transponer 'a' con 'b'
}

int min (int a, int b, int c) {
    return min(min(a,b),c);
}

unordered_map<char,int> initializeMap() {
    
    unordered_map<char,int> CP;

    //Letras minusculas
    for ( char c = 'a'; c <= 'z'; ++c) {
        CP[c] = 0;
    }
    
    return CP;
}

// Transformar p->s
int dynamicDL(string p, string s) {
    // Inicialización de los largos
    int length_p = p.length(), length_s = s.length(),  lastSeenInTarget;
    // Creación de la matriz de costos
    matrix memo(length_p + 1, vector<int>(length_s + 1,0)); //C
    // Este mapa guarda la ultima vez que se vió un caracter.
    unordered_map<char,int> lastSeenInSource = initializeMap();
    
    //Inicialización de filas y columnas.
    int sumar = 0;
    for (int i = 1; i < length_p + 1; i++) {
        sumar += costo_del(p[i-1]);
        memo[i][0] = sumar;
    } 
    
    sumar = 0;
    for (int j = 1; j < length_s + 1; j++) {
        sumar += costo_ins(s[j-1]);
        memo[0][j] = sumar;
    }
    for (int i = 1; i < length_p + 1; i++){ // Por cada letra en p
        lastSeenInTarget = 0;
        for ( int j = 1; j < length_s + 1; j++) { // Recorremos s
            
            

            // Si los caracteres son iguales el costo es cero, por el contrario si no lo son hay que calcular el costo de inserción.
            int d = (p[i-1] == s[j-1]) ? 0 : costo_sub(p[i-1],s[j-1]); 
            
            memo[i][j] = min(memo[i-1][j] + costo_del(p[i-1]), // Eliminacion //arriba
                           memo[i][j-1] + costo_ins(s[j-1]), // Inserción //izquierda
                           memo[i-1][j-1] + d                // Sustitución //diagonal
                          );
            
            

            int i_prime = lastSeenInSource[s[j-1]];
            int j_prime = lastSeenInTarget; //Última vez que p[i] aparecio
            // Solo se permite la transposición de carácteres adyacentes.


            /**
             if (i == 3 && j == 5) { 
                cout << "p[i-1] : " << p[i-1] << "  s[j-1] : " << s[j-1] << endl;
                cout << "i: " << i << " j: " << j << endl;
                cout << "memo[i-1][j-1]: " << memo[i-1][j-1] << endl;
                cout << "memo[i][j-1]: " << memo[i][j-1] << endl;
                cout << "memo[i-1][j]: " << memo[i-1][j] << endl;
                cout << "d: " << d << endl;
                cout << "p[i-1]: " << p[i-1] << " s[j-1]: " << s[j-1] << endl;
                cout << "Costo de sustitución: " <<  memo[i-1][j-1] + d << endl;
                cout << "Costo de inserción: " << memo[i][j-1] + costo_ins(s[j-1]) << endl;
                cout << "Costo de eliminación: " << memo[i-1][j] + costo_del(p[i-1]) << endl;

                print_matrix(memo);
                cout << "i_prime: " << i_prime << " j_prime: " << j_prime << endl;
                cout << "Last seen in source: " << lastSeenInSource[s[j-1]] << endl;
                cout << "Last seen in target: " << lastSeenInTarget << endl;
            }
             */
            
            if ( i_prime > 0 && j_prime > 0 && i_prime == i -1 && j_prime == j -1 && p[i-1] == s[j_prime-1] && s[j-1] == p[i_prime-1]) {
                memo[i][j] = min(memo[i][j],memo[i_prime-1][j_prime-1] + costo_trans(p[i-1],s[j-1]));
            }

            if (p[i-1]==s[j-1]) {
                lastSeenInTarget = j;
            }
        }

        if ( lastSeenInSource.find(p[i-1]) != lastSeenInSource.end()) {
            lastSeenInSource[p[i-1]] = i;
        }
    }
    return memo[length_p][length_s];
}

int main() {

    ifstream del("../Costos/cost_delete.txt");
    ifstream ins("../Costos/cost_insert.txt");
    ifstream rep("../Costos/cost_replace.txt");
    ifstream tra("../Costos/cost_transpose.txt");

    delete_costs = read_matrixs(del);
    insert_costs = read_matrixs(ins);
    replace_costs = read_matrixs(rep);
    transpose_costs = read_matrixs(tra);

    del.close();
    ins.close();
    rep.close();
    tra.close();


    // apto para pruebas
    return 0;
}