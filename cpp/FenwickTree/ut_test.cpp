#include "fenwick.h"

#include "../SimpleAlgoUtil/simple_exception.h"
#include "../SimpleAlgoUtil/unit_test.h"

#include <iostream>

namespace NFT = NFenwickTree;

int EmptyFunction(int a, int b) {
    return a + b + 1;
}

void SumTest() {
    NFT::TFenwickTree<int, NFT::TAdd<int>, NFT::TSub<int>> tree(
        //               0  1  2  3  4  5
        std::vector<int>{2, 5, 1, 4, 0, -1}
    );
    int answer = tree.Get(1, 3);
    int rightAnswer = 6;
    if (rightAnswer != answer) {
        throw TSimpleException("[Within range sum]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
    answer = tree.Get(0, 0);
    rightAnswer = 0;
    if (rightAnswer != answer) {
        throw TSimpleException("[Left verge sum]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
    answer = tree.Get(5, 6);
    rightAnswer = -1;
    if (rightAnswer != answer) {
        throw TSimpleException("[Right verge sum]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
    answer = tree.Get(0, 6);
    rightAnswer = 11;
    if (rightAnswer != answer) {
        throw TSimpleException("[Full range sum]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
}

void SwapTest() {
    NFT::TFenwickTree<int, NFT::TAdd<int>, NFT::TSub<int>> tree(
        //               0  1  2
        std::vector<int>{2, 5, 1}
    );
    tree.Swap(1, 3);
    int answer = tree.Get(1, 3);
    int rightAnswer = 4;
    if (rightAnswer != answer) {
        throw TSimpleException("[Swap value]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
}

void PushPopTest() {
    NFT::TFenwickTree<int, NFT::TAdd<int>, NFT::TSub<int>> tree(
        //               0  1
        std::vector<int>{2, 5}
    );
    tree.Push(4);
    int answer = tree.Get(1, 3);
    int rightAnswer = 9;
    if (rightAnswer != answer) {
        throw TSimpleException("[Push]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
    tree.Pop();
    answer = tree.Get(1, 3);
    rightAnswer = 5;
    if (rightAnswer != answer) {
        throw TSimpleException("[Pop]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
}

int main() {
    SumTest();
    SwapTest();
    PushPopTest();
    return 0;
}

