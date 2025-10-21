#ifndef KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
#define KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
#include <vector>

namespace cll {
    class AbstractClassifier {
    public:
        virtual void fit(std::vector<std::vector<float>>&, std::vector<int>&) = 0;

        virtual std::vector<int> predict(std::vector<std::vector<float>>&) const = 0;
        virtual int predict(std::vector<float>&) const = 0;
    };
}

#endif //KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
