#pragma once

#include <string>
#include <vector>
#include <iostream>

std::vector<size_t>
zFunction(
    const std::string& str
);

std::vector<size_t>
zFunctionPatternMatch(
    const std::string& pattern
    , const std::string& where
);

