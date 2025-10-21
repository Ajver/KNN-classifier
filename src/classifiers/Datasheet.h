#ifndef KNN_CLASSIFIER_DATASHEET_H
#define KNN_CLASSIFIER_DATASHEET_H
#include <string>
#include <vector>
#include <map>


namespace cll {
    struct Datasheet {
        std::vector<std::vector<float>> X;
        std::vector<int> Y;

        std::map<std::string, int> class_to_int;
        std::map<int, std::string> int_to_class;

        static Datasheet load_from_csv(std::string, int, int=0);

        static std::pair<Datasheet, Datasheet> train_test_split(Datasheet&, float);

    };
} // cll

#endif //KNN_CLASSIFIER_DATASHEET_H