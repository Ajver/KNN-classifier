#ifndef KNN_KNN_H
#define KNN_KNN_H

#include "AbstractClassifier.h"
#include "tools/AbstractDistanceMeasurement.h"


namespace cll {

    class KNN : public AbstractClassifier {
    public:
        KNN(size_t);

        void fit(std::vector<std::vector<float>>&, std::vector<int>&) override;
        void fit(Datasheet&) override;

        std::vector<ClassificationResult> predict(std::vector<std::vector<float>>&) const override;
        ClassificationResult predict(std::vector<float>) const override;
    private:
        size_t K;
        std::vector<std::vector<float>> X;
        std::vector<int> Y;

        std::vector<float> min_values;
        std::vector<float> max_values;

        AbstractDistanceMeasurement* distance_measurement;
    };

}

#endif