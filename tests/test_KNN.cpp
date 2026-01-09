#include <gtest/gtest.h>

#include "../src/classifiers/KNN.h"


TEST(KNNTest, PredictK_1) {
    std::vector<std::vector<float>> X {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 2},
        {-3, 0, 1},
    };

    std::vector<int> y {
        1,
        2,
        3,
        4,
    };

    cll::KNN knn(1);
    knn.fit(X, y);

    EXPECT_EQ(knn.predict({0, 0.4, 0}).predicted_class, 1);
    EXPECT_EQ(knn.predict({0, 0.3, 0.4}).predicted_class, 1);
    EXPECT_EQ(knn.predict({0, -1, 0}).predicted_class, 1);

    EXPECT_EQ(knn.predict({0, 1.0, 0}).predicted_class, 2);
    EXPECT_EQ(knn.predict({0, 0.6, 0}).predicted_class, 2);

    EXPECT_EQ(knn.predict({0, 0.5, 1.3}).predicted_class, 3);

    EXPECT_EQ(knn.predict({-2, 0.1, 0.1}).predicted_class, 4);
}

TEST(KNNTest, PredictK_3) {
    std::vector<std::vector<float>> X {
        {0.0, 0.0, 0.0},
        {0.1, 0.0, 0.0},
        {0.0, 0.1, 0.0},
        {5.0, 5.0, 5.0},
        {5.1, 5.0, 5.0},
        {5.0, 5.1, 5.0},
        {10.0, 10.0, 10.0},
        {10.1, 10.0, 10.0},
        {10.0, 10.1, 10.0},
        {0.0, 0.0, 10.0}
    };

    std::vector<int> y {1, 1, 1, 2, 2, 2, 3, 3, 3, 4};

    cll::KNN knn(3);
    knn.fit(X, y);

    EXPECT_EQ(knn.predict({0.05, 0.05, 0.0}).predicted_class, 1);
    EXPECT_EQ(knn.predict({5.05, 5.05, 5.0}).predicted_class, 2);
    EXPECT_EQ(knn.predict({10.05, 10.05, 10.0}).predicted_class, 3);
    EXPECT_EQ(knn.predict({0.0, 0.0, 5.0}).predicted_class, 1);
}


TEST(KNNTest, PredictConfidenceAndClassCounts) {
    /*

      1         2

      A         B

      1         2

     */
    std::vector<std::vector<float>> X {
        {0.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0},
        {1.0, 0.0},
    };

    std::vector<int> y {1, 2, 1, 2};

    cll::KNN knn(3);
    knn.fit(X, y);

    std::vector<float> A {0.0, 0.5};
    EXPECT_EQ(knn.predict(A).predicted_class, 1);
    EXPECT_NEAR(knn.predict(A).confidence, 2./3, 1e-5);
    EXPECT_EQ(knn.predict(A).classes[1], 2);
    EXPECT_EQ(knn.predict(A).classes[2], 1);

    std::vector<float> B {1.0, 0.5};
    EXPECT_EQ(knn.predict(B).predicted_class, 2);
    EXPECT_NEAR(knn.predict(B).confidence, 2./3, 1e-5);
    EXPECT_EQ(knn.predict(B).classes[1], 1);
    EXPECT_EQ(knn.predict(B).classes[2], 2);
}


TEST(KNNTest, PredictMultipleK_1) {
    std::vector<std::vector<float>> X {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 2},
        {-3, 0, 1},
    };

    std::vector<int> y {
        1,
        2,
        3,
        4,
    };

    cll::KNN knn(1);
    knn.fit(X, y);

    std::vector<std::vector<float>> Xtest {
        {0, 0.4, 0},
        {0, -1, 0},
        {0, 1.0, 0},
        {0, 0.6, 0},
        {0, 0.5, 1.3},
        {-2, 0.1, 0.1},
    };
    std::vector<cll::ClassificationResult> results = knn.predict(Xtest);

    EXPECT_EQ(results[0].predicted_class, 1);
    EXPECT_EQ(results[1].predicted_class, 1);
    EXPECT_EQ(results[2].predicted_class, 2);
    EXPECT_EQ(results[3].predicted_class, 2);
    EXPECT_EQ(results[4].predicted_class, 3);
    EXPECT_EQ(results[5].predicted_class, 4);
}

TEST(KNNTest, NormalScaler) {
    /*
        - Big difference in X axis
        - Small difference in Y axis

    Before normalisation, A is closer to 2...

                                        A
                        1

      1                                     2

                        2

    But after normalisation, A is closer to 1...

           A
         1
      1     2
         2

    */
    std::vector<std::vector<float>> X {
            {0, 1},
            {10, 0},
            {20, 1},
            {10, 2},
        };

    std::vector<int> y {1, 2, 2, 1};

    cll::KNN knn_no_scaler(1, cll::NONE);
    cll::KNN knn_normal_scaler(1, cll::NORMALIZE);
    knn_no_scaler.fit(X, y);
    knn_normal_scaler.fit(X, y);

    std::vector<float> A = {18.0, 2.3};
    EXPECT_EQ(knn_no_scaler.predict(A).predicted_class, 2);

    EXPECT_EQ(knn_normal_scaler.predict(A).predicted_class, 1);
}
