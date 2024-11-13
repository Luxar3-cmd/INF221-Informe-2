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
void process_test1(map<int, vector<long long>>& times_FBplus , map<int, vector<long long>>& times_FB, map<int, vector<long long>>& times_DP, map<int, vector<long long>>& times_FBplus_same_word,map<int, vector<long long>>& times_FB_same_word, map<int, vector<long long>>& times_DP_same_word, const string& output_file) {
    ofstream output(output_file);

    output << "Length, Avg_TIempo_FBplus, Std_Tiempo_FBplus , Avg_Tiempo_FB, Std_Tiempo_FB, Avg_Tiempo_DP, Std_Tiempo_DP, Avg_Tiempo_FBplus_same_word, Std_Tiempo_FBplus_same_word, Avg_Tiempo_FB_same_word, Std_Tiempo_FB_same_word, Avg_Tiempo_DP_same_word,Std_Tiempo_DP_same_word\n";

    for (const auto& entry : times_FB) {
        int length = entry.first;
        auto [avg_FBplus, std_FBplus] = avg_std(times_FBplus[length]);
        auto [avg_FB, std_FB] = avg_std(times_FB[length]);
        auto [avg_DP, std_DP] = avg_std(times_DP[length]);
        auto [avg_FBplus_same, std_FBplus_same] = avg_std(times_FBplus_same_word[length]);
        auto [avg_FB_same, std_FB_same] = avg_std(times_FB_same_word[length]);
        auto [avg_DP_same, std_DP_same] = avg_std(times_DP_same_word[length]);


        output << length << "," << avg_FBplus << "," << std_FBplus << "," << avg_FB << "," << std_FB << "," << avg_DP << "," << std_DP << "," << avg_FBplus_same << "," << std_FBplus_same << "," << avg_FB_same << "," << std_FB_same << "," << avg_DP_same << "," << std_DP_same << "\n";
    }

    output.close();
    cout << "Posprocesado de Test-1 guardado en " << output_file << endl;
}

// Posprocesado de Test-2
void process_test2(const string& input_file, const string& output_file) {
    ifstream file(input_file);
    ofstream output(output_file);
    output << "Case, Avg_Tiempo_FBplus, Std_Tiempo_FBplus ,Avg_Tiempo_FB, Std_Tiempo_FB, Avg_Tiempo_DP, Std_Tiempo_DP\n";

    map<string, vector<long long>> times_FBplus ,times_FB, times_DP;
    string line;

    // Saltar la cabecera
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string case_type;
        long long tiempo_FBplus, tiempo_FB, tiempo_DP;

        getline(ss, case_type, ',');
        ss >> tiempo_FBplus;
        ss.ignore(); // Ignorar la coma
        ss >> tiempo_FB;
        ss.ignore(); // Ignorar la coma
        ss >> tiempo_DP;

        times_FBplus[case_type].push_back(tiempo_FBplus);
        times_FB[case_type].push_back(tiempo_FB);
        times_DP[case_type].push_back(tiempo_DP);
    }

    for (const auto& entry : times_FB) {
        const string& case_type = entry.first;
        auto [avg_FBplus, std_FBplus] = avg_std(times_FBplus[case_type]);
        auto [avg_FB, std_FB] = avg_std(times_FB[case_type]);
        auto [avg_DP, std_DP] = avg_std(times_DP[case_type]);

        output << case_type << "," << avg_FBplus << "," << std_FBplus << "," << avg_FB << "," << std_FB << "," << avg_DP << "," << std_DP << "\n";
    }

    file.close();
    output.close();
    
    cout << "Posprocesado de Test-2 guardado en " << output_file << endl;
}

#endif // POSTPROCESSING_H
