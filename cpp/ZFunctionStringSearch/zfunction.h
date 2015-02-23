#pragma once

#include <string>
#include <vector>
#include <iostream>

/*
* [ccccccccccccccc]
*      ^    ^
*      s    f
* return number of first mismatch 's'
*/

inline size_t findFirstMissmatch(const std::string str, size_t s, size_t f) {
    std::cerr << " find( " << s << ", " << f << " ): ";
    size_t len = str.size();
    while (f < len) {
        if (str[s] != str[f]) {
            break;
        }
        ++f;
        ++s;
    }
    std::cerr << s << " ";
    return s;
}

std::vector<size_t> zFunction(const std::string& str) {
    size_t len = str.size();
    if (str.empty()) {
        return std::vector<size_t>(0);
    }
    std::vector<size_t> rezult(len);
    rezult[0] = len;

    if (len == 1) {
        return rezult;
    }

    rezult[1] = findFirstMissmatch(str, 0, 1);
    std::cerr << std::endl;

    for (size_t s = 1, f = 2; f < len; ++f) {
        size_t ff = f - s;
        std::cerr
            << "s ["  << s  << "]: '" << str[s] << "' "
            << "f ["  << f  << "]: '" << str[f] << "' "
        ;

        std::cerr << " ff:" << ff << " + z[ff]: " << rezult[ff] << " > " << rezult[s];
        size_t zf = 0;
        if (ff + rezult[ff] > rezult[s]) {
            if (s + rezult[s] <= f) {
                std::cerr << " {1.1} ";
                zf = findFirstMissmatch(str, 0, f); // f + rezult[ff]);
            } else {
                std::cerr << " {1.2} ";
                zf = findFirstMissmatch(str, rezult[s], s + rezult[s]) - 1;
            }
            s = f;
        } else {
            std::cerr << " {2} ";
            zf = rezult[ff];
        }
        if (f + zf > len) {
            zf = len - f;
        }
        rezult[f] = zf;
        std::cerr << "rezult[ " << f << " ] = " << rezult[f];
        std::cerr << std::endl;
    }
    return rezult;
}

