#include "quicksort.h"

template<typename T>
void exch(T* a, T* b) {
    T t(*a);
    *a = *b;
    *b = t;
}

int partition(int* arr, int first, int second) {
    int i = first-1;
    int j = second;
    int v = arr[second];
    while(1) {
        while(i < second && arr[++i] <= v);
        while(arr[--j] >= v) {
            if( j == i || j == first ) {
                break;
            }
        }
        if( j <= i ) {
            break;
        }
    }
    exch(arr+second, arr+i);
    return i;
}

void quicksort( int* arr, int first, int second ) {
    if( first >= second ) {
        return;
    }
    int c = partition(arr, first, second);
    quicksort( arr, first, c-1 );
    quicksort( arr, c+1, second );
}

