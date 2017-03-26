#pragma once

#include "../simple_algo_util/simple_exception.h"

#include <algorithm>
#include <iostream>

namespace NPermutations {

template<typename TIterator>
TIterator
FindMinGreaterThen(
    TIterator begin
    , TIterator end
    , const typename TIterator::value_type& pivot
) {
    TIterator minElement = end;
    while (begin != end) {
        if (pivot < *begin
            && (minElement == end || *begin < *minElement)
        ) {
            minElement = begin;
        }
        ++begin;
    }
    return minElement;
}

template<typename TCont>
bool
NextInOrder(
    TCont& cont
) {
    auto leftReverseIt = cont.rbegin();
    auto rightReverseIt = leftReverseIt;
    ++leftReverseIt;
    for (; leftReverseIt != cont.rend(); ++leftReverseIt, ++rightReverseIt) {
        if (*leftReverseIt < *rightReverseIt) {
            auto pMin = FindMinGreaterThen(
                leftReverseIt.base(),
                cont.end(),
                *leftReverseIt
            );
            if (pMin == cont.end()) {
                throw TSimpleException("It's imposible! Just fail.");
            }
            std::swap(*leftReverseIt, *pMin);
            std::reverse(leftReverseIt.base(), cont.end());
            return true;
        }
    }
    return false;
}

}
