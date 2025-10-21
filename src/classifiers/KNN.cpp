#include "KNN.h"
#include <iostream>


namespace cll {

    KNN::KNN(int a) {
        std::cout << "Hi from the constructor! " << a << std::endl;
    }

    void KNN::fit() {
        std::cout << "fitting..." << std::endl;
    }

    int KNN::predict() const {
        std::cout << "Predicting..." << std::endl;
        return 2;
    }

}
