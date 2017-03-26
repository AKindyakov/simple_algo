#pragma once

#include "sort_error.h"

#include <limits>
#include <vector>

using Container = std::vector<int>;

std::size_t
get_place_for(
    const Container& cnt,
    std::size_t start,
    std::size_t end,
    std::size_t inserted
);

std::size_t
bin_search_place_for(
    const Container& cnt,
    std::size_t start,
    std::size_t end,
    std::size_t inserted
);

void
insertion_sort(
    Container& cnt,
    std::size_t start = 0,
    std::size_t end = std::numeric_limits<unsigned>::max()
);

template<
    typename TIterator,
    typename TComparator
>
TIterator
search_place_for(
    TIterator start,
    TIterator end,
    TIterator inserted,
    TComparator comparator
) {
    for (TIterator i = start; i != end; ++i) {
        if (comparator(*inserted, *i)) {
            return i;
        }
    }
    return end;
}

/**
 * before:
 *     |+++++T******F----|
 *           ^      ^
 *           |      |
 *           to     from
 * after:
 *     |+++++FT******----|
 *           ^^
 *          /  \
 *       from   to
 */
template<
    typename TIterator
>
void
rotate_left(
    TIterator to,  // left
    TIterator from // right
) {
    TIterator j = from;
    TIterator i = from;
    while (i != to) {
        j--;
        std::swap(*i, *j);
        i--;
    }
}

template<
    typename TIterator,
    typename TComparator
>
void
insertion_sort(
    TIterator start,
    TIterator end,
    TComparator comparator
) {
    for (TIterator scan = start; scan != end; ++scan) {
        TIterator place = search_place_for(start, scan, scan, comparator);
        rotate_left(place, scan);
    }
}
