#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // Para INT_MAX

using namespace std;


int costo_ins(char) {
    return 4; 
}

int costo_del(char) {
    return 4; 
}

int costo_sub(char a, char b) {
    return (a == b) ? 0 : 4; 
}

int costo_trans(char a, char b) {
    return (a == b) ? 0 : 1; 
}

// Implementación dinámica de la distancia de Levenshtein con transposición
int levenshtein(const string &s1, const string &s2) {
    int m = s1.size();
    int n = s2.size();

    vector<vector<int>> memo(m + 1, vector<int>(n + 1, 0));


    for (int i = 0; i <= m; ++i) {
        memo[i][0] = i * costo_del(' '); 
    }
    for (int j = 0; j <= n; ++j) {
        memo[0][j] = j * costo_ins(' '); 
    }

    // Llenar la matriz
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {

            memo[i][j] = min(memo[i - 1][j] + costo_del(s1[i - 1]), min(memo[i][j - 1] + costo_ins(s2[j - 1]), memo[i - 1][j - 1] + costo_sub(s1[i - 1], s2[j - 1]))); // Sustitución
            
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                memo[i][j] = min(memo[i][j], memo[i - 2][j - 2] + costo_trans(s1[i - 2], s1[i - 1]));
            }
        }
    }

    return memo[m][n]; // Devolvemos el costo mínimo
}

int main() {
    string cadena1 = "abcd";
    string cadena2 = "bcda";

    int distancia = levenshtein(cadena1, cadena2);
    cout << "La distancia de edición mínima entre '" << cadena1 << "' y '" << cadena2 << "' es: " << distancia << endl;

    return 0;
}