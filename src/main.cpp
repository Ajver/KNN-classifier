#include <iostream>
#include <vector>

#include "classifiers/KNN.h"

using namespace std;
using namespace cll;


int main() {
    vector<vector<float>> X = {
        vector<float>{1, 1},
        vector<float>{2, 2},
        vector<float>{3, 3},
        vector<float>{4, 4},
        vector<float>{5, 5},
    };

    vector<int> Y = {1, 2, 3, 4, 5,};

    KNN model(3);
    model.fit(X, Y);

    vector<float> val_x = { 4, 4 };
    int test_y = 4;
    int pred_y = model.predict(val_x);

    cout << "Predicted: " << pred_y << " expected: " << test_y << endl;

    return 0;
}