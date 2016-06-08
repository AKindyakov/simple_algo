#pragma once

#include "../SimpleAlgoUtil/simple_exception.h"

#include <algorithm>
#include <iostream>


/*
123456
123465
123546
123546
*/
template<typename TIterator>
TIterator
FindMinGreaterThen(
    TIterator begin
    , TIterator end
    , const typename TIterator::value_type& pivot
) {
    TIterator minElement = begin;
    std::cout << "b: " <<  *begin << " P: " << pivot << std::endl;
    while (begin != end) {
        std::cout << "P: " << pivot << " b: " <<  *begin << std::endl;
        if (pivot < *begin && *begin < *minElement) {
            minElement = begin;
        }
        ++begin;
    }
    std::cout << "min: " <<  *minElement << std::endl;
    return minElement;
}

template<typename TCont>
bool
Next(
    TCont& cont
) {
    auto leftReverseIt = cont.rbegin();
    auto rightReverseIt = leftReverseIt;
    //std::cout << "leftReverseIt-> " << *leftReverseIt << std::endl;
    ++leftReverseIt;
    //std::cout << "leftReverseIt-> " << *leftReverseIt << std::endl;
    //std::cout << "leftReverseIt.base()-> " << *(leftReverseIt.base()) << std::endl;
    for (; leftReverseIt != cont.rend(); ++leftReverseIt, ++rightReverseIt) {
        if (*leftReverseIt < *rightReverseIt) {
            auto pMin = FindMinGreaterThen(leftReverseIt.base(), cont.end(), *leftReverseIt);
            if (pMin == cont.end()) {
                throw TSimpleException("It's imposible! Just fail.");
            }
            std::swap(*leftReverseIt, *pMin);
            std::sort(leftReverseIt.base(), cont.end());
            return true;
        }
    }
    return false;
}
