#ifndef COST_FUNCTIONS_H
#define COST_FUNCTIONS_H

#include <vector>
using namespace std;
// Declaración de las matrices globales de costo
extern vector<vector<int>> insert_costs;
extern vector<vector<int>> delete_costs;
extern vector<vector<int>> replace_costs;
extern vector<vector<int>> transpose_costs;
// Declaración de funciones
int costo_sub(char a, char b);
int costo_ins(char b);
int costo_del(char a);
int costo_trans(char a, char b);

#endif // COST_FUNCTIONS_H
