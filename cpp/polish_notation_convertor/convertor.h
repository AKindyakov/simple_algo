#pragma once

#include <string>
#include <sstream>

namespace PolishNotation {

constexpr char Delimiter = ' ';

std::string NormalToReverse(const std::string& inStr);

void NormalToReverse(
    std::ostream& to
    , std::istream& from
);

}  // namespace PolishNotation
