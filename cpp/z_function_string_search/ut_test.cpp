#include "zfunction.h"

#include <iostream>
#include <sstream>
#include <string>

#include "../simple_algo_util/simple_exception.h"
#include "../simple_algo_util/unit_test.h"

void
testsZFunction() {
    TestSomeFunction(
        std::vector<size_t>{7, 0, 1, 0, 3, 0, 1, },
        zFunction,
        "abacaba"
    );
    TestSomeFunction(
        std::vector<size_t>{10, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        zFunction,
        "abcdefghij"
    );
    TestSomeFunction(
        std::vector<size_t>{3, 2, 1, },
        zFunction,
        "aaa"
    );
    TestSomeFunction(
        std::vector<size_t>{9, 8, 7, 6, 5, 4, 3, 2, 1, },
        zFunction,
        "aaaaaaaaa"
    );
    TestSomeFunction(
        std::vector<size_t>{1, },
        zFunction,
        "a"
    );
    TestSomeFunction(
        std::vector<size_t>{},
        zFunction,
        ""
    );
    TestSomeFunction(
        std::vector<size_t>{7, 0, 4, 0, 2, 0, 0, },
        zFunction,
        "abababb"
    );
    TestSomeFunction(
        std::vector<size_t>{10, 0, 0, 6, 0, 0, 3, 0, 0, 0, },
        zFunction,
        "abcabcabcc"
    );
    TestSomeFunction(
        std::vector<size_t>{11, 0, 0, 1, 0, 1, 0, 4, 0, 0, 1,},
        zFunction,
        "abracadabra"
    );
    TestSomeFunction(
        std::vector<size_t>{16, 0, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 2, 0, 0, 1},
        zFunction,
        "abcdabscabcdabia"
    );
    TestSomeFunction(
        std::vector<size_t>{7, 2, 1, 0, 2, 1, 0},
        zFunction,
        "aaabaab"
    );
    TestSomeFunction(
        std::vector<size_t>{7, 0, 1, 0, 3, 0, 1},
        zFunction,
        "abacaba"
    );
    TestSomeFunction(
        std::vector<size_t>{4, 0, 0, 0,},
        zFunction,
        "abcd"
    );
    TestSomeFunction(
        std::vector<size_t>{8, 0, 2, 0, 0, 3, 0, 1},
        zFunction,
        "ababcaba"
    );
    TestSomeFunction(
        std::vector<size_t>{17, 0, 0, 1, 0, 2, 0, 4, 0, 0, 4, 0, 0, 1, 0, 2, 0},
        zFunction,
        "abca$ababcabсacab"
    );
}

void
testZFunctionFind() {
    TestSomeFunction(
        std::vector<size_t>{2,},
        zFunctionPatternMatch,
        "must", "I must not fear."
    );
    TestSomeFunction(
        std::vector<size_t>{12,},
        zFunctionPatternMatch,
        "mind", "Fear is the mind-killer."
    );
    TestSomeFunction(
        std::vector<size_t>{0,},
        zFunctionPatternMatch,
        "Fear", "Fear is the little-death that brings total obliteration."
    );
    TestSomeFunction(
        std::vector<size_t>{15,},
        zFunctionPatternMatch,
        "fear.", "I will face my fear."
    );
    TestSomeFunction(
        std::vector<size_t>{30, 45},
        zFunctionPatternMatch,
        "me", "I will permit it to pass over me and through me."
    );
    TestSomeFunction(
        std::vector<size_t>{},
        zFunctionPatternMatch,
        "When", "And when it has gone past I will turn the inner eye to see its path."
    );
    TestSomeFunction(
        std::vector<size_t>{},
        zFunctionPatternMatch,
        "pain", "Where the fear has gone there will be nothing."
    );
    TestSomeFunction(
        std::vector<size_t>{2, 9, 10},
        zFunctionPatternMatch,
        "l", "Only I will remain."
    );
}

int main() {
    testsZFunction();
    testZFunctionFind();
    return 0;
}
