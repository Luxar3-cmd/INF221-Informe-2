#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "../matrix_methods.h"
#define matrix vector<vector<int> >

using namespace std;

matrix insert_costs, delete_costs, replace_costs, transpose_costs;

int get_char_index(char c) {
    return toupper(c) - 'A';
}

//Costo sustitución
int costo_sub(char a, char b) {
    int i = get_char_index(a);
    int j = get_char_index(b);
    return replace_costs[i][j];
}

//Costo de inserción
int costo_ins(char b) {
    int j = get_char_index(b);
    return insert_costs[0][j];
}

//Costo de eliminación
int costo_del(char a) {
    cout << "Para " << a << " el costo de eliminación es: " << endl;
    int j = get_char_index(a);
    cout << "Valor en j: " << j << endl;
    return delete_costs[0][j];
}

//Costo de transposición
//p[m-1] es la letra de la derecha y s[n-1] es la letra de la izquierda antes de la transposición
int costo_trans(char a, char b) {
    int i = get_char_index(a);
    int j = get_char_index(b);
    return transpose_costs[i][j]; // Costo de transponer 'a' con 'b'
}

/**
 * Implementación recursiva de la distancia de Damerau-Levenshtein con transposiciones.
 */
int bruteDL (string& p,string& s ,int i, int j) {
    cout << "valor de i:  " << i << endl;
    cout << "valor de j:  " << j << endl;

    if ( i==0 && j == 0 ) return 0;
    //Casos donde se llega al final de un string mientras el otro aún no ha terminado de recorrer.
    if (i == 0) {
        int total_cost = 0;
        for (int k = j; k > 0; --k) {
            total_cost += costo_ins(s[k - 1]);
        }
        return total_cost;
    } // Caso donde llegamos al final de p pero quedan caracteres en s (inserciones restantes)

    if (j == 0) {
        cout << "test" << endl;
        int total_cost = 0;
        for (int k = i; k > 0; --k) {
            total_cost += costo_del(p[k - 1]);
        }

        cout << "test 2" << endl;
        return total_cost;
        
    } // Coste de eliminar caracteres restantes en p
    
    if (p[i-1]==s[j-1]) return bruteDL(p,s, i-1, j-1);  // Si ambos carácteres son iguales entonces se continúa con los siguientes.
    cout << "test trans" << endl;
    int transposition = INT_MAX; 
    if ( i > 1 && j > 1 && p[i-1] == s[j-2] && p[i-2] == s[j-1] ) {
        transposition = costo_trans(p[i-1],p[i-2]) + bruteDL(p,s,i-2,j-2); 
    } 

    int sustitucion = costo_sub(p[i-1], s[j-1]) + bruteDL(p,s,i-1,j-1); // Sustitución
    int insercion = costo_ins(s[j-1]) + bruteDL(p,s,i-1,j); // Inserción
    int eliminacion = costo_del(p[i-1]) + bruteDL(p,s,i,j-1); // Eliminación

    return min({transposition,sustitucion,insercion,eliminacion});
}

int main () {
    
    //apto para pruebas
    string p = "p";
    string s = "";
    cout << bruteDL(p,s,p.length(),s.length()) << endl;

    return 0;

}
