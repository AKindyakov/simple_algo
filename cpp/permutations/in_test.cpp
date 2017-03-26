#include "permutations.h"

#include <iostream>
#include <vector>

namespace NP = NPermutations;

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5};
    unsigned n = 0;
    do {
        std::cout << " " << n++ << ": [";
        for (const auto& it : arr) {
            std::cout << it << ", ";
        }
        std::cout << "]\n";
    } while (NP::NextInOrder(arr));
    return 0;
}
