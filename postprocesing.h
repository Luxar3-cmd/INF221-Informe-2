#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include <bits/stdc++.h>

using namespace std;

// Función para calcular promedio y desviación estándar
pair<double, double> avg_std(const vector<long long>& times) {
    double avg = accumulate(times.begin(), times.end(), 0.0) / times.size();
    double variance = 0.0;
    for (const auto& time : times) {
        variance += pow(time - avg, 2);
    }
    variance /= times.size();
    return {avg, sqrt(variance)};
}

// Posprocesado de Test-1
void process_test1(const string& input_file, const string& output_file) {
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
        auto [avg_FB, std_FB] = avg_std(times_FB[length]);
        auto [avg_DP, std_DP] = avg_std(times_DP[length]);
        auto [avg_FB_same, std_FB_same] = avg_std(times_FB_same_word[length]);
        auto [avg_DP_same, std_DP_same] = avg_std(times_DP_same_word[length]);

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
        auto [avg_FB, std_FB] = avg_std(times_FB[case_type]);
        auto [avg_DP, std_DP] = avg_std(times_DP[case_type]);

        output << case_type << "," << avg_FB << "," << std_FB << "," << avg_DP << "," << std_DP << "\n";
    }

    file.close();
    output.close();
    cout << "Posprocesado de Test-2 guardado en " << output_file << endl;
}

#endif // POSTPROCESSING_H
