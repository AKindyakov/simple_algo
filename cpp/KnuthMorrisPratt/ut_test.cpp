#include "knuth_moris_pratt.h"

#include "../SimpleAlgoUtil/simple_exception.h"
#include "../SimpleAlgoUtil/unit_test.h"

#include <iostream>
#include <sstream>
#include <string>

void
testPrefixFunction() {
    TestSomeFunction(
        std::vector<size_t>{0, 0, 0, 1, 0, 1, 0, 1, 2, 3, 4,},
        ComputeStringPrefixFunction,
        "abracadabra"
    );
    TestSomeFunction(
        std::vector<size_t>{0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0,},
        ComputeStringPrefixFunction,
        "PARTICIPATE IN PARACHUTE"
    );
    TestSomeFunction(
        std::vector<size_t>{0, 0, 0, 1, 2, 1,},
        ComputeStringPrefixFunction,
        "abcaba"
    );
}

void
testKmpFind() {
    TestSomeFunction(
        std::vector<size_t>{2,},
        KnuthMorrisPrattFind,
        "must", "I must not fear."
    );
    TestSomeFunction(
        std::vector<size_t>{12,},
        KnuthMorrisPrattFind,
        "mind", "Fear is the mind-killer."
    );
    TestSomeFunction(
        std::vector<size_t>{0,},
        KnuthMorrisPrattFind,
        "Fear", "Fear is the little-death that brings total obliteration."
    );
    TestSomeFunction(
        std::vector<size_t>{15,},
        KnuthMorrisPrattFind,
        "fear.", "I will face my fear."
    );
    TestSomeFunction(
        std::vector<size_t>{30, 45},
        KnuthMorrisPrattFind,
        "me", "I will permit it to pass over me and through me."
    );
    TestSomeFunction(
        std::vector<size_t>{},
        KnuthMorrisPrattFind,
        "When", "And when it has gone past I will turn the inner eye to see its path."
    );
    TestSomeFunction(
        std::vector<size_t>{},
        KnuthMorrisPrattFind,
        "pain", "Where the fear has gone there will be nothing."
    );
    TestSomeFunction(
        std::vector<size_t>{2, 9, 10},
        KnuthMorrisPrattFind,
        "l", "Only I will remain."
    );
}

int main() {
    testPrefixFunction();
    testKmpFind();
    return 0;
}

