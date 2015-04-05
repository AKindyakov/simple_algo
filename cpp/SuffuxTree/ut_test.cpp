#include "tree.h"

#include "../SimpleAlgoUtil/simple_exception.h"
#include "../SimpleAlgoUtil/unit_test.h"

#include <exception>
#include <iostream>
#include <vector>

int main(int /*argn*/, const char** /*args*/) {
    try {
        std::string str = "mississippiz";
        std::cerr << "start\n";
        TSuffixTree stree(str);
        std::cerr << "show\n";
        stree.show(std::cout);
    }
    catch(const TSimpleException& e) {
        std::cerr
            << "TSimpleException error "
            << e.what() << '\n';
    }
    catch(const std::exception& e) {
        std::cerr
            << "Std error "
            << e.what() << '\n';
    }
    catch(...) {
        std::cerr << "Unexpected error";
    }
    return 0;
}
