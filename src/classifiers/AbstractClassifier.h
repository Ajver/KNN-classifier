#ifndef KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
#define KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
#include <vector>

#include "ClassificationResult.h"
#include "Datasheet.h"


namespace cll {
    class AbstractClassifier {
    public:
        virtual void fit(std::vector<std::vector<float>>&, std::vector<int>&) = 0;
        virtual void fit(Datasheet&) = 0;

        virtual std::vector<ClassificationResult> predict(std::vector<std::vector<float>>&) const = 0;
        virtual ClassificationResult predict(std::vector<float>) const = 0;
    };
}

#endif //KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
