//
// Created by dom on 04/11/2025.
//

#ifndef KNN_CLASSIFIER_ABSTRACTDATASCALING_H
#define KNN_CLASSIFIER_ABSTRACTDATASCALING_H

#include <vector>

namespace cll {
    class AbstractDataScaling {
    public:
        virtual void fit(const std::vector<std::vector<float>>&) = 0;

        virtual std::vector<std::vector<float>> scale(const std::vector<std::vector<float>>&) const = 0;
        virtual std::vector<float> scale(const std::vector<float>&) const = 0;
    };
}

#endif //KNN_CLASSIFIER_ABSTRACTDATASCALING_H