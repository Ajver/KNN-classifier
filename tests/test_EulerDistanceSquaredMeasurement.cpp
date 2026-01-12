#include <complex>
#include <gtest/gtest.h>

#include "../src/classifiers/tools/EulerDistanceSquaredMeasurement.h"

using namespace std;
using namespace cll;

TEST(EulerDistanceSquaredMeasurement, TestDistance) {
    EulerDistanceSquaredMeasurement m;

    vector<float> a, b;

    // Distance is squared
    a = {0, 0, 0};
    b = {1, 1, 1};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(b, a), 3, 1e-5);

    a = {0, 0, 0};
    b = {0, 0, 0};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(b, a), 0, 1e-5);

    a = {0, 0, 1};
    b = {1, 1, 1};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(a, b), 2, 1e-5);

    a = {5, -2, 3};
    b = {-3, 4, 2};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(a, b), 101, 1e-5);

    a = {0.2, 0.3, -1.4};
    b = {2.1, 0.4, -1.4};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(a, b), 3.62, 1e-5);

    a = {1, 2, 3, 4};
    b = {4, 3, 2, 1};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(a, b), 20, 1e-5);

    a = {1, 1};
    b = {2, 2};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(a, b), 2, 1e-5);

    a = {4};
    b = {7};
    EXPECT_NEAR(m.calculate_distance(a, b), m.calculate_distance(b, a), 1e-5);
    EXPECT_NEAR(m.calculate_distance(a, b), 9, 1e-5);
}
