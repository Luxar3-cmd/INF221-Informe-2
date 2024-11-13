#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "../matrix_methods.h"
#define matrix vector<vector<int> >

using namespace std;

matrix insert_costs, delete_costs, replace_costs, transpose_costs;
vector<string> operations; // Para almacenar las operaciones realizadas

int get_char_index(char c) {
    return toupper(c) - 'A';
}

// Costo de sustitución
int costo_sub(char a, char b) {
    int i = get_char_index(a);
    int j = get_char_index(b);
    return replace_costs[i][j];
}

// Costo de inserción
int costo_ins(char b) {
    int j = get_char_index(b);
    return insert_costs[0][j];
}

// Costo de eliminación
int costo_del(char a) {
    int j = get_char_index(a);
    return delete_costs[0][j];
}

// Costo de transposición
int costo_trans(char a, char b) {
    int i = get_char_index(a);
    int j = get_char_index(b);
    return transpose_costs[i][j];
}

// Calculo del costo mínimo para transformar p en s (primera pasada)
int bruteDL(string &p, string &s, int i, int j) {
    if (i == 0 && j == 0) return 0;

    if (i == 0) {
        int total_cost = 0;
        for (int k = j; k > 0; --k) {
            total_cost += costo_ins(s[k - 1]);
        }
        return total_cost;
    }

    if (j == 0) {
        int total_cost = 0;
        for (int k = i; k > 0; --k) {
            total_cost += costo_del(p[k - 1]);
        }
        return total_cost;
    }

    if (p[i - 1] == s[j - 1]) {
        return bruteDL(p, s, i - 1, j - 1);
    }

    int transposition = INT_MAX;
    if (i > 1 && j > 1 && p[i - 1] == s[j - 2] && p[i - 2] == s[j - 1]) {
        transposition = costo_trans(p[i - 1], p[i - 2]) + bruteDL(p, s, i - 2, j - 2);
    }

    int sustitucion = costo_sub(p[i - 1], s[j - 1]) + bruteDL(p, s, i - 1, j - 1);
    int insercion = costo_ins(s[j - 1]) + bruteDL(p, s, i, j - 1);
    int eliminacion = costo_del(p[i - 1]) + bruteDL(p, s, i - 1, j);

    return min({transposition, sustitucion, insercion, eliminacion});
}

// Segunda pasada para reconstruir las operaciones
void traceOperations(string &p, string &s, int i, int j) {
    if (i == 0 && j == 0) return;

    if (i == 0) {
        for (int k = j; k > 0; --k) {
            operations.push_back("Se inserta: " + string(1, s[k - 1]));
        }
        return;
    }

    if (j == 0) {
        for (int k = i; k > 0; --k) {
            operations.push_back("Se elimina: " + string(1, p[k - 1]));
        }
        return;
    }

    if (p[i - 1] == s[j - 1]) {
        traceOperations(p, s, i - 1, j - 1);
        return;
    }

    int currentCost = bruteDL(p, s, i, j);

    if (i > 1 && j > 1 && p[i - 1] == s[j - 2] && p[i - 2] == s[j - 1]) {
        int transpositionCost = costo_trans(p[i - 1], p[i - 2]) + bruteDL(p, s, i - 2, j - 2);
        if (transpositionCost == currentCost) {
            operations.push_back("Se transpone: " + string(1, p[i - 2]) + " con " + string(1, p[i - 1]));
            traceOperations(p, s, i - 2, j - 2);
            return;
        }
    }

    int sustitucionCost = costo_sub(p[i - 1], s[j - 1]) + bruteDL(p, s, i - 1, j - 1);
    if (sustitucionCost == currentCost) {
        operations.push_back("Se sustituye: " + string(1, p[i - 1]) + " por " + string(1, s[j - 1]));
        traceOperations(p, s, i - 1, j - 1);
        return;
    }

    int insercionCost = costo_ins(s[j - 1]) + bruteDL(p, s, i, j - 1);
    if (insercionCost == currentCost) {
        operations.push_back("Se inserta: " + string(1, s[j - 1]));
        traceOperations(p, s, i, j - 1);
        return;
    }

    int eliminacionCost = costo_del(p[i - 1]) + bruteDL(p, s, i - 1, j);
    if (eliminacionCost == currentCost) {
        operations.push_back("Se elimina: " + string(1, p[i - 1]));
        traceOperations(p, s, i - 1, j);
        return;
    }
}

/*
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

    // Prueba con dos cadenas
    string p = "intention";
    string s = "execution";
    int total_cost = bruteDL(p, s, p.length(), s.length());
    cout << "Costo total: " << total_cost << endl;

    operations.clear();
    traceOperations(p, s, p.length(), s.length());

    cout << "Pasos realizados:" << endl;
    for (const auto &op : operations) {
        cout << op << endl;
    }

    return 0;
}

*/