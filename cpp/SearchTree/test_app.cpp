#include "simple_search_tree.h"
// #include "read_black_tree.h"

#include <exception>
#include <iostream>
#include <memory>

int main(int /*argn*/, char** /*args*/) {
    TSsTree tree;
    std::string line;
    for (std::string line; std::getline(std::cin, line); ) {
        tree.insert(line);
    }
    tree.print(std::cerr);
    tree.inOrderPrint(std::cerr);

    tree.remove("1");

    std::cout << "-------\n";
    tree.print(std::cerr);
    tree.inOrderPrint(std::cerr);

    return 0;
}

