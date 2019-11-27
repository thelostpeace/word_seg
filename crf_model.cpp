#include "crf_model.h"
#include <iostream>
#include "common.h"

// 以unicode长度去截取字符串
void CRFModel::parse_query(const string &query, crf_query_t &crf_query) {
    vector<string> unicode_query;
    WordSeg::unicode_parse(query, unicode_query);
    crf_query.query = WordSeg::join(unicode_query, "\n");
    crf_query.query += "\n";

    size_t pos = 0; 
    for (auto &ch : unicode_query) {
        crf_query.begin_idx.push_back(pos);
        crf_query.end_idx.push_back(pos + ch.length() - 1);
        pos += ch.length();
    }
}

int CRFModel::loadModel(const string &model_path) {
    _crf_model = CRFPP::createTagger1(model_path.c_str());
    if (!_crf_model) {
        std::cout << "Load CRF model failed!!!" << std::endl;
        return -1;
    }

    return 0;
}

int CRFModel::predict(const string &query, word_seg_t &segs) {
    crf_query_t crf_query;
    parse_query(query, crf_query);
    string seg = _crf_model->predict(crf_query.query.c_str());

    size_t begin = 0;
    for (size_t i = 0; i < seg.length(); ++i) {
        switch (seg[i]) {
            case 'S':
                begin = crf_query.begin_idx[i];
                break;
            case 'B':
                begin = crf_query.begin_idx[i];
                continue;
            case 'M':
                continue;
            case 'E':
                break;
            default:
                std::cout << "error!!!" << std::endl;
                return -1;
        }
        segs.tokens.push_back(query.substr(begin, crf_query.end_idx[i] - begin + 1));
        segs.begin_idx.push_back(begin);
        segs.end_idx.push_back(crf_query.end_idx[i]);
    }

    std::cout << "query: " << query << std::endl;
    std::cout << "segs: " << WordSeg::join(segs.tokens, "|") << std::endl;

    return 0;
}
