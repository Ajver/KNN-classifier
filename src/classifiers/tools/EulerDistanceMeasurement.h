#ifndef KNN_CLASSIFIER_EULERDISTANCEMEASUREMENT_H
#define KNN_CLASSIFIER_EULERDISTANCEMEASUREMENT_H

#include "AbstractDistanceMeasurement.h"


namespace cll {
    class EulerDistanceMeasurement : public AbstractDistanceMeasurement {
    public:
        float calculate_distance(const std::vector<float>&, const std::vector<float>&) const override;
    };
}

#endif //KNN_CLASSIFIER_EULERDISTANCEMEASUREMENT_H