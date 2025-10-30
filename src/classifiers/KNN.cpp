#include "KNN.h"

#include <cassert>
#include <iostream>
#include <map>

#include "tools/EulerDistanceMeasurement.h"


namespace cll {

    KNN::KNN(size_t newK) {
        assert(newK > 0);

        K = newK;
        distance_measurement = new EulerDistanceMeasurement;
    }

    void KNN::fit(std::vector<std::vector<float>> &newX, std::vector<int> &newY) {
        assert(newX.size() == newY.size());
        assert(newX.size() >= K);

        const size_t p = newX[0].size();
        for (int i = 1; i < newX.size(); i++) {
            assert(newX[i].size() == p);
        }

        X = newX;
        Y = newY;

        // Data normalization
        min_values = newX[0];
        max_values = newX[0];

        for (auto data_row : newX) {
            for (int i = 0; i < data_row.size(); i++) {
                if (data_row[i] < min_values[i]) {
                    min_values[i] = data_row[i];
                }
                if (data_row[i] > max_values[i]) {
                    max_values[i] = data_row[i];
                }
            }
        }

        for (auto & data_row : X) {
            for (int feature_idx = 0; feature_idx < data_row.size(); feature_idx++) {
                const float min_val = min_values[feature_idx];
                const float max_val = max_values[feature_idx];
                data_row[feature_idx] = (data_row[feature_idx] - min_val) / (max_val - min_val);
            }
        }
    }

    void KNN::fit(Datasheet &ds) {
        fit(ds.X, ds.Y);
    }

    std::vector<ClassificationResult> KNN::predict(std::vector<std::vector<float>>& predX) const {
        std::vector<ClassificationResult> predY(predX.size());

        for (int i = 0; i < predX.size(); i++) {
            predY[i] = predict(predX[i]);
        }

        return predY;
    }

    struct Neighbor {
        std::vector<float> weights;
        float distance;
        int neigh_class;
    };

    ClassificationResult KNN::predict(std::vector<float> pred_row) const {
        // Normalization
        for (int feature_idx = 0; feature_idx < pred_row.size(); feature_idx++) {
            const float min_val = min_values[feature_idx];
            const float max_val = max_values[feature_idx];
            pred_row[feature_idx] = (pred_row[feature_idx] - min_val) / (max_val - min_val);
        }

        Neighbor* neighbors = new Neighbor[K];
        float max_dist = -1;
        int max_dist_index = -1;
        int filled_neighbors = 0;

        for (int i = 0; i < X.size(); i++) {
            std::vector<float> data_x = X[i];

            float dist = distance_measurement->calculate_distance(pred_row, data_x);

            Neighbor new_ngh = Neighbor{data_x, dist, Y[i]};

            if (filled_neighbors < K) {
                if (dist > max_dist) {
                    max_dist = dist;
                    max_dist_index = filled_neighbors;
                }

                neighbors[filled_neighbors++] = new_ngh;
            }else {
                // We already have K neighbors...

                if (dist < max_dist) {
                    // This neighbor is closer than one of the founded

                    neighbors[max_dist_index] = new_ngh;

                    // We need to find the new max_dist, since we removed the last guy
                    max_dist = neighbors[0].distance;
                    max_dist_index = 0;
                    for (int j = 1; j < K; j++) {
                        if (neighbors[j].distance > max_dist) {
                            max_dist = neighbors[j].distance;
                            max_dist_index = j;
                        }
                    }
                }
            }
        }

        std::map<int, size_t> classes{};

        for (int i = 0; i < K; i++) {
            Neighbor neighbor = neighbors[i];

            // classes[neighbor.neigh_class] = 1
            if (!classes[neighbor.neigh_class]) {
                classes[neighbor.neigh_class] = 1;
            }else {
                classes[neighbor.neigh_class]++;
            }

            // std::cout << " - [";
            // for (auto w : neighbor.weights) {
            //     std::cout << w << ", ";
            // }
            // std::cout << "] = " << neighbor.neigh_class << " " << neighbor.distance << std::endl;
        }

        float confidence = 0.0;
        int pred_class = 0;
        size_t max_preds_count = 0;

        for (const auto& p : classes) {
            if (p.second > max_preds_count) {
                pred_class = p.first;
                max_preds_count = p.second;
                confidence = static_cast<float>(max_preds_count) / K;
            }
            // std::cout << '[' << p.first << "] = " << p.second << '\n';
        }

        delete[] neighbors;

        ClassificationResult result{pred_class, confidence, classes};

        return result;
    }
}
