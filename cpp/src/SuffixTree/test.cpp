#include <iostream>
#include <exception>
#include "tree.h"

int main( int argN, char** argS ) {
    try {
        int samples = 0;
        std::cin >> samples;
        std::cin.ignore();
        if( samples < 1 ) {
            throw 1;
        }
        
        SuffTree tree;
        char ch = std::cin.get();
        while( ch != '\n' ) {
            std::cout << ch << '\n';
            tree.add(ch);
            ch = std::cin.get();
        }
        /**/ tree.showMe(std::cout);
        tree.endString();
        tree.finishTree();
        
        while( --samples ) {
            ch = std::cin.get();
            while( ch != '\n' ) {
                tree.check(ch);
                ch = std::cin.get();
            }
            tree.endString();
            /**/ tree.showMe(std::cout);
            /**/ std::cout << "Great: [" << tree.getGreatSubstring() << "]\n";
        }
        //**/ tree.showMe(std::cout);
        std::cout << tree.getGreatSubstring() << '\n';
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
