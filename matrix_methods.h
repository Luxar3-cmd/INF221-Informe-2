#ifndef MATRIX_METHODS_H
#define MATRIX_METHODS_H

#include <vector>
#include <fstream>
using namespace std;

#define matrix vector<vector<int>>

// Declaración de funciones
void print_matrix(const matrix& mat);
matrix read_matrixs(ifstream& data);
matrix get_submatrix(const matrix& original, int n, int m);

#endif // MATRIX_METHODS_H