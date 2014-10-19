#pragma once

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
    std::size_t end = 10000
);
