#ifndef _FACTORY_H
#define _FACTORY_H
/***
 * charlesliu.cn.bj@gmail.com
 * 2019-11-25
 * factory.h
 * model factory, easy to extend
 */
#include "model.h"
#include "crf_model.h"

class ModelMaker {
public:
    static Model *makeModel(const string model) {
        return _model_map.at(model);
    }
    static ModelMaker *getInstance() {
        return &_model_maker;
    }
private:
    ModelMaker() {
        init();
    }
    ~ModelMaker() {
        for (auto &model : _model_map) {
            if (model.second != NULL) {
                delete model.second;
            }
        }
    }
    static void init() {
        _model_map["CRF"] = new CRFModel();
    }
private:
    map<string, Model *> _model_map;
    static ModelMaker _model_maker;
};

#endif
