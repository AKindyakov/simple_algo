#include "zfunction.h"

/*
* [ccccccccccccccc]
*      ^    ^
*      s    f
* return number of first mismatch 's'
*/
static inline size_t
findFirstMissmatch(
    const std::string str,
    size_t s,
    size_t f
) {
    size_t len = str.size();
    while (f < len) {
        if (str[s] != str[f]) {
            break;
        }
        ++f;
        ++s;
    }
    return f;
}

std::vector<size_t>
zFunction(
    const std::string& str
) {
    size_t len = str.size();
    if (str.empty()) {
        return std::vector<size_t>(0);
    }
    std::vector<size_t> z(len);
    z[0] = len;

    if (len == 1) {
        return z;
    }

    z[1] = findFirstMissmatch(str, 0, 1) - 1;
    for (size_t s = 1, f = 2; f < len; ++f) {
        size_t ff = f - s;
        size_t zf = 0;
        if (s + z[s] <= f) { // bad base point - full scan
            zf = findFirstMissmatch(str, 0, f) - f;
            s = f;
        } else if (ff + z[ff] > z[s]) {
            zf = findFirstMissmatch(str, z[ff], s + z[s]) - f;
            s = f;
        } else {
            zf = z[ff];
        }
        if (f + zf > len) {
            zf = len - f;
        }
        z[f] = zf;
    }
    return z;
}

