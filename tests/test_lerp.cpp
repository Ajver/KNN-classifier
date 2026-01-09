#include <gtest/gtest.h>

#include "../src/classifiers/tools/lerp.h"

using namespace std;


TEST(TestLerp, lerp) {
    EXPECT_NEAR(lerp(0, 1, 0.3), 0.3, 1e-4);
    EXPECT_NEAR(lerp(0, 2, 0.3), 0.6, 1e-4);
    EXPECT_NEAR(lerp(1, 2, 0.3), 1.3, 1e-4);
    EXPECT_NEAR(lerp(-1, 3, 0.75), 2.0, 1e-4);
    EXPECT_NEAR(lerp(10, 20, 0.6), 16, 1e-4);

    EXPECT_NEAR(lerp(2, 1, 0.75), 1.25, 1e-4);
    EXPECT_NEAR(lerp(1, 0, 0.9), 0.1, 1e-4);
}
