#include "matrix_methods.h"
#include "cost_functions.h"
#include "bruteDL.h"
#include "dynamicDL.h"
#include "postprocesing.h"
#include <bits/stdc++.h>

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
    /*Test1*/
    string filename1 = "./Datasets/fixed_length_dataset.csv";
    ifstream file1(filename1);
    ofstream output1("./Resultados/output_results1.csv");
    output1 << "Tiempo_FB, Tiempo_DP, Tiempo_FB_same_word, Tiempo_DP_same_word" << endl;

    // Verificar si el archivo se abrió correctamente
    if (!file1.is_open()) {
        cerr << "No se pudo abrir el archivo de datos." << endl;
        return 0;
    }

    long long total_FB = 0, total_DP = 0, total_FB_same_word = 0, total_DP_same_word = 0;
    int num_tests = 0;

    map<int, vector<long long> > times_FB, times_DP, times_FB_same_word, times_DP_same_word;
    string line1;
    getline(file1, line1); // Saltar la cabecera

    // Leer el archivo de entrada
    while ( getline(file1,line1) ) {
        stringstream ss1(line1);
        string word1, word2, length_str;
        getline(ss1, word1, ',');
        getline(ss1, word2, ',');
        getline(ss1, length_str, ',');
        int length1 = stoi(length_str);

        // Medir tiempo para bruteDL con palabras diferentes
        auto start0 = chrono::high_resolution_clock::now();
        int brute_result = bruteDL(word1, word2, word1.length(), word2.length());
        auto end0 = chrono::high_resolution_clock::now();
        auto Tiempo_FB = chrono::duration_cast<chrono::milliseconds>(end0 - start0).count();

        // Medir tiempo para dynamicDL con palabras diferentes
        auto start1 = chrono::high_resolution_clock::now();
        int dynamic_result = dynamicDL(word1, word2);
        auto end1 = chrono::high_resolution_clock::now();
        auto Tiempo_DP = chrono::duration_cast<chrono::milliseconds>(end1 - start1).count();

        // Medir tiempo para bruteDL con palabras iguales
        auto start2 = chrono::high_resolution_clock::now();
        int brute_same_result = bruteDL(word1, word1, word1.length(), word1.length());
        auto end2 = chrono::high_resolution_clock::now();
        auto Tiempo_FB_same_word = chrono::duration_cast<chrono::milliseconds>(end2 - start2).count();

        // Medir tiempo para dynamicDL con palabras iguales
        auto start3 = chrono::high_resolution_clock::now();
        int dynamic_same_result = dynamicDL(word1, word1);
        auto end3 = chrono::high_resolution_clock::now();
        auto Tiempo_DP_same_word = chrono::duration_cast<chrono::milliseconds>(end3 - start3).count();

        times_FB[length1].push_back(Tiempo_FB);
        times_DP[length1].push_back(Tiempo_DP);
        times_FB_same_word[length1].push_back(Tiempo_FB_same_word);
        times_DP_same_word[length1].push_back(Tiempo_DP_same_word);

        output1 << Tiempo_FB << "," << Tiempo_DP << "," << Tiempo_FB_same_word << "," << Tiempo_DP_same_word << endl;
    }
    // En este punto cada mapa tiene los tiempos de ejecución de cada algoritmo
    file1.close();
    output1.close();

    // Calculo de promedios y desviaciones estándar
    


    return 0;
}