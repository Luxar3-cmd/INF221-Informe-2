#include <string>
#include <iostream>
#include <algorithm>
#include <climits> // Para INT_MAX

using namespace std;

// Funciones de costo (ajustables según el problema)
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


int levenshtein_bruteforce(const string &s1, const string &s2, int i, int j) {


    
    if (i == s1.size()) {
        return (s2.size() - j) * costo_ins(' '); 
    }
    if (j == s2.size()) {
        return (s1.size() - i) * costo_del(' '); 
    }


    int minimo = INT_MAX;

    minimo = min(minimo, costo_sub(s1[i], s2[j]) + levenshtein_bruteforce(s1, s2, i + 1, j + 1));
    minimo = min(minimo, costo_ins(s2[j]) + levenshtein_bruteforce(s1, s2, i, j + 1));
    minimo = min(minimo, costo_del(s1[i]) + levenshtein_bruteforce(s1, s2, i + 1, j));


    if (i + 1 < s1.size() && j + 1 < s2.size()) {
        if (s1[i] == s2[j + 1] && s1[i + 1] == s2[j]) {
            minimo = min(minimo, costo_trans(s1[i], s1[i + 1]) + levenshtein_bruteforce(s1, s2, i + 2, j + 2));
        } else if (s1[i] == s2[j + 1] && s1[i + 1] != s2[j]) {
            minimo = min(minimo, costo_trans(s1[i], s1[i + 1]) + costo_sub(s1[i + 1], s2[j]) + levenshtein_bruteforce(s1, s2, i + 2, j + 2));
        } else if (s1[i] != s2[j + 1] && s1[i + 1] == s2[j]) {
            string aux = s1;
            swap(aux[i], aux[i + 1]);
            minimo = min(minimo, costo_trans(s1[i], s1[i + 1]) + levenshtein_bruteforce(aux, s2, i + 1, j + 1));
        }
    }


    return minimo;
}

int main() {
    string cadena1 = "abcd";
    string cadena2 = "bcda";

    int distancia = levenshtein_bruteforce(cadena1, cadena2, 0, 0);
    cout << "La distancia de edición mínima entre '" << cadena1 << "' y '" << cadena2 << "' es: " << distancia << endl;

    return 0;
}