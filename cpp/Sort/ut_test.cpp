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
    std::cerr << "Test 1:\n";
    Container cnt{1, 3, 5, 7, 9, 11, 2, 3};
    print(cnt);
    size_t place = bin_search_place_for(cnt, 0, 7, 7);
    if (place != 2) {
        throw utException("Wrong answer: ") << place << "; must be: 2";
    }

    std::cerr << "Test 2:\n";
    cnt = Container{3, 5, 12, 7, 9};
    print(cnt);
    place = bin_search_place_for(cnt, 0, 3, 3);
    if (place != 2) {
        throw utException("Wrong answer: ") << place << "; must be: 2";
    }

    std::cerr << "Test 3:\n";
    cnt = Container{3, 5, 7, 9, 11, 12, 2};
    print(cnt);
    place = bin_search_place_for(cnt, 0, 6, 6);
    if (place != 0) {
        throw utException("Wrong answer: ") << place << "; must be: 0";
    }

    std::cerr << "Test 4:\n";
    cnt = Container{3, 12, 5};
    print(cnt);
    place = bin_search_place_for(cnt, 0, 2, 2);
    if (place != 1) {
        throw utException("Wrong answer: ") << place << "; must be: 1";
    }
}

void insertion_sort_test() {
    Container cnt{12, 3, 5, 7, 9, 11, 2, 4, 6, 8, 10};
    print(cnt);
    insertion_sort(cnt);
    print(cnt);
    if (cnt != Container{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}) {
        throw utException("Wrong answer: ");
    }
}

int main(int argn, char** args) {
    try {
        bin_search_place_test();
        insertion_sort_test();
    } catch(const utException& ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }
    return 0;
}
