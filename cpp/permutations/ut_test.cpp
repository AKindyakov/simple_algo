#include "permutations.h"

#include "../simple_algo_util/simple_exception.h"
#include "../simple_algo_util/unit_test.h"

#include <vector>

namespace NP = NPermutations;

void NextInOrder() {
    auto arr = std::vector<int>{0, 1, 2, 3};
    auto rightAnswer = std::vector<int>{0, 1, 3, 2};
    if (!NP::NextInOrder(arr)) {
        throw TSimpleException("[NextInOrder]")
            << " Is not last permutation";
    }
    if (rightAnswer != arr) {
        throw TSimpleException("[NextInOrder]")
            << " Wrong answer: " << arr
            << " Expected: " << rightAnswer;
    }

    rightAnswer = std::vector<int>{0, 2, 1, 3};
    if (!NP::NextInOrder(arr)) {
        throw TSimpleException("[NextInOrder]")
            << " Is not last permutation";
    }
    if (rightAnswer != arr) {
        throw TSimpleException("[NextInOrder]")
            << " Wrong answer: " << arr
            << " Expected: " << rightAnswer;
    }

    rightAnswer = std::vector<int>{0, 2, 3, 1};
    if (!NP::NextInOrder(arr)) {
        throw TSimpleException("[NextInOrder]")
            << " Is not last permutation";
    }
    if (rightAnswer != arr) {
        throw TSimpleException("[NextInOrder]")
            << " Wrong answer: " << arr
            << " Expected: " << rightAnswer;
    }

    rightAnswer = std::vector<int>{0, 3, 1, 2};
    if (!NP::NextInOrder(arr)) {
        throw TSimpleException("[NextInOrder]")
            << " Is not last permutation";
    }
    if (rightAnswer != arr) {
        throw TSimpleException("[NextInOrder]")
            << " Wrong answer: " << arr
            << " Expected: " << rightAnswer;
    }

    arr = std::vector<int>{3, 2, 1, 0};
    if (NP::NextInOrder(arr)) {
        throw TSimpleException("[NextInOrder]")
            << "Permutation have to be last";
    }
}

void FindMinGreaterThen() {
    auto arr = std::vector<int>{
    //  0   1   2   3   4   5   6   7   8   9  10  11
        6, 20, 64, 61, 21, 63, 66, 69, 67, 75, 72,  5,
    };
    int pivot = 6;
    int rightAnswer = 20;
    int answer = *NP::FindMinGreaterThen(arr.begin(), arr.begin() + 4, pivot);
    if (answer != rightAnswer) {
        throw TSimpleException("[FindMinGreaterThen]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer
        ;
    }
    pivot = 62;
    rightAnswer = 63;
    answer = *NP::FindMinGreaterThen(arr.begin(), arr.begin() + 6, pivot);
    if (answer != rightAnswer) {
        throw TSimpleException("[FindMinGreaterThen]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer
        ;
    }
    pivot = 67;
    rightAnswer = 69;
    answer = *NP::FindMinGreaterThen(arr.begin(), arr.end(), pivot);
    if (answer != rightAnswer) {
        throw TSimpleException("[FindMinGreaterThen]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer
        ;
    }
}

int main() {
    FindMinGreaterThen();
    NextInOrder();
    return 0;
}

