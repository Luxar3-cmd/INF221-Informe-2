
#include "cost_functions.h"
#include <bits/stdc++.h>
#include "matrix_methods.h"
using namespace std;
// Definición de las matrices globales de costo
vector<vector<int>> insert_costs;
vector<vector<int>> delete_costs;
vector<vector<int>> replace_costs;
vector<vector<int>> transpose_costs;


int get_char_index(char c) {
    return toupper(c) - 'A';
}

// Implementación de funciones de costo
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
    return delete_costs[0][j];
}

int costo_trans(char a, char b) {
    int i = get_char_index(a);
    int j = get_char_index(b);
    return transpose_costs[i][j];
}
