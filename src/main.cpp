#include <iostream>
#include "classifiers/KNN.h"

using namespace std;
using namespace cll;


int main() {

    KNN model(6);
    model.fit();
    int output = model.predict();

    cout << "model output: " << output << endl;

    return 0;
}