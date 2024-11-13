#include "matrix_methods.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <bits/stdc++.h>
#define matrix vector<vector<int> >

using namespace std;

matrix insert_costs, delete_costs, replace_costs, transpose_costs;

// Función para calcular promedio y desviación estándar
pair<double, double> calculate_stats(const vector<long long>& times) {
    double avg = accumulate(times.begin(), times.end(), 0.0) / times.size();
    double variance = 0.0;
    for (const auto& time : times) {
        variance += pow(time - avg, 2);
    }
    variance /= times.size();
    return {avg, sqrt(variance)};
}

// Posprocesado de Test-1
void process_test1(string input_file, string output_file) {
    ifstream file(input_file);
    ofstream output(output_file);

    output << "Length,Avg_Tiempo_FB,Std_Tiempo_FB,Avg_Tiempo_DP,Std_Tiempo_DP,"
              "Avg_Tiempo_FB_same_word,Std_Tiempo_FB_same_word,Avg_Tiempo_DP_same_word,Std_Tiempo_DP_same_word\n";

    map<int, vector<long long>> times_FB, times_DP, times_FB_same_word, times_DP_same_word;
    string line;
    
    // Saltar la cabecera
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        long long tiempo_FB, tiempo_DP, tiempo_FB_same_word, tiempo_DP_same_word;
        int length;

        ss >> tiempo_FB;
        ss.ignore(); // Ignorar la coma
        ss >> tiempo_DP;
        ss.ignore();
        ss >> tiempo_FB_same_word;
        ss.ignore();
        ss >> tiempo_DP_same_word;
        ss.ignore();
        length = line.size();  // Determina la longitud del string

        times_FB[length].push_back(tiempo_FB);
        times_DP[length].push_back(tiempo_DP);
        times_FB_same_word[length].push_back(tiempo_FB_same_word);
        times_DP_same_word[length].push_back(tiempo_DP_same_word);
    }

    for (const auto& entry : times_FB) {
        int length = entry.first;
        auto [avg_FB, std_FB] = calculate_stats(times_FB[length]);
        auto [avg_DP, std_DP] = calculate_stats(times_DP[length]);
        auto [avg_FB_same, std_FB_same] = calculate_stats(times_FB_same_word[length]);
        auto [avg_DP_same, std_DP_same] = calculate_stats(times_DP_same_word[length]);

        output << length << "," << avg_FB << "," << std_FB << "," << avg_DP << "," << std_DP << ","
               << avg_FB_same << "," << std_FB_same << "," << avg_DP_same << "," << std_DP_same << "\n";
    }

    file.close();
    output.close();
    cout << "Posprocesado de Test-1 guardado en " << output_file << endl;
}


// Posprocesado de Test-2
void process_test2(const string& input_file, const string& output_file) {
    ifstream file(input_file);
    ofstream output(output_file);
    output << "Case,Avg_Tiempo_FB,Std_Tiempo_FB,Avg_Tiempo_DP,Std_Tiempo_DP\n";

    map<string, vector<long long>> times_FB, times_DP;
    string line;

    // Saltar la cabecera
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string case_type;
        long long tiempo_FB, tiempo_DP;

        getline(ss, case_type, ',');
        ss >> tiempo_FB;
        ss.ignore(); // Ignorar la coma
        ss >> tiempo_DP;

        times_FB[case_type].push_back(tiempo_FB);
        times_DP[case_type].push_back(tiempo_DP);
    }

    for (const auto& entry : times_FB) {
        const string& case_type = entry.first;
        auto [avg_FB, std_FB] = calculate_stats(times_FB[case_type]);
        auto [avg_DP, std_DP] = calculate_stats(times_DP[case_type]);

        output << case_type << "," << avg_FB << "," << std_FB << "," << avg_DP << "," << std_DP << "\n";
    }

    file.close();
    output.close();
    cout << "Posprocesado de Test-2 guardado en " << output_file << endl;
}

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
int bruteDL (string& p,string& s ,int i, int j) {

    if ( i==0 && j == 0 ) return 0;
    //Casos donde se llega al final de un string mientras el otro aún no ha terminado de recorrer.
    if (i == 0) {
        int total_cost = 0;
        for (int k = j; k > 0; --k) {
            total_cost += costo_ins(s[k - 1]);
        }
        return total_cost;
    } // Caso donde llegamos al final de p pero quedan caracteres en s (inserciones restantes)

    if (j == 0) {
        int total_cost = 0;
        for (int k = i; k > 0; --k) {
            total_cost += costo_del(p[k - 1]);
        }
        return total_cost;
    } // Coste de eliminar caracteres restantes en p
   
    if (p[i-1]==s[j-1]) return bruteDL(p,s, i-1, j-1);  // Si ambos carácteres son iguales entonces se continúa con los siguientes.

    int transposition = INT_MAX; 
    if ( i > 1 && j > 1 && p[i-1] == s[j-2] && p[i-2] == s[j-1] ) {
        transposition = costo_trans(p[i-1],p[i-2]) + bruteDL(p,s,i-2,j-2); 
    } 

    int sustitucion = costo_sub(p[i-1], s[j-1]) + bruteDL(p,s,i-1,j-1); // Sustitución
    int insercion = costo_ins(s[j-1]) + bruteDL(p,s,i,j - 1); // Inserción
    int eliminacion = costo_del(p[i-1]) + bruteDL(p,s,i - 1, j ); // Eliminación

    return min({transposition,sustitucion,insercion,eliminacion});
}

int dynamicDL(string p, string s) {
    // Inicialización de los largos
    int length_p = p.length(), length_s = s.length();
    // Creación de la matriz de costos
    matrix memo(length_p + 1, vector<int>(length_s + 1,0)); //C
    // Este mapa guarda la ultima vez que se vió un caracter.

    
    //Inicialización de filas y columnas.
    int sumar = 0;
    for (int i = 1; i < length_p + 1; i++) {
        sumar += costo_del(p[i-1]);
        memo[i][0] = sumar;
    } 
    
    sumar = 0;
    for (int j = 1; j < length_s + 1; j++) {
        sumar += costo_ins(s[j-1]);
        memo[0][j] = sumar;
    }
    
    for (int i = 1; i < length_p + 1; i++){ // Por cada letra en p
        for ( int j = 1; j < length_s + 1; j++) { // Recorremos s
            // Si los caracteres son iguales el costo es cero, por el contrario si no lo son hay que calcular el costo de inserción.
            int d = (p[i-1] == s[j-1]) ? 0 : costo_sub(p[i-1],s[j-1]); 
            
            memo[i][j] = min({memo[i-1][j] + costo_del(p[i-1]), // Eliminacion //arriba
                           memo[i][j-1] + costo_ins(s[j-1]), // Inserción //izquierda
                           memo[i-1][j-1] + d}                // Sustitución //diagonal
                          );
            
            // Solo se permite la transposición de carácteres adyacentes.

            if ( i > 1 && j > 1 && p[i-1] == s[j-2] && p[i-2] == s[j-1] ) { 
                memo[i][j] = min(memo[i][j],memo[i-2][j-2] + costo_trans(p[i-1],p[i-2]));
            }

        }
    }
    return memo[length_p][length_s];
}

int main() {

    // Inicialización de las matrices de costos
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
    /*---------------------------------------Test-1--------------------------------------------------*/
    string filename = "./Datasets/fixed_length_dataset.csv";
    ifstream file(filename);
    ofstream output("output_results.csv");
    output << "Tiempo_FB, Tiempo_DP, Tiempo_FB_same_word, Tiempo_DP_same_word " << endl;

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo de datos." << endl;
        return 0;
    }

    long long total_FB = 0, total_DP = 0, total_FB_same_word = 0, total_DP_same_word = 0;
    int num_tests = 0;
    map<int, vector<long long>> times_FB, times_DP, times_FB_same_word, times_DP_same_word;
    string line;
    getline(file, line); // Saltar la cabecera
    // Leer el archivo de entrada
    while (getline(file, line)) {
        stringstream ss(line);
        string word1, word2, length_str;
        getline(ss, word1, ',');
        getline(ss, word2, ',');
        getline(ss, length_str, ',');

        // Medir tiempo para bruteDL con palabras diferentes
        auto start0 = chrono::high_resolution_clock::now();
        int brute_result = bruteDL(word1, word2, word1.length(), word2.length());
        auto end0 = chrono::high_resolution_clock::now();
        auto Tiempo_FB = chrono::duration_cast<chrono::microseconds>(end0 - start0).count();

        // Medir tiempo para dynamicDL con palabras diferentes
        auto start1 = chrono::high_resolution_clock::now();
        int dynamic_result = dynamicDL(word1, word2);
        auto end1 = chrono::high_resolution_clock::now();
        auto Tiempo_DP = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();

        // Medir tiempo para bruteDL con la misma palabra
        auto start2 = chrono::high_resolution_clock::now();
        int brute_same_result = bruteDL(word1, word1, word1.length(), word1.length());
        auto end2 = chrono::high_resolution_clock::now();
        auto Tiempo_FB_same_word = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();

        // Medir tiempo para dynamicDL con la misma palabra
        auto start3 = chrono::high_resolution_clock::now();
        int dynamic_same_result = dynamicDL(word1, word1);
        auto end3 = chrono::high_resolution_clock::now();
        auto Tiempo_DP_same_word = chrono::duration_cast<chrono::microseconds>(end3 - start3).count();

        times_FB[stoi(length_str)].push_back(Tiempo_FB); 
        times_DP[stoi(length_str)].push_back(Tiempo_DP);
        times_FB_same_word[stoi(length_str)].push_back(Tiempo_FB_same_word);
        times_DP_same_word[stoi(length_str)].push_back(Tiempo_DP_same_word);


        output << Tiempo_FB << "," << Tiempo_DP << "," << Tiempo_FB_same_word << "," << Tiempo_DP_same_word << endl;

        // Agregar los tiempos individuales a los acumuladores
        total_FB += Tiempo_FB;
        total_DP += Tiempo_DP;
        total_FB_same_word += Tiempo_FB_same_word;
        total_DP_same_word += Tiempo_DP_same_word;

        num_tests++;
    }

    file.close();
    output.close();

    // Calculo de promedios
    double avg_FB = static_cast<double>(total_FB) / num_tests;
    double avg_DP = static_cast<double>(total_DP) / num_tests;
    double avg_FB_same_word = static_cast<double>(total_FB_same_word) / num_tests;
    double avg_DP_same_word = static_cast<double>(total_DP_same_word) / num_tests;

    // Calculo de desviación estándar
    auto calc_std_dev = [num_tests](const vector<long long>& times, double avg) {
        double variance = 0.0;
        for (auto time : times) {
            variance += pow(time - avg, 2);
        }
        variance /= num_tests;
        return sqrt(variance);
    };

    //double std_dev_FB = calc_std_dev(times_FB, avg_FB);
    //double std_dev_DP = calc_std_dev(times_DP, avg_DP);
    //double std_dev_FB_same_word = calc_std_dev(times_FB_same_word, avg_FB_same_word);
    //double std_dev_DP_same_word = calc_std_dev(times_DP_same_word, avg_DP_same_word);

    // Mostrar los promedios y desviación estándar en consola
    cout << "Promedios de tiempo (en microsegundos): " << endl;
    //cout << "Tiempo_BF: " << avg_FB << " +- " << std_dev_FB << endl;
    //cout << "Tiempo_DP: " << avg_DP << " +- " << std_dev_DP << endl;
    //cout << "Tiempo_FB_same_word: " << avg_FB_same_word << " +- " << std_dev_FB_same_word << endl;
    //cout << "Tiempo_DP_same_word: " << avg_DP_same_word << " +- " << std_dev_DP_same_word << endl;

    cout << "Pruebas completadas. Resultados guardados en 'output_results.csv'." << endl;

    /*------------------------------------------Test-2----------------------------------------------*/

    filename = "./Datasets/datasets.csv";
    ifstream file2(filename);
    ofstream output2("output_results2.csv");
    output2 << "Case, Tiempo_FB, Tiempo_DP" << endl;

    if ( !file2.is_open() ) {
        cerr << "No se pudo abrir el archivo de datos." << endl;
        return 0;
    }
    
    getline(file2,line); // Leer la cabecera del archivo CSV
    while (getline(file2,line)) {
        stringstream ss2(line);
        string word1,word2,case_type;
        getline(ss2,word1,',');
        getline(ss2,word2,',');
        getline(ss2,case_type,',');
        // Medir tiempo para bruteDL
        auto start0 = chrono::high_resolution_clock::now();
        int brute_result = bruteDL(word1,word2,word1.length(),word2.length());
        auto end0 = chrono::high_resolution_clock::now();
        auto Tiempo_FB = chrono::duration_cast<chrono::microseconds>(end0 - start0).count();

        // Medir tiempo para dynamicDL
        auto start1 = chrono::high_resolution_clock::now();
        int dynamic_result = dynamicDL(word1,word2);
        auto end1 = chrono::high_resolution_clock::now();
        auto Tiempo_DP = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();

        output2 << case_type << "," << Tiempo_FB << "," <<   Tiempo_DP << endl;

    }

    file2.close();
    output2.close();

    cout << "Pruebas completadas. Resultados guardados en 'ouput_results2.csv'." << endl;


    /*-------------------------------------------------Posprocesado-----------------------------------------------------*/

    // Realizar posprocesado de Test-1
    process_test1("output_results.csv", "test1_postprocessed.csv");
    // Realizar posprocesado de Test-2
    process_test2("output_results2.csv", "test2_postprocessed.csv");

    return 0;
}