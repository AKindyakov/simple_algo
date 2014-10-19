#pragma once

#include <limits>
#include <vector>

using Container = std::vector<int>;

void
merge_range(
    Container& cnt,
    Container& buf,
    std::size_t firstStart,
    std::size_t firstEnd,
    std::size_t secondStart,
    std::size_t secondEnd
);

void
pure_merge_sort(
    Container& cnt,
    std::size_t start = 0,
    std::size_t end = std::numeric_limits<unsigned>::max()
);

void
merge_sort(
    Container& cnt,
    std::size_t start = 0,
    std::size_t end = std::numeric_limits<unsigned>::max()
);
