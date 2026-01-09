#include "NoScaler.h"

namespace cll {

    void NoScaler::fit(const vector<vector<float>>& _) {
        // We're not scaling anything
        // Hence, no operation here
    }

    vector<vector<float>> NoScaler::scale(const vector<vector<float>>& original_rows) const {
        std::vector<std::vector<float>> normalized_rows(original_rows.size());

        for (int i = 0; i < original_rows.size(); i++) {
            normalized_rows[i] = scale(original_rows[i]);
        }

        return normalized_rows;
    }

    vector<float> NoScaler::scale(const vector<float>& row) const {
        // Return unmodified copy
        return row;
    }

}
