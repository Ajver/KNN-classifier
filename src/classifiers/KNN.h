#ifndef KNN_KNN_H
#define KNN_KNN_H

#include "AbstractClassifier.h"


namespace cll {

    class KNN : public AbstractClassifier{
    public:
        KNN(int);

        void fit();
        int predict() const;
    };

}

#endif