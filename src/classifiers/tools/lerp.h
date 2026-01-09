//
// Created by dom on 04/11/2025.
//

#ifndef KNN_CLASSIFIER_LERP_H
#define KNN_CLASSIFIER_LERP_H


inline float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}


#endif //KNN_CLASSIFIER_LERP_H