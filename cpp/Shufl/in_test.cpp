#include "next.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5};
    unsigned n = 0;
    do {
        std::cout << " " << n++ << ": [";
        for (const auto& it : arr) {
            std::cout << it << ", ";
        }
        std::cout << "]\n";
    } while (Next(arr));
    return 0;
}
