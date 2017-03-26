#include "convertor.h"

#include "../simple_algo_util/simple_exception.h"

#include <exception>
#include <iostream>

#define M_ASSERT_EQUAL(FIRST, SECOND) { \
    auto f = FIRST; \
    auto s = SECOND; \
    if (! (s == f)) { \
        throw TSimpleException("Assert: ") \
            << '"' << f << "\" == \"" << s << '"' \
        ; \
    } \
} \


int main() {
    M_ASSERT_EQUAL(
        PolishNotation::NormalToReverse("* + 1 2 3"), "1 2 + 3 *"
    );
    M_ASSERT_EQUAL(
        PolishNotation::NormalToReverse("* / 15 - 7 + 1 1 3"), "15 7 1 1 + - / 3 *"
    );
}
