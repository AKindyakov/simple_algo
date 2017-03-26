#include "convertor.h"

#include <iostream>

namespace PolishNotation {

// const char Delimiter;

std::string ReadToken(
    std::istream& from
) {
    auto token = std::string{};
    auto ch = from.get();
    while (!from.eof() && ch != Delimiter) {
        token.push_back(ch);
        ch = from.get();
    }
    return token;
}

bool IsOperator(const std::string& str) {
    switch (str[0]) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
            break;
        default:
            return false;
            break;
    }
    return false;
}

std::string NormalToReverse(
    const std::string& inStr
) {
    auto to = std::ostringstream{};
    auto from = std::istringstream{inStr};
    NormalToReverse(to, from);
    return to.str();
}

bool NormalToReverseRec(
    std::ostream& to
    , std::istream& from
    , bool isFirst
) {
    auto token = ReadToken(from);
    if (token.empty()) {
        return false;
    }
    if (IsOperator(token)) {
        NormalToReverseRec(to, from, false);
        NormalToReverseRec(to, from, false);
    }
    to << token;
    if (!isFirst) {
        to << Delimiter;
    }
    return true;
}

void NormalToReverse(
    std::ostream& to
    , std::istream& from
) {
    NormalToReverseRec(to, from, true);
}


}  // namespace PolishNotation
