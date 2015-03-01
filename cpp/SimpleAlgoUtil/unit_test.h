#pragma once

#include "simple_exception.h"

template<
    typename AnswerType
    , typename TestedFunc
    , typename... Args
    >
void
TestSomeFunction(
    AnswerType rightAnswer
    , TestedFunc func
    , Args&... args
) {
    auto answer = func(args...);
    if (rightAnswer != answer) {
        throw TSimpleException("[testSmth]")
            << " function" << TSimpleException::argsToString(args...)
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
}

