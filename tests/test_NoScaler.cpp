#include <gtest/gtest.h>

#include "../src/classifiers/tools/NoScaler.h"


TEST(NoScaler, TestOneVec) {
    cll::NoScaler scaler;
    std::vector<std::vector<float>> X {{1, 2}, {3, 4}};  // may be empty
    scaler.fit(X); // Does nothing

    std::vector<float> x_test {{0.5, 14.3}};
    std::vector<float> result = scaler.scale(x_test);

    EXPECT_NEAR(result[0], 0.5, 1e-5);
    EXPECT_NEAR(result[1], 14.3, 1e-5);
}


TEST(NoScaler, FitNotNeeded) {
    cll::NoScaler scaler;

    // No .fit called

    std::vector<float> x_test {{0.5, 14.3}};
    std::vector<float> result = scaler.scale(x_test);

    EXPECT_NEAR(result[0], 0.5, 1e-5);
    EXPECT_NEAR(result[1], 14.3, 1e-5);
}


TEST(NoScaler, TestMultipleVectors) {
    cll::NoScaler scaler;
    std::vector<std::vector<float>> X {{1, 2}, {3, 4}};  // may be empty
    scaler.fit(X); // Does nothing

    std::vector<std::vector<float>> X_test {{0.5, 14.3}, {-92.12, 0.0}};
    std::vector<std::vector<float>> results = scaler.scale(X_test);

    EXPECT_NEAR(results[0][0], 0.5, 1e-5);
    EXPECT_NEAR(results[0][1], 14.3, 1e-5);
    EXPECT_NEAR(results[1][0], -92.12, 1e-5);
    EXPECT_NEAR(results[1][1], 0.0, 1e-5);
}