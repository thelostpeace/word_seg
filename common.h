#ifndef _COMMON_H
#define _COMMON_H
/***
 * charlesliu.cn.bj@gmail.com
 * 2019-11-27
 * common.h
 * common functions
 */
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

namespace WordSeg {

void unicode_parse(const string &query, vector<string> &output) {
    output.clear();
    size_t begin_idx = 0;
    for (size_t end_idx = 1; end_idx < query.length(); ++end_idx) {
        if ((query[end_idx] & 0xC0) == 0x80) {
            continue;
        }
        output.push_back(query.substr(begin_idx, end_idx - begin_idx));
        begin_idx = end_idx;
    }
    output.push_back(query.substr(begin_idx));
}

string join(vector<string> &list, const string &delim) {
    string joined = "";
    for (size_t i = 0; i < list.size() - 1; ++i) {
        joined += list[i] + delim;
    }
    if (list.size() >= 1) {
        joined += list[list.size() - 1];
    }

    return joined;
}

} // end of namespace WordSeg

#endif
