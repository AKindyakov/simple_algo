#include "expansion.h"

#include "../simple_algo_util/unit_test.h"


void Test0() {
    auto rightAnswer = std::vector<std::string>{
        "abc1",
        "abc2",
        "abc3",
    };
    auto answ = BraceExpansion("abc{1..3}");
    if (rightAnswer != answ) {
        throw TSimpleException()
            << "Wrong answer: " << answ
            << ", expected: " << rightAnswer;
    }
}

void Test1() {
    auto rightAnswer = std::vector<std::string>{
        "0abc1",
        "0abc2",
        "1abc1",
        "1abc2",
    };
    auto answ = BraceExpansion("{0..1}abc{1..2}");
    if (rightAnswer != answ) {
        throw TSimpleException()
            << "Wrong answer: " << answ
            << ", expected: " << rightAnswer;
    }
}

void Test2() {
    auto rightAnswer = std::vector<std::string>{
        "a-1abc1c",
        "a-1abc2c",
        "a0abc1c",
        "a0abc2c",
        "a1abc1c",
        "a1abc2c",
    };
    auto answ = BraceExpansion("a{-1..1}abc{1..2}c");
    if (rightAnswer != answ) {
        throw TSimpleException()
            << "Wrong answer: " << answ
            << ", expected: " << rightAnswer;
    }
}

void Test3() {
    auto rightAnswer = std::vector<std::string>{
        "-2abc",
        "-1abc",
        "0abc",
    };
    auto answ = BraceExpansion("{-2..0}abc");
    if (rightAnswer != answ) {
        throw TSimpleException()
            << "Wrong answer: " << answ
            << ", expected: " << rightAnswer;
    }
}

void Test4() {
    auto answ = BraceExpansion("{0..999}abcdef");
    if (1000 != answ.size()) {
        throw TSimpleException()
            << "Wrong answer: " << answ.size()
            << ", expected: " << 1000;
    }
}

void Test5() {
    auto answ = BraceExpansion("{0..999}abcdef{0..99}");
    if (100000 != answ.size()) {
        throw TSimpleException()
            << "Wrong answer: " << answ.size()
            << ", expected: " << 100000;
    }
}
void Test6() {
    auto answ = BraceExpansion("");
    if (answ.size() != 1 || !answ[0].empty()) {
        throw TSimpleException()
            << "Wrong answer: " << answ
            << ", expected: \"\"";
    }
}

int main() {
    Test0();
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    return 0;
}

