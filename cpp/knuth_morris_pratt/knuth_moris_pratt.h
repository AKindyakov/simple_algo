#pragma once

#include <vector>
#include <string>

std::vector<size_t>
ComputeStringPrefixFunction(
    const std::string& str
);

std::vector<size_t>
KnuthMorrisPrattFind(
    const std::string& pattern
    , const std::string& where
);

