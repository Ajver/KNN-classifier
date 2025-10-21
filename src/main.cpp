#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "classifiers/KNN.h"

using namespace std;
using namespace cll;


vector<vector<string>> readCSV(const string& filename, int skip_rows=0) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        if (skip_rows-- > 0) {
            continue;
        }

        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (!row.empty()) {
            data.push_back(row);
        }
    }

    file.close();
    return data;
}


int main() {
    auto bmi_data = readCSV("data/bmi_simplified.csv", 1);

    map<string, int> class_to_int{{"Underweight", 1}, {"Normal Weight", 2}, {"Overweight", 3}, {"Obese", 4}};
    map<int, string> int_to_class{{1, "Underweight"}, {2, "Normal Weight"}, {3, "Overweight"}, {4, "Obese"}};

    vector<vector<float>> X(bmi_data.size());

    for (int i = 0; i < bmi_data.size(); i++) {
        X[i] = vector<float>(bmi_data[i].size() - 1);
        X[i][0] = stof(bmi_data[i][0]);
        X[i][1] = stof(bmi_data[i][1]);
    }

    vector<int> Y(bmi_data.size());
    for (int i = 0; i < bmi_data.size(); i++) {
        Y[i] = class_to_int[bmi_data[i][2]];
    }

    KNN model(3);
    model.fit(X, Y);

    vector<float> val_x = { 4, 4 };
    int test_y = 4;
    ClassificationResult pred = model.predict(val_x);

    cout << "Predicted: " << pred.predicted_class << " (" << round(pred.confidence*100) << "% conf)"  << " expected: " << test_y << endl;

    return 0;
}