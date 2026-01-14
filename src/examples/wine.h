#ifndef KNN_CLASSIFIER_MNIST_H
#define KNN_CLASSIFIER_MNIST_H

#include "../classifiers/tools/Datasheet.h"

using namespace std;
using namespace cll;


void example_wine() {
    cout << "\nWINE example:\n" << endl;

    Datasheet dataset = Datasheet::load_from_csv("data/wine_dataset.csv", 0, 0);
    cout << "data: " << dataset.X.size() << endl;
    pair train_test_split = Datasheet::train_test_split(dataset, 0.8, 42);
    Datasheet train_data = train_test_split.first;
    Datasheet test_data = train_test_split.second;

    KNN classifier(3, MINMAX);
    classifier.fit(train_data);

    vector<ClassificationResult> preds = classifier.predict(test_data.X);
    size_t n_classes = train_data.class_to_int.size();
    cout << "n_classes: " << n_classes << endl;

    int confusion_matrix[3][3];
    int TP_TN_FP_FN[3][4];
    for (int i = 0; i < n_classes; i++) {
        for (int j = 0; j < n_classes; j++) {
            confusion_matrix[i][j] = 0;
        }
        for (int j = 0; j < 4; j++) {
            TP_TN_FP_FN[i][j] = 0;
        }
    }

    int correct_preds = 0;
    for (int i = 0; i < preds.size(); i++) {
        int pred_class = preds[i].predicted_class;
        int true_class = test_data.Y[i];
        confusion_matrix[true_class-1][pred_class-1]++;

        if (pred_class == true_class) {
            correct_preds++;

            TP_TN_FP_FN[true_class-1][0]++;  // True Positive
        }else {
            TP_TN_FP_FN[pred_class-1][2]++;  // False Positive
            TP_TN_FP_FN[true_class-1][3]++;  // False Negative
        }
    }

    for (int i = 0; i < n_classes; i++) {
        cout << "\t" << i;
    }

    for (int i = 0; i < n_classes; i++) {
        cout << endl << endl << i << "\t";
        for (int j = 0; j < n_classes; j++) {
            cout << confusion_matrix[i][j] << "\t";
        }
    }

    cout << endl << endl;

    for (int i = 0; i < n_classes; i++) {
        float precision = (float)TP_TN_FP_FN[i][0] / (TP_TN_FP_FN[i][2]+TP_TN_FP_FN[i][0]);
        float recall = (float)TP_TN_FP_FN[i][0] / (TP_TN_FP_FN[i][3]+TP_TN_FP_FN[i][0]);
        float f1 = 2*precision*recall / (precision+recall);
        cout << "class " << i+1 << " f1 score: " << f1 << endl;
    }

    cout << "accuracy: " << (float)correct_preds/preds.size() << endl;
}


#endif //KNN_CLASSIFIER_MNIST_H