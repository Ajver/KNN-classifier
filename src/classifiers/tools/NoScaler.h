#ifndef KNN_CLASSIFIER_NOSCALER_H
#define KNN_CLASSIFIER_NOSCALER_H

#include "AbstractDataScaler.h"


using namespace std;
namespace cll {

    class NoScaler : public AbstractDataScaler {
    public:
        void fit(const std::vector<std::vector<float>>&) override;

        std::vector<std::vector<float>> scale(const std::vector<std::vector<float>>&) const override;
        std::vector<float> scale(const std::vector<float>&) const override;

    private:
        std::vector<float> mean_values;
        std::vector<float> std_values;
    };

}


#endif //KNN_CLASSIFIER_NOSCALER_H