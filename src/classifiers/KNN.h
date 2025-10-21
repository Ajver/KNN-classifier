#ifndef KNN_KNN_H
#define KNN_KNN_H

#include "AbstractClassifier.h"


namespace cll {

    class KNN : public AbstractClassifier {
    public:
        KNN(size_t);

        void fit(std::vector<std::vector<float>>&, std::vector<int>&) override;
        std::vector<int> predict(std::vector<std::vector<float>>&) const override;
        int predict(std::vector<float>&) const override;
    private:
        size_t K;
        std::vector<std::vector<float>> X;
        std::vector<int> Y;
    };

}

#endif