#include <gtest/gtest.h>

#include "../src/classifiers/tools/StandardScaler.h"


TEST(StandardScalers, ScaleVector) {
    cll::StandardScaler scaler;
    std::vector<std::vector<float>> X{
        {0,   0,   1 },
        {5,  -10,  2 },
        {5,  -4,   3 },
        {10,  -2,  4 },
    };
    scaler.fit(X);

    std::vector<float> scaled = scaler.scale(std::vector<float>{3, -2, 1});
    EXPECT_NEAR(scaled[0], -0.5657, 1e-4);
    EXPECT_NEAR(scaled[1], 0.5345, 1e-4);
    EXPECT_NEAR(scaled[2], -1.3416, 1e-4);
}

TEST(StandardScalers, ScaleMultipleSamples) {
    cll::StandardScaler scaler;
    std::vector<std::vector<float>> X{
        {0,   0,   1 },
        {5,  -10,  2 },
        {5,  -4,   3 },
        {10,  -2,  4 },
    };
    scaler.fit(X);

    std::vector<std::vector<float>> scaled = scaler.scale(std::vector<std::vector<float>>{
        {3, -2, 1},
        {4, 5, 6},
    });

    EXPECT_NEAR(scaled[0][0], -0.5657, 1e-4);
    EXPECT_NEAR(scaled[0][1], 0.5345, 1e-4);
    EXPECT_NEAR(scaled[0][2], -1.3416, 1e-4);

    EXPECT_NEAR(scaled[1][0], -0.2828, 1e-4);
    EXPECT_NEAR(scaled[1][1], 2.4053, 1e-4);
    EXPECT_NEAR(scaled[1][2], 3.1305, 1e-4);
}