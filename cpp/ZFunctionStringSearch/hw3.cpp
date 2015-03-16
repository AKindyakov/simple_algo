#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<size_t> z_function(const std::string& str) {
    size_t len = str.length();
    std::vector<size_t> z_ret (len);
    z_ret[0] = len;
    for (size_t i = 1, l = 0, r = 0; i < len; ++i) {
        if (i <= r) {
            z_ret[i] = std::min(r - i + 1, z_ret[i - l]);
        }
        while (i + z_ret[i] < len && str[z_ret[i]] == str[i + z_ret[i]]) {
            ++z_ret[i];
        }
        if (i + z_ret[i] - 1 > r) {
            l = i;
            r = i + z_ret[i] - 1;
        }
    }
    return z_ret;
}

size_t min_period(const std::vector<size_t>& zfun) {
    size_t len = zfun.size();
    for (size_t i = 1; i < len; ++i) {
        if (zfun[i] == zfun[0] - i) {
            // std::cout
            //     << len << " % "
            //     << zfun[0] - zfun[i] << " = "
            //     << len % (zfun[0] - zfun[i])
            //     << std::endl;
            if (len % (zfun[0] - zfun[i]) == 0) {
                return len/(zfun[0] - zfun[i]);
            }
        }
    }
    return 1;
}

int main() {
    std::string str;
    while (std::cin) {
        char ch = std::cin.get();
        if (isprint(ch)) {
            str.push_back(ch);
        }
    }
    std::cout << min_period(z_function(str)) << std::endl;
    return 0;
}

