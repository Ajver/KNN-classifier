#include <gtest/gtest.h>

#include "../src/classifiers/tools/MinMaxScaler.h"


TEST(MinMaxScaler, ScaleVector) {
    cll::MinMaxScaler scaler;
    std::vector<std::vector<float>> X{
        {0,   0,  -2,  2,  1,  1., },
        {5,  -10,  3,  3,  2,  2., },
        {10,  -3,  6,  0,  3,  3., },
    };
    scaler.fit(X);
    std::vector<float> scaled = scaler.scale(std::vector<float>{7, -4, 4, 2., 1, 3});

    EXPECT_FLOAT_EQ(scaled[0], 0.7);
    EXPECT_FLOAT_EQ(scaled[1], 0.6);
    EXPECT_FLOAT_EQ(scaled[2], 0.75);
    EXPECT_FLOAT_EQ(scaled[3], 2./3.);
    EXPECT_FLOAT_EQ(scaled[4], 0.0);
    EXPECT_FLOAT_EQ(scaled[5], 1.0);
}


TEST(MinMaxScaler, ScaleMultipleSamples) {
    cll::MinMaxScaler scaler;
    std::vector<std::vector<float>> X{
        {0,   0,  -2,  2,  1,  1., },
        {5,  -10,  3,  3,  2,  2., },
        {10,  -3,  6,  0,  3,  3., },
    };
    scaler.fit(X);
    std::vector<std::vector<float>> scaled = scaler.scale(std::vector<std::vector<float>>{
        {7, -4, 4, 2., 1, 3},
        {1, -9, 4, 3., 3, 1},
    });

    EXPECT_FLOAT_EQ(scaled[0][0], 0.7);
    EXPECT_FLOAT_EQ(scaled[0][1], 0.6);
    EXPECT_FLOAT_EQ(scaled[0][2], 0.75);
    EXPECT_FLOAT_EQ(scaled[0][3], 2./3.);
    EXPECT_FLOAT_EQ(scaled[0][4], 0.0);
    EXPECT_FLOAT_EQ(scaled[0][5], 1.0);

    EXPECT_FLOAT_EQ(scaled[1][0], 0.1);
    EXPECT_FLOAT_EQ(scaled[1][1], 0.1);
    EXPECT_FLOAT_EQ(scaled[1][2], 0.75);
    EXPECT_FLOAT_EQ(scaled[1][3], 1.0);
    EXPECT_FLOAT_EQ(scaled[1][4], 1.0);
    EXPECT_FLOAT_EQ(scaled[1][5], 0.0);
}
