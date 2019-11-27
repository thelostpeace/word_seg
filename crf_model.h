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

typedef struct {
    string query;
    vector<int> begin_idx;
    vector<int> end_idx;
} crf_query_t;

class CRFModel : public Model {
public:
    CRFModel() {
        _crf_model = NULL;
    }
    ~CRFModel() {
        if (!_crf_model) {
            delete _crf_model;
        }
    }
    int loadModel(const string &model_path);
    int predict(const string &query, word_seg_t &segs);
    void parse_query(const string &query, crf_query_t &crf_query);
private:
    CRFPP::Tagger *_crf_model;
};

#endif
