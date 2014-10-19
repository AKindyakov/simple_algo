#include <iostream>
#include <ctime>
#include <cstdlib>
#include "quicksort.h"

int main( int argN, char** argS ) {
    int sz = 10;
    int* arr = NULL;
    if( argN == 2 ) {
        sz = atoi(argS[1]);
    }
    else {
        if( argN > 2 ) {
            sz = argN-1;
            if( arr == NULL ) {
                arr = new int[sz];
            }
            for( int i = 0; i < sz; ++i ) {
                arr[i] = atoi(argS[i+1]);
            }
        }
    }

    if( arr == NULL ) {
        arr = new int[sz];
        for( int i = 0; i < sz; ++i ) {
            srand( static_cast<int>( clock() ) );
            std::cout << static_cast<int>( clock() ) << '\n';
            arr[i] = rand();
        }
    }
    std::cout << "Before:\n";
    for( int i = 0; i < sz; ++i ) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;

    quicksort(arr, 0, sz-1);

    std::cout << "After:\n";
    for( int i = 0; i < sz; ++i ) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

