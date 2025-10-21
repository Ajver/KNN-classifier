//
// Created by dom on 21/10/2025.
//

#ifndef KNN_CLASSIFIER_PREDICTIONRESULT_H
#define KNN_CLASSIFIER_PREDICTIONRESULT_H

#include <map>

namespace cll {
    struct ClassificationResult {
        int predicted_class;
        float confidence;

        std::map<int, size_t> classes;
    };
}


#endif //KNN_CLASSIFIER_PREDICTIONRESULT_H