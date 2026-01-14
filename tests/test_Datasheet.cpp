#include <fstream>
#include <gtest/gtest.h>

#include "../src/classifiers/tools/Datasheet.h"

using namespace std;
using namespace cll;


void create_file(const string& path, const string& content) {
    ofstream file(path);
    ASSERT_TRUE(file.is_open());

    file << content;

    file.close();
}


string read_file(const string& path) {
    ifstream file(path);
    assert(file.is_open());

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    string content(buffer.str());
    return content;
}


TEST(DatasheetTest, LoadFromCSV) {
    create_file("tests/test1.csv", "y1,2.2,3.1\ny2, 5.2, 6.1 \ny1, 8.4, 9.5");
    Datasheet data = Datasheet::load_from_csv("tests/test1.csv", 0, 0);

    ASSERT_EQ(data.X.size(), 3);
    ASSERT_EQ(data.Y.size(), 3);

    ASSERT_EQ(data.X[0].size(), 2);
    ASSERT_EQ(data.X[1].size(), 2);
    ASSERT_EQ(data.X[2].size(), 2);

    EXPECT_NEAR(data.X[0][0], 2.2, 1e-3);
    EXPECT_NEAR(data.X[0][1], 3.1, 1e-3);
    EXPECT_NEAR(data.X[1][0], 5.2, 1e-3);
    EXPECT_NEAR(data.X[1][1], 6.1, 1e-3);
    EXPECT_NEAR(data.X[2][0], 8.4, 1e-3);
    EXPECT_NEAR(data.X[2][1], 9.5, 1e-3);

    EXPECT_EQ(data.Y[0], 1);
    EXPECT_EQ(data.Y[1], 2);
    EXPECT_EQ(data.Y[2], 1);

    EXPECT_EQ(data.class_to_int["y1"], 1);
    EXPECT_EQ(data.class_to_int["y2"], 2);
}


TEST(DatasheetTest, LoadFromCSV_LastColumnAsClass) {
    create_file("tests/test2.csv", "1,2,3,AAA\n2, 3, 4.0,BBB\n 3,4,5,CCC");
    Datasheet data = Datasheet::load_from_csv("tests/test2.csv", 3, 0);

    ASSERT_EQ(data.X.size(), 3);
    ASSERT_EQ(data.Y.size(), 3);

    ASSERT_EQ(data.X[0].size(), 3);
    ASSERT_EQ(data.X[1].size(), 3);
    ASSERT_EQ(data.X[2].size(), 3);

    EXPECT_NEAR(data.X[0][0], 1, 1e-3);
    EXPECT_NEAR(data.X[0][1], 2, 1e-3);
    EXPECT_NEAR(data.X[0][2], 3, 1e-3);
    EXPECT_NEAR(data.X[1][0], 2, 1e-3);
    EXPECT_NEAR(data.X[1][1], 3, 1e-3);
    EXPECT_NEAR(data.X[1][2], 4, 1e-3);
    EXPECT_NEAR(data.X[2][0], 3, 1e-3);
    EXPECT_NEAR(data.X[2][1], 4, 1e-3);
    EXPECT_NEAR(data.X[2][2], 5, 1e-3);

    EXPECT_EQ(data.Y[0], 1);
    EXPECT_EQ(data.Y[1], 2);
    EXPECT_EQ(data.Y[2], 3);

    EXPECT_EQ(data.class_to_int["AAA"], 1);
    EXPECT_EQ(data.class_to_int["BBB"], 2);
    EXPECT_EQ(data.class_to_int["CCC"], 3);
}


TEST(DatasheetTest, LoadFromCSV_SkipOneRow) {
    create_file("tests/test2.csv", "1,1,1\n2,2,2\n3,3,3\n4,4,4\n5,5,5");
    Datasheet data = Datasheet::load_from_csv("tests/test2.csv", 0, 1);

    ASSERT_EQ(data.X.size(), 4);
    ASSERT_EQ(data.Y.size(), 4);

    ASSERT_EQ(data.X[0].size(), 2);
    ASSERT_EQ(data.X[1].size(), 2);
    ASSERT_EQ(data.X[2].size(), 2);
    ASSERT_EQ(data.X[3].size(), 2);

    // No row 1
    EXPECT_NEAR(data.X[0][0], 2, 1e-3);
    EXPECT_NEAR(data.X[0][1], 2, 1e-3);
    EXPECT_NEAR(data.X[1][0], 3, 1e-3);
    EXPECT_NEAR(data.X[1][1], 3, 1e-3);
    EXPECT_NEAR(data.X[2][0], 4, 1e-3);
    EXPECT_NEAR(data.X[2][1], 4, 1e-3);
    EXPECT_NEAR(data.X[3][0], 5, 1e-3);
    EXPECT_NEAR(data.X[3][1], 5, 1e-3);

    EXPECT_EQ(data.Y[0], 1);
    EXPECT_EQ(data.Y[1], 2);
    EXPECT_EQ(data.Y[2], 3);
    EXPECT_EQ(data.Y[3], 4);

    EXPECT_EQ(data.class_to_int["2"], 1);
    EXPECT_EQ(data.class_to_int["3"], 2);
    EXPECT_EQ(data.class_to_int["4"], 3);
    EXPECT_EQ(data.class_to_int["5"], 4);
}


TEST(DatasheetTest, LoadFromCSV_SkipTwoRows) {
    create_file("tests/test2.csv", "1,1,1\n2,2,2\n3,3,3\n4,4,4\n5,5,5");
    Datasheet data = Datasheet::load_from_csv("tests/test2.csv", 0, 2);

    ASSERT_EQ(data.X.size(), 3);
    ASSERT_EQ(data.Y.size(), 3);

    ASSERT_EQ(data.X[0].size(), 2);
    ASSERT_EQ(data.X[1].size(), 2);
    ASSERT_EQ(data.X[2].size(), 2);

    // No rows 1 and 2
    EXPECT_NEAR(data.X[0][0], 3, 1e-3);
    EXPECT_NEAR(data.X[0][1], 3, 1e-3);
    EXPECT_NEAR(data.X[1][0], 4, 1e-3);
    EXPECT_NEAR(data.X[1][1], 4, 1e-3);
    EXPECT_NEAR(data.X[2][0], 5, 1e-3);
    EXPECT_NEAR(data.X[2][1], 5, 1e-3);

    EXPECT_EQ(data.Y[0], 1);
    EXPECT_EQ(data.Y[1], 2);
    EXPECT_EQ(data.Y[2], 3);

    EXPECT_EQ(data.class_to_int["3"], 1);
    EXPECT_EQ(data.class_to_int["4"], 2);
    EXPECT_EQ(data.class_to_int["5"], 3);
}

TEST(DatasheetTest, SaveToCSV) {
    vector<vector<float>> X {
        {1, 2, 3},
        {4, 5, 6},
    };
    vector<int> Y {1, 2};

    map<string, int> class_to_int {
        {"class1", 1},
        {"class2", 2},
    };
    map<int, string> int_to_class {
        {1, "class1"},
        {2, "class2"},
    };

    Datasheet data {X, Y, class_to_int, int_to_class};
    data.save_as_csv("tests/test_save1.csv", {"f1,f2,f3,class"});

    EXPECT_EQ(read_file("tests/test_save1.csv"), "f1,f2,f3,class\n1,2,3,class1\n4,5,6,class2\n");
}

TEST(DatasheetTest, TrainTestSplit) {
    srand(42);  // For test consistency

    create_file("tests/test2.csv", "1,1,1\n2,2,2\n3,3,3\n4,4,4\n5,5,5");
    Datasheet data = Datasheet::load_from_csv("tests/test2.csv", 0, 0);

    pair train_test_split = Datasheet::train_test_split(data, 0.6, 42);
    Datasheet train_data = train_test_split.first;
    Datasheet test_data = train_test_split.second;

    ASSERT_EQ(train_data.X.size(), 3);
    ASSERT_EQ(train_data.Y.size(), 3);

    ASSERT_EQ(test_data.X.size(), 2);
    ASSERT_EQ(test_data.Y.size(), 2);

    EXPECT_NEAR(train_data.X[0][0], 3, 1e-3);
    EXPECT_NEAR(train_data.X[0][1], 3, 1e-3);
    EXPECT_EQ(train_data.Y[0], 3);

    EXPECT_NEAR(train_data.X[1][0], 4, 1e-3);
    EXPECT_NEAR(train_data.X[1][1], 4, 1e-3);
    EXPECT_EQ(train_data.Y[1], 4);

    EXPECT_NEAR(train_data.X[2][0], 5, 1e-3);
    EXPECT_NEAR(train_data.X[2][1], 5, 1e-3);
    EXPECT_EQ(train_data.Y[2], 5);

    EXPECT_NEAR(test_data.X[0][0], 2, 1e-3);
    EXPECT_NEAR(test_data.X[0][1], 2, 1e-3);
    EXPECT_EQ(test_data.Y[0], 2);

    EXPECT_NEAR(test_data.X[1][0], 1, 1e-3);
    EXPECT_NEAR(test_data.X[1][1], 1, 1e-3);
    EXPECT_EQ(test_data.Y[1], 1);
}

