//
// Created by dom on 22/10/2025.
//

#include "Datasheet.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


namespace cll {
    Datasheet Datasheet::load_from_csv(const std::string& filepath, int classes_column_idx, int skip_rows) {
        std::vector<std::vector<float>> X;
        std::vector<int> Y;
        std::map<std::string, int> class_to_int{};
        std::map<int, std::string> int_to_class{};

        std::ifstream file(filepath);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << std::endl;
            Datasheet ds{X, Y, class_to_int, int_to_class};
            return ds;
        }

        std::string line;
        while (getline(file, line)) {
            if (skip_rows-- > 0) {
                continue;
            }

            std::vector<float> row;
            std::stringstream ss(line);
            std::string cell;

            int nth_cell = 0;
            while (getline(ss, cell, ',')) {
                if (nth_cell++ != classes_column_idx) {
                    row.push_back(stof(cell));
                }else {
                    // It's the Y column!
                    if (class_to_int.count(cell) == 0) {
                        // A new class!
                        class_to_int[cell] = class_to_int.size() + 1;
                        int_to_class[class_to_int[cell]] = cell;
                    }
                    Y.push_back(class_to_int[cell]);
                }
            }

            if (!row.empty()) {
                X.push_back(row);
            }
        }

        file.close();

        Datasheet ds{X, Y, class_to_int, int_to_class};

        return ds;
    }

    std::pair<Datasheet, Datasheet> Datasheet::train_test_split(Datasheet &ds, float train_ratio) {
        size_t train_size =  ds.X.size() * train_ratio;
        size_t test_size = ds.X.size() - train_size;

        Datasheet train_ds = ds;
        Datasheet test_ds{std::vector<std::vector<float>>(test_size), std::vector<int>(test_size), ds.class_to_int, ds.int_to_class};

        for (int i = 0; i < test_size; i++) {
            size_t random_idx = rand() % test_ds.X.size();
            test_ds.X[i] = train_ds.X[random_idx];
            test_ds.Y[i] = train_ds.Y[random_idx];
            train_ds.X.erase(train_ds.X.begin() + random_idx);
            train_ds.Y.erase(train_ds.Y.begin() + random_idx);
        }

        return std::pair(train_ds, test_ds);
    }

    void Datasheet::save_as_csv(const std::string& filepath, std::vector<std::string> header_row) {
        std::ofstream file(filepath);

        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << filepath << std::endl;
            return;
        }

        if (!header_row.empty()) {
            for (size_t i = 0; i < header_row.size(); i++) {
                file << header_row[i];
                if (i != header_row.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }

        for (size_t i = 0; i < X.size(); ++i) {
            for (size_t j = 0; j < X[i].size(); ++j) {
                file << X[i][j];
                file << ",";
            }

            std::string class_name = int_to_class[Y[i]];
            file << class_name << "\n";
        }

        file.close();
    }

} // cll