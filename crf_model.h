#ifndef _CRF_MODEL_H
#define _CRF_MODEL_H
/***
 * charlesliu.cn.bj@gmail.com
 * 2019-11-26
 * crf_model.h
 * crf model load/predict
 */
#include "model.h"
#include "crfpp.h"

#define CRF_MODEL_FILE "model/crf_model"

class CRFModel : public Model {
public:
    CRFModel() {}
    ~CRFModel() {
        if (!_crf_model) {
            delete _crf_model;
        }
    }
    int loadModel(const string &model_path);
    int predict(const string &query, word_seg_t &segs);
private:
    CRFPP::Tagger *_crf_model;
};

#endif
