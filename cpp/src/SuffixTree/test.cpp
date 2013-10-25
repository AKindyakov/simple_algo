#include <iostream>
#include <exception>
#include "tree.h"

int main( int argN, char** argS ) {
    try {
        SuffTree tree;
        char ch = std::cin.get();
        while( ch != '\n' ) {
            tree.add(ch);
            ch = std::cin.get();
        }
        tree.endString();
        tree.showMe(std::cout);
    }
    catch(const std::exception& e) {
        std::cerr << "Std error "
                  << e.what() << '\n';
    }
    catch(...) {
        std::cerr << "Samething wrong\n";
    }
   
    return 0;
}
