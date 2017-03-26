#include "insertion_sort.h"

std::size_t
get_place_for(
    const Container& cnt,
    std::size_t start,
    std::size_t end,
    std::size_t inserted
) {
    for (auto i = start; i < end; ++i) {
        if (cnt[i] < cnt[inserted]) {
            return i;
        }
    }
    return end;
}

std::size_t
bin_search_place_for(
    const Container& cnt,
    std::size_t start,
    std::size_t end,
    std::size_t inserted
) {

    std::size_t ind = 0;
    while (1) {
        ind = start + (end - start)/2;
        if (end <= start) {
            break;
        } else if (cnt[ind] < cnt[inserted]) {
            start = ind + 1;
        } else if (cnt[inserted] < cnt[ind]) {
            end = ind;
        } else {
            ++ind;
            break;
        }
    }
    return ind;
}

void
rotate_left(
    Container& cnt,
    std::size_t to,
    std::size_t from
) {
    for (std::size_t ind = from; ind > to; --ind) {
        std::swap(cnt[ind - 1], cnt[ind]);
    }
}

void
insertion_sort(
    Container& cnt,
    std::size_t start,
    std::size_t end
) {
    if (end > cnt.size()) {
        end = cnt.size();
    }
    for (std::size_t scan = start; scan < end; ++scan) {
        auto place = bin_search_place_for(cnt, start, scan, scan);
        rotate_left(cnt, place, scan);
    }
}
