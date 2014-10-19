#include "merge_sort.h"
#include "insertion_sort.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

class utException: public std::exception {
public:
    utException() {}
    utException(const std::string& what)
        : whatHappen(what) {
    }

    template<typename T>
    utException& operator<<(const T& val) {
        std::ostringstream ostr;
        ostr << val;
        whatHappen.append(ostr.str());
        return *this;
    }

    const char* what() const throw() override { return whatHappen.c_str(); }
private:
    std::string whatHappen;
};

void merge_sequences_test() {
    Container cnt{1, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    Container buf(cnt.size());
    merge_range(cnt, buf, 0, 6, 6, cnt.size());
    if (cnt != Container{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}) {
        throw utException("[merge 2 sequences test]") << "Wrong answer: ";
    }
}

void pure_merge_sort_test() {
    Container cnt{12, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    pure_merge_sort(cnt);
    if (cnt != Container{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}) {
        throw utException("[pure merge sort test]") << "Wrong answer: ";
    }
}

void bin_search_place_test() {
    Container cnt{1, 3, 5, 7, 9, 11, 2, 3};
    size_t place = bin_search_place_for(cnt, 0, 7, 7);
    if (place != 2) {
        throw utException("[bin search test]") << "Wrong answer: " << place << "; must be: 2";
    }

    cnt = Container{3, 5, 12, 7, 9};
    place = bin_search_place_for(cnt, 0, 3, 3);
    if (place != 2) {
        throw utException("[bin search test]") << "Wrong answer: " << place << "; must be: 2";
    }

    cnt = Container{3, 5, 7, 9, 11, 12, 2};
    place = bin_search_place_for(cnt, 0, 6, 6);
    if (place != 0) {
        throw utException("[bin search test]") << "Wrong answer: " << place << "; must be: 0";
    }

    cnt = Container{3, 12, 5};
    place = bin_search_place_for(cnt, 0, 2, 2);
    if (place != 1) {
        throw utException("[bin search test]") << "Wrong answer: " << place << "; must be: 1";
    }
}

void insertion_sort_test() {
    Container cnt{12, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    insertion_sort(cnt);
    if (cnt != Container{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}) {
        throw utException("[insertion sort test]") << "Wrong answer: ";
    }
}

void merge_sort_test() {
    Container cnt{12, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    merge_sort(cnt);
    if (cnt != Container{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}) {
        throw utException("[merge sort test]") << "Wrong answer: ";
    }
}

int main(int argn, char** args) {
    try {
        merge_sequences_test();
        pure_merge_sort_test();
        bin_search_place_test();
        insertion_sort_test();
        merge_sort_test();
    } catch(const utException& ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }
    return 0;
}
