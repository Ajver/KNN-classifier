#ifndef KNN_CLASSIFIER_ABSTRACTDISTANCEMEASUREMENT_H
#define KNN_CLASSIFIER_ABSTRACTDISTANCEMEASUREMENT_H

#include <vector>

namespace cll {
    class AbstractDistanceMeasurement {
    public:
        virtual ~AbstractDistanceMeasurement() = default;

        virtual float calculate_distance(const std::vector<float>&, const std::vector<float>&) const = 0;
    };
}

#endif //KNN_CLASSIFIER_ABSTRACTDISTANCEMEASUREMENT_H