// bruteDL.h
#ifndef BRUTEDL_H
#define BRUTEDL_H

#include "cost_functions.h" 
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

int bruteDL(string& p, string& s, int i, int j) {
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

    if (p[i-1] == s[j-1]) return bruteDL(p, s, i - 1, j - 1);

    int transposition = INT_MAX;
    if (i > 1 && j > 1 && p[i-1] == s[j-2] && p[i-2] == s[j-1]) {
        transposition = costo_trans(p[i-1], p[i-2]) + bruteDL(p, s, i - 2, j - 2);
    }

    int sustitucion = costo_sub(p[i-1], s[j-1]) + bruteDL(p, s, i - 1, j - 1);
    int insercion = costo_ins(s[j-1]) + bruteDL(p, s, i, j - 1);
    int eliminacion = costo_del(p[i-1]) + bruteDL(p, s, i - 1, j);

    return min({transposition, sustitucion, insercion, eliminacion});
}

#endif // BRUTEDL_H
