#include <iostream>
#include "knuth_moris_pratt.h"

void
testPrefixFunction(
    const std::string& str
) {
    auto p = ComputeStringPrefixFunction(str);
    std::cerr << str << ": [";
    for (auto& i : p) {
        std::cerr << i << ", ";
    }
    std::cerr << "]\n";
}

void
testKnuthMorrisPrattFind(
    const std::string& pattern
    , const std::string& where
) {
    auto r = KnuthMorrisPrattFind(pattern, where);
    std::cerr << pattern << " in " << where << ": [";
    for (auto& i : r) {
        std::cerr << i << ", ";
    }
    std::cerr << "]\n";
}
int main() {
    testPrefixFunction("abacaba");
    testPrefixFunction("abrakadabra");
    testPrefixFunction("PARTICIPATE IN PARACHUTE");
    testKnuthMorrisPrattFind("23", "1234");
    testKnuthMorrisPrattFind("123", "1234");
    testKnuthMorrisPrattFind("234", "1234");
    testKnuthMorrisPrattFind("2", "12322332");
    testKnuthMorrisPrattFind("", "123");
    testKnuthMorrisPrattFind("1", "");
    testKnuthMorrisPrattFind("123", std::string(1 << 20, '0'));
    return 0;
}
