#ifndef _MODEL_H
#define _MODEL_H
/***
 * charlesliu.cn.bj@gmail.com
 * model.h
 * 2019-11-25
 * virtual class of models
 */
#include <vector>
#include <string>
using std::vector;
using std::string;

typedef struct {
    vector<string> tokens;
    vector<int> begin_idx;
    vector<int> end_idx;
} word_seg_t;

class Model {
public:
    virtual int loadModel(const string &model_path) = 0;
    virtual int predict(const string &query, word_seg_t &segs) = 0;
};

#endif
