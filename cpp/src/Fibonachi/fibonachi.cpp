#include <iostream>
#include <vector>
#include <cstdlib>


int simpleFibonachi(int N) {
    std::vector<int> mem(N);
    mem[0] = 1;
    mem[1] = 1;
    //std::cout << "F: 1 1 ";
    for ( int i=2; i<N; ++i) {
        mem[i] = mem[i-1] + mem[i-2];
    //    std::cout << mem[i] << ' ';
    }
    //std::cout << '\n';
    return mem[N-1];
}

int recurseFibonachi(int N) {
    if( N <  1 ) { 
        return 0;
    }
    if( N == 1 ) {
        return 1;
    }
    return recurseFibonachi(N-1) + recurseFibonachi(N-2);
}

int main( int argn, char** args ) {
    for( int arg = 1; arg < argn; ++arg ) {
        int n = atoi(args[arg]);
        std::cout << "F-> n=" << args[arg];
        std::cout << "  \tSimple:  " << simpleFibonachi(n);
        std::cout << "  \tRecurse: " << recurseFibonachi(n);
    }
    std::cout << '\n';
    return 0;
}
