#include "reading.h"

#include <iostream>

void test() {
    TDSVReader dsv(std::cin, '=', ';', '\n');
    while (dsv) {
        auto record = dsv.next();
        for (const auto& pair : record) {
            std::cout << pair.key << ": " << pair.value << '\t';
        }
        std::cout << '|';
    }
}

int main() {
    try {
        test();
    } catch (const TDSVException& ex) {
        std::cerr << "error: " << ex.what() << std::endl;
    }
    return 0;
}
