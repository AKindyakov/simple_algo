#include "knuth_moris_pratt.h"

#include <iostream>
#include <vector>
#include <string>

std::vector<size_t>
ComputeStringPrefixFunction(
    const std::string& str
) {
    size_t len = str.size();
    std::vector<size_t> L(len);
    L[0] = 0;
    size_t k = 0;
    for (size_t i = 1; i < len; ++i) {
        while (k > 0 && str[k] != str[i]) {
            std::cerr << "L[ " << k-1 << " ]\n";
            k = L[k-1];
        }
        if (str[k] == str[i]) {
            ++k;
        }
        L[i] = k;
    }
    return L;
}

std::vector<size_t>
KnuthMorrisPrattFind(
    const std::string& pattern
    , const std::string& where
) {
    if (pattern.empty()) {
        return std::vector<size_t>();
    }
    auto prefixes =  ComputeStringPrefixFunction(pattern);
    auto len = where.size();
    auto patternLen = pattern.size();
    size_t f = 0;
    size_t s = 0;
    /*
    * ...abcdef...
    *     ^  ^
    *     s  f
    */
    std::vector<size_t> rez;
    while (f < len) {
        //* debug */ std::cerr << f << " of " << len << std::endl;
        size_t k = f - s;
        if (where[f] == pattern[k]) {
            ++f;
            if (k + 1 == patternLen) {
                rez.push_back(s);
                s = f;
            }
        } else {
            auto p = prefixes[k];
            if (p == 0) {
                if (s == f) {
                    ++f;
                }
                s = f;
            } else {
                s += p;
            }
        }
    }
    return rez;
}
