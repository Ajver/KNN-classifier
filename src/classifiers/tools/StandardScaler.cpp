#include "StandardScaler.h"

#include <cmath>
#include <iostream>
#include <ostream>

using namespace std;

namespace cll {

    void StandardScaler::fit(const vector<vector<float>>& X) {
        mean_values.resize(X[0].size());
        std_values.resize(X[0].size());

        for (int i = 0; i < mean_values.size(); i++) {
            mean_values[i] = 0.0;
            std_values[i] = 0.0;
        }

        for (auto &data_row : X) {
            for (int i = 0; i < data_row.size(); i++) {
                mean_values[i] += data_row[i];
            }
        }
        int samples = X.size();
        for (int i = 0; i < mean_values.size(); i++) {
            mean_values[i] /= samples;
        }

        for (auto &data_row : X) {
            for (int i = 0; i < data_row.size(); i++) {
                std_values[i] += std::powf(mean_values[i] - data_row[i], 2);
            }
        }
        for (int i = 0; i < std_values.size(); i++) {
            std_values[i] = sqrtf(std_values[i]/samples);
        }
    }

    vector<vector<float>> StandardScaler::scale(const vector<vector<float>>& original_rows) const {
        std::vector<std::vector<float>> normalized_rows(original_rows.size());

        for (int i = 0; i < original_rows.size(); i++) {
            normalized_rows[i] = scale(original_rows[i]);
        }

        return normalized_rows;
    }

    vector<float> StandardScaler::scale(const vector<float>& row) const {
        std::vector<float> normalized_row(row.size());

        for (int feature_idx = 0; feature_idx < row.size(); feature_idx++) {
            const float mean_val = mean_values[feature_idx];
            const float std_val = std_values[feature_idx];
            normalized_row[feature_idx] = (row[feature_idx] - mean_val) / std_val;
        }

        return normalized_row;
    }

}