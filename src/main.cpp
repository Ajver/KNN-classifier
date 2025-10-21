#include <cmath>
#include <iostream>
#include <vector>

#include "classifiers/Datasheet.h"
#include "classifiers/KNN.h"

using namespace std;
using namespace cll;

int main() {
    Datasheet bmi_data = Datasheet::load_from_csv("data/bmi_simplified.csv", 2, 1);

    KNN model(3);
    model.fit(bmi_data);

    vector<float> val_x = { 4, 4 };
    int test_y = 4;
    ClassificationResult pred = model.predict(val_x);

    cout << "Predicted: " << pred.predicted_class << " (" << round(pred.confidence*100) << "% conf)"  << " expected: " << test_y << endl;

    return 0;
}