#include <bits/stdc++.h>
#include "matrix_methods.h"
#include "cost_functions.h"
#include "bruteDL.h"
#include "dynamicDL.h"
#include "postprocesing.h"

using namespace std;

void load_cost_matrices() {
    ifstream del("Costos/cost_delete.txt");
    ifstream ins("Costos/cost_insert.txt");
    ifstream rep("Costos/cost_replace.txt");
    ifstream tra("Costos/cost_transpose.txt");

    delete_costs = read_matrixs(del);
    insert_costs = read_matrixs(ins);
    replace_costs = read_matrixs(rep);
    transpose_costs = read_matrixs(tra);

    del.close();
    ins.close();
    rep.close();
    tra.close();
}

int main() {
    load_cost_matrices();
    string p = "kitten";
    string s = "sitting";
    cout << dynamicDL(p, s) << endl;

    cout << bruteDL(p, s, p.length(), s.length()) << endl;

    cout << bruteDLplus(p, s, p.length(), s.length()) << endl;
    return 0;
}