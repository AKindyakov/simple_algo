#include "../SimpleAlgoUtil/unit_test.h"

#include "fenwick.h"
namespace NFT = NFenwickTree;

int EmptyFunction(int a, int b) {
    return a + b + 1;
}

void SumTest() {
    auto tree = NFT::Create(
        std::vector<int>{1, 2, 3, 4}
        , NFT::Add<int>
        , NFT::Sub<int>
    );
}

int main() {
    TestSomeFunction(
        6,
        EmptyFunction,
        2, 3
    );
    return 0;
}

