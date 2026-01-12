#include <cassert>
#include "EulerDistanceSquaredMeasurement.h"

namespace cll {

    float EulerDistanceSquaredMeasurement::calculate_distance(const std::vector<float> &a, const std::vector<float> &b) const {
        // Calculates distance squared (because we don't need to waste computation power on square-rooting it)
        // We only care about "closest" objects, don't need to know the exact distance

        assert(a.size() == b.size());

        float sum = 0;
        for (int i = 0; i < a.size(); i++) {
            float diff = a[i] - b[i];
            sum += diff * diff;
        }

        return sum;
    }

}