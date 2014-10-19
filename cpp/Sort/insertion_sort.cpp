#include "insertion_sort.h"

#include <iostream>

std::size_t get_place_for(
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
    auto delta = (end - start)/2;
    auto ind = (end - start)/2;
    while (delta > 0 && !!ind) {
        delta = delta > 1 ? delta>>1 : 1;
        if (cnt[start + ind] < cnt[inserted]) {
            ind += delta;
        } else if (cnt[inserted] < cnt[start + ind]) {
            if (ind < 1 || !(cnt[inserted] < cnt[start + ind - 1])) {
                delta = 0; // out
            }
            ind -= delta;
        } else {
            delta = 0; // out
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
    //std::cerr << "  rotate from: " << from << ", to: " << to << '\n';
    for (std::size_t ind = from; ind > to; --ind) {
        std::swap(cnt[ind - 1], cnt[ind]);
        //std::cerr << "  swap: " << ind - 1 << ", " << ind << '\n';
    }
}

static void print(const Container& cnt) {
    std::cerr << "{ ";
    for (auto & num : cnt) {
        std::cerr << num << ", ";
    }
    std::cerr << "}\n";
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
        std::size_t place = bin_search_place_for(cnt, 0, scan, scan);
        std::cerr << "  scan: " << scan << ";    place: " << place << '\n';
        rotate_left(cnt, place, scan);
        print(cnt);
    }
}
