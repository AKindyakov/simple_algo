#include <iostream>
#include "../heap.h"

int main( int argN, char** argS ) {
    HeapTree heap(10);
    int t = 10;
    while(--t) {
        heap.add(t);
    }
    return 0;
}
