#include <cmath>
#include <iostream>
#include <vector>

#include "classifiers/Datasheet.h"
#include "classifiers/KNN.h"

using namespace std;
using namespace cll;

int main() {
    Datasheet bmi_data = Datasheet::load_from_csv("data/bmi_simplified.csv", 2, 1);
    pair train_test_split = Datasheet::train_test_split(bmi_data, 0.8);
    Datasheet train_data = train_test_split.first;
    Datasheet test_data = train_test_split.second;

    cout << "Full data: " << bmi_data.X.size() << " " << bmi_data.Y.size() << endl;
    cout << "Train data: " << train_data.X.size() << " " << train_data.Y.size() << endl;
    cout << "Test data: " << test_data.X.size() << " " << test_data.Y.size() << endl;

    KNN model(3);
    model.fit(train_data);

    vector<ClassificationResult> pred = model.predict(test_data.X);

    int correct = 0;
    for (int i = 0; i < pred.size(); i++) {
        correct += static_cast<int>(pred[i].predicted_class == test_data.Y[i]);
        // cout << "Predicted: " << pred[i].predicted_class << " (" << round(pred[i].confidence*100) << "% conf)"  << " expected: " << test_data.Y[i] << endl;
    }

    cout << "Accuracy: " << static_cast<float>(correct) / test_data.X.size() << endl;

    train_data.save_as_csv("data/train_data.csv", {"Height,Weight,BmiClass"});
    test_data.save_as_csv("data/test_data.csv",  {"Height,Weight,BmiClass"});

    return 0;
}