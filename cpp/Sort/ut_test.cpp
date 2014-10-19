#include "merge_sort.h"
#include "insertion_sort.h"

#include <iostream>

void print(const Container& cnt) {
    std::cout << "{ ";
    for (auto & num : cnt) {
        std::cout << num << ", ";
    }
    std::cout << "}\n";
}

void merge_test() {
    Container cnt{1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    Container buf(cnt.size());
    print(cnt);
    merge_range(cnt, buf, 0, 6, 6, cnt.size());
    print(cnt);
}

void pure_merge_sort_test() {
    Container cnt{12, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    print(cnt);
    pure_merge_sort(cnt);
    print(cnt);
}

void bin_search_place_test() {
    Container cnt{1, 3, 5, 7, 9, 11, 2, 3};
    print(cnt);
    size_t place = bin_search_place_for(cnt, 0, 7, 7);
    if (
    std::cout << "place for 2: " << place << "\n";

    cnt = Container{3, 5, 12, 7, 9};
    print(cnt);
    place = bin_search_place_for(cnt, 0, 3, 3);
    std::cout << "place for 2: " << place << '\n';

    cnt = Container{3, 5, 7, 9, 11, 12, 2};
    print(cnt);
    place = bin_search_place_for(cnt, 0, 6, 6);
    std::cout << "place for 2: " << place << '\n';
}

void insertion_sort_test() {
    Container cnt{12, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    print(cnt);
    insertion_sort(cnt);
    print(cnt);
}

int main(int argn, char** args) {
    //insertion_sort_test();
    bin_search_place_test();
    return 0;
}
