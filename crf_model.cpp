#include "crf_model.h"
#include <iostream>

int CRFModel::loadModel(const string &model_path) {
    if (!CRFPP::createTagger1(model_path.c_str())) {
        std::cout << "Load CRF model failed!!!" << std::endl;
        return -1;
    }

    return 0;
}

int CRFModel::predict(const string &query, word_seg_t &segs) {


    return 0;
}
