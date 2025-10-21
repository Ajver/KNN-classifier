#ifndef KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
#define KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H

namespace cll {
    class AbstractClassifier {
    public:
        virtual void fit() = 0;

        virtual int predict() const = 0;
    };
} // cll

#endif //KNN_CLASSIFIER_ABSTRACTCLASSIFIER_H
