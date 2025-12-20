#ifndef KNN_CLASSIFIER_DATANORMALIZATION_H
#define KNN_CLASSIFIER_DATANORMALIZATION_H

#include "AbstractDataScaler.h"


namespace cll {

    class NormalScaler : public AbstractDataScaler {
    public:
        void fit(const std::vector<std::vector<float>>&) override;

        std::vector<std::vector<float>> scale(const std::vector<std::vector<float>>&) const override;
        std::vector<float> scale(const std::vector<float>&) const override;
    private:
        std::vector<float> min_values;
        std::vector<float> max_values;

    };

}


#endif
