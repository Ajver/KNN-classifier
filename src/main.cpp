#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include "classifiers/Datasheet.h"
#include "classifiers/KNN.h"

using namespace std;
using namespace cll;

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}


void create_classification_map(Datasheet &data, KNN &model) {
    assert(data.X[0].size() == 2);

    const int points_in_a_row = 30;

    vector<float> min_values = data.X[0];
    vector<float> max_values = data.X[0];

    for (auto data_row : data.X) {
        for (int i = 0; i < data_row.size(); i++) {
            if (data_row[i] < min_values[i]) {
                min_values[i] = data_row[i];
            }
            if (data_row[i] > max_values[i]) {
                max_values[i] = data_row[i];
            }
        }
    }

    float MARGIN_RATIO = 0.05;
    vector<float> margins(min_values.size());
    for (int i = 0; i < margins.size(); i++) {
        margins[i] = (max_values[i] - min_values[i]) * MARGIN_RATIO;
    }


    vector<vector<float>> X(pow(points_in_a_row, data.X[0].size()));

    for (int y = 0; y < points_in_a_row; y++) {
        for (int x = 0; x < points_in_a_row; x++) {
            X[y*points_in_a_row + x] = vector<float>{
                lerp(min_values[0]-margins[0], max_values[0]+margins[0], static_cast<float>(y)/points_in_a_row),
                lerp(min_values[1]-margins[1], max_values[1]+margins[1], static_cast<float>(x)/points_in_a_row),
            };
        }
    }

    vector<ClassificationResult> results = model.predict(X);

    vector<int> Y(results.size());

    for (int i = 0; i < results.size(); i++) {
        Y[i] = results[i].predicted_class;
    }

    Datasheet points_map{X, Y, data.class_to_int, data.int_to_class};
    points_map.save_as_csv("data/classification_map.csv");
}

int main() {
    Datasheet bmi_data = Datasheet::load_from_csv("data/bmi_simplified.csv", 2, 1);
    pair train_test_split = Datasheet::train_test_split(bmi_data, 0.8);
    Datasheet train_data = train_test_split.first;
    Datasheet test_data = train_test_split.second;

    cout << "Full data: " << bmi_data.X.size() << " " << bmi_data.Y.size() << endl;
    cout << "Train data: " << train_data.X.size() << " " << train_data.Y.size() << endl;
    cout << "Test data: " << test_data.X.size() << " " << test_data.Y.size() << endl;

    Datasheet k_vs_accuracy;

    for (int k=1; k<=30; k++) {
        KNN model(k);
        model.fit(train_data);

        vector<ClassificationResult> pred = model.predict(test_data.X);

        int correct = 0;
        for (int i = 0; i < pred.size(); i++) {
            correct += static_cast<int>(pred[i].predicted_class == test_data.Y[i]);
            // cout << "Predicted: " << pred[i].predicted_class << " (" << round(pred[i].confidence*100) << "% conf)"  << " expected: " << test_data.Y[i] << endl;
        }

        float accuracy = static_cast<float>(correct) / test_data.X.size();
        cout << "K = " << k << " - Accuracy: " << accuracy << endl;

        k_vs_accuracy.X.push_back(vector<float>{static_cast<float>(k), accuracy});
        k_vs_accuracy.Y.push_back(0);
    }

    KNN model(9);
    model.fit(train_data);
    create_classification_map(bmi_data, model);

    k_vs_accuracy.save_as_csv("data/k_vs_accuracy.csv");

    train_data.save_as_csv("data/train_data.csv", {"Height,Weight,BmiClass"});
    test_data.save_as_csv("data/test_data.csv",  {"Height,Weight,BmiClass"});

    return 0;
}