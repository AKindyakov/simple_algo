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

int main() {
    std::string str;
    while (std::cin) {
        char ch = std::cin.get();
        if (isprint(ch)) {
            str.push_back(ch);
        }
    }
    for (const auto& zi : z_function(str)) {
        std::cout << zi << ' ';
    }
    std::cout << std::endl;
    return 0;
}
