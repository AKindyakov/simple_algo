#include "insertion_sort.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main( int argN, char** argS ) {
    int sz = 10;
    std::vector<int> arr;
    if( argN == 2 ) {
        sz = atoi(argS[1]);
        for (size_t i = 0; i < sz; ++i) {
            srand(static_cast<int>(clock()));
            arr.push_back(rand());
        }
    }
    else {
        if (argN > 2) {
            sz = argN-1;
            for (size_t i = 0; i < sz; ++i) {
                arr.push_back(atoi(argS[i+1]));
            }
        }
    }

    std::cout << "Before:\n";
    for( const auto& a : arr) {
        std::cout << a << ' ';
    }
    std::cout << std::endl;

    insertion_sort(arr, 0, sz);

    std::cout << "After:\n";
    for( const auto& a : arr) {
        std::cout << a << ' ';
    }
    std::cout << std::endl;
}

