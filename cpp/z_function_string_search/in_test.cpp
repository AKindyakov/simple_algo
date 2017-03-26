#include "zfunction.h"

#include <iostream>
#include <sstream>
#include <string>

#include "../simple_algo_util/simple_exception.h"
#include "../simple_algo_util/unit_test.h"

std::vector<unsigned> z_function (std::string s) {
    unsigned n = s.length();
    std::vector<unsigned> z (n);
    for (unsigned i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = std::min(r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    z[0] = n;
    return z;
}

std::vector<unsigned> z_function_trivial (std::string s) {
    unsigned n = s.length();
    std::vector<unsigned> z (n);
    for (unsigned i=1; i<n; ++i)
        while (i + z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
    z[0] = n;
    return z;
}

unsigned
findFirstMissmatch(
    const std::string str,
    unsigned ss,
    unsigned forward
) {
    unsigned len = str.size();
    while (forward < len) {
        if (str[ss] != str[forward]) {
            break;
        }
        ++forward;
        ++ss;
    }
    return forward;
}

std::vector<unsigned>
modZFunction(
    const std::string& str
) {
    unsigned len = str.size();
    if (str.empty()) {
        return std::vector<unsigned>(0);
    }
    std::vector<unsigned> zzz(len);
    zzz[0] = len;

    if (len == 1) {
        return zzz;
    }

    zzz[1] = findFirstMissmatch(str, 0, 1) - 1;
    for (unsigned ss = 1, forward = 2; forward < len; ++forward) {
        unsigned ff = forward - ss;
        unsigned zf = 0;
        if (ss + zzz[ss] <= forward) { // bad base point - full scan
            zf = findFirstMissmatch(str, 0, forward) - forward;
            ss = forward;
        } else if (ff + zzz[ff] > zzz[ss]) {
            zf = findFirstMissmatch(str, zzz[ff], ss + zzz[ss]) - forward;
            ss = forward;
        } else {
            zf = zzz[ff];
        }
        if (forward + zf > len) {
            zf = len - forward;
        }
        zzz[forward] = zf;
    }
    return zzz;
}

int main() {
    std::string str;
    while (std::cin) {
        char ch = std::cin.get();
        if (isalnum(ch)) {
            str.push_back(ch);
        }
    }

    auto z_right = z_function(str);
    auto z_right_t = z_function_trivial(str);

    TestSomeFunction(
        z_right,
        modZFunction,
        str
    );

    TestSomeFunction(
        z_right_t,
        modZFunction,
        str
    );
    return 0;
}
