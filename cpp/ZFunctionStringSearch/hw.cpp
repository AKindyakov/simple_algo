#include <iostream>
#include <vector>
#include <string>
#include <cctype>

static inline size_t
findFirstMissmatch(
    const std::string str,
    size_t left,
    size_t right
) {
    size_t len = str.size();
    while (right < len) {
        if (str[left] != str[right]) {
            break;
        }
        ++right;
        ++left;
    }
    return right;
}

std::vector<size_t>
zFunction(
    const std::string& str
) {
    size_t len = str.size();
    if (str.empty()) {
        return std::vector<size_t>(0);
    }
    std::vector<size_t> zRet(len);
    zRet[0] = len;

    if (len == 1) {
        return zRet;
    }

    zRet[1] = findFirstMissmatch(str, 0, 1) - 1;
    for (size_t left = 1, right = 2; right < len; ++right) {
        size_t ff = right - left;
        size_t zf = 0;
        if (left + zRet[left] <= right) { // bad base point - full scan
            zf = findFirstMissmatch(str, 0, right) - right;
            left = right;
        } else if (ff + zRet[ff] > zRet[left]) {
            zf = findFirstMissmatch(str, zRet[ff], left + zRet[left]) - right;
            left = right;
        } else {
            zf = zRet[ff];
        }
        if (right + zf > len) {
            zf = len - right;
        }
        zRet[right] = zf;
    }
    return zRet;
}

int main() {
    std::string str;
    while (std::cin) {
        char ch = std::cin.get();
        if (isgraph(ch)) {
            str.push_back(ch);
        }
    }
    for (const auto& si : str) {
        std::cout << si << ' ';
    }
    std::cout << std::endl;
    for (const auto& zi : zFunction(str)) {
        std::cout << zi << ' ';
    }
    std::cout << std::endl;
    return 0;
}

