#ifndef KNN_KNN_H
#define KNN_KNN_H

#include "AbstractClassifier.h"
#include "tools/AbstractDataScaler.h"
#include "tools/AbstractDistanceMeasurement.h"
#include "tools/DataScalingMethods.h"


namespace cll {

    class KNN : public AbstractClassifier {
    public:
        KNN(size_t, DataScalingMethods=MINMAX);
        ~KNN() override;

        void fit(std::vector<std::vector<float>>&, std::vector<int>&) override;
        void fit(Datasheet&) override;

        std::vector<ClassificationResult> predict(std::vector<std::vector<float>>&) const override;
        ClassificationResult predict(std::vector<float>) const override;
    private:
        const size_t K;
        std::vector<std::vector<float>> X;
        std::vector<int> Y;

        AbstractDataScaler *data_scaling;
        AbstractDistanceMeasurement* distance_measurement;
    };

}

#endif