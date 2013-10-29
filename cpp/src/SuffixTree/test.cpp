#include <iostream>
#include <exception>
#include "tree.h"

#include "../SimpleAlgoException/simpleException.h"

int main( int argN, char** argS ) {
    try {
        int samples = 0;
        std::cin >> samples;
        std::cin.ignore();
        if( samples < 1 ) {
            throw SimpleException("Unexpected algo list", __LINE__);
        }
        
        SuffTree tree;
        char ch = std::cin.get();
        while( ch != '\n' ) {
            tree.add(ch);
            ch = std::cin.get();
        }
        std::cout << "build compleete\n";
        //**/ tree.showMe(std::cout);
        tree.endString();
        tree.finishTree();
        
        while( --samples ) {
            ch = std::cin.get();
            while( ch != '\n' ) {
                tree.check(ch);
                ch = std::cin.get();
            }
            tree.endString();
            std::cout << "check : " << samples << "\n";
            //**/ tree.showMe(std::cout);
            //**/ std::cout << "Great: [" << tree.getGreatSubstring() << "]\n";
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
