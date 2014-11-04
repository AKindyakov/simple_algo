#include "heap.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

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

void constructor_min_heap() {
    std::vector<int> cnt{9, 8, 12, 23, 5, 0, 0, 0, -1, -1, -9};
    std::vector<int> out(cnt);
    std::sort(out.begin(), out.end(), std::less<int>());
    Heap<int, std::less<int>, 1, std::vector<int>> testHeap(
        std::less<int>(),
        std::move(cnt)
    );

    for (std::size_t i = 0; i < cnt.size(); ++i) {
        int test  = testHeap.top();
        int right = out[i];
        if (test != right) {
            throw utException("[constructor min heap test]")
                << " Wrong answer: " << test
                << " Expected: " << right;
        }
        testHeap.pop();
    }
}

void constructor_max_heap() {
    std::vector<int> cnt{9, 8, 12, 23, 5, 0, 0, -10, -1, -1, -9};
    std::vector<int> out(cnt);
    std::sort(out.begin(), out.end(), std::greater<int>());
    Heap<int, std::greater<int>, 1, std::vector<int>> testHeap(
        std::greater<int>(),
        std::move(cnt)
    );

    for (std::size_t i = 0; i < cnt.size(); ++i) {
        int test  = testHeap.top();
        int right = out[i];
        if (test != right) {
            throw utException("[constructor max heap test]")
                << " Wrong answer: " << test
                << " Expected: " << right;
        }
        testHeap.pop();
    }
}

void order_4_heap() {
    std::vector<int> cnt{2320, 5468, 6973, 2060, 6960, 6520, 6160, 6060, 7773, 2070, 7260, 6365, 7373, 6573, 2060, 6020};
    std::vector<int> out(cnt);
    std::sort(out.begin(), out.end(), std::less<int>());
    Heap<int, std::less<int>, 2, std::vector<int>> testHeap(
        std::less<int>(),
        std::move(cnt)
    );

    for (std::size_t i = 0; i < cnt.size(); ++i) {
        int test  = testHeap.top();
        int right = out[i];
        if (test != right) {
            throw utException("[constructor min heap with order 4 test]")
                << " Wrong answer: " << test
                << " Expected: " << right;
        }
        testHeap.pop();
    }
}

int main(int argn, char** args) {
    try {
        constructor_min_heap();
        constructor_max_heap();
        order_4_heap();
    } catch(const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }
    return 0;
}
