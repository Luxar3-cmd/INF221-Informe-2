#ifndef DYNAMICDL_H
#define DYNAMICDL_H

#include "cost_functions.h" // Incluir para el uso de las funciones de costo
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int dynamicDL(const string &p, const string &s) {
    int length_p = p.length(), length_s = s.length();

    // Creación de la matriz de costos
    vector<vector<int>> memo(length_p + 1, vector<int>(length_s + 1, 0));

    // Inicialización de filas y columnas
    int sumar = 0;
    for (int i = 1; i <= length_p; i++) {
        sumar += costo_del(p[i - 1]);
        memo[i][0] = sumar;
    }
    
    sumar = 0;
    for (int j = 1; j <= length_s; j++) {
        sumar += costo_ins(s[j - 1]);
        memo[0][j] = sumar;
    }
    
    // Llenado de la matriz de costos usando DP
    for (int i = 1; i <= length_p + 1; i++) {
        for (int j = 1; j <= length_s + 1; j++) {
            // Cálculo del costo de sustitución o coincidencia
            int d = (p[i - 1] == s[j - 1]) ? 0 : costo_sub(p[i - 1], s[j - 1]);
            
            // Cálculo de costos mínimos entre eliminación, inserción, y sustitución
            memo[i][j] = min({
                memo[i - 1][j] + costo_del(p[i - 1]),  // Eliminación
                memo[i][j - 1] + costo_ins(s[j - 1]),  // Inserción
                memo[i - 1][j - 1] + d                 // Sustitución o coincidencia
            });
            
            // Cálculo del costo de transposición
            if (i > 1 && j > 1 && p[i - 1] == s[j - 2] && p[i - 2] == s[j - 1]) {
                memo[i][j] = min(memo[i][j], memo[i - 2][j - 2] + costo_trans(p[i - 1], p[i - 2]));
            }
        }
    }
    return memo[length_p][length_s];
}

#endif // DYNAMICDL_H