#pragma once

namespace NPermutations {
/*
* Next permutation in sequence
* For instance:
* 1234 -> 1243
* 1243 -> 1324
* 4321 -> false
* return false if cont is the last one
*/
template<typename TCont>
bool NextInOrder(TCont& cont);

/*
* Find minimal element from range [begin, end)
* greater then pivot
*/
template<typename TCont>
typename TCont::iterator
FindMinGreaterThen(
    typename TCont::iterator begin
    , typename TCont::iterator end
    , const typename TCont::value_type& pivot
);

}

#include "permutations_impl.h"
