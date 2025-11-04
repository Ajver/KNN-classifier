#include "DataNormalization.h"

#include <iostream>

namespace cll {

    void DataNormalization::fit(const std::vector<std::vector<float>> &X) {
        min_values = X[0];
        max_values = X[0];

        for (auto &data_row : X) {
            for (int i = 0; i < data_row.size(); i++) {
                if (data_row[i] < min_values[i]) {
                    min_values[i] = data_row[i];
                }
                if (data_row[i] > max_values[i]) {
                    max_values[i] = data_row[i];
                }
            }
        }

        std::cout << "FIT: ";
        std::cout << std::endl;
        for (int i = 0; i < min_values.size(); i++) {
            std::cout << min_values[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < max_values.size(); i++) {
            std::cout << max_values[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    std::vector<std::vector<float>> DataNormalization::scale(const std::vector<std::vector<float>> &original_rows) const {
        std::vector<std::vector<float>> normalized_rows(original_rows.size());

        for (int i = 0; i < original_rows.size(); i++) {
            normalized_rows[i] = scale(original_rows[i]);
        }

        return normalized_rows;
    }

    std::vector<float> DataNormalization::scale(const std::vector<float> &row) const {
        std::vector<float> normalized_row(row.size());

        for (int feature_idx = 0; feature_idx < row.size(); feature_idx++) {
            const float min_val = min_values[feature_idx];
            const float max_val = max_values[feature_idx];
            normalized_row[feature_idx] = (row[feature_idx] - min_val) / (max_val - min_val);
        }

        return normalized_row;
    }

}
