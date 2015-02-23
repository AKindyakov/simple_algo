#include "zfunction.h"

#include <iostream>
#include <string>

void
testZFunction(
    const std::string& str
) {
    auto z = zFunction(str);
    std::cerr << "\n   ";
    for (size_t i = 0; i < str.size(); ++i) {
        std::cerr << i << ", ";
    }
    std::cerr << "\n   ";
    for (auto& c : str) {
        std::cerr << c << ", ";
    }
    std::cerr << "\n: [";
    for (auto& iz : z) {
        std::cerr << iz << ", ";
    }
    std::cerr << "]\n\n\n";
}

int main() {
    testZFunction("abacaba");
    testZFunction("abcdefghij");
    testZFunction("aaaaaaaaa");
    testZFunction("a");
    testZFunction("");
    testZFunction("abababb");
    return 0;
}
