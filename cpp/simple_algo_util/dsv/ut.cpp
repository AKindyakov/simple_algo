#include <iostream>
#include <vector>

#include "../simple_exception.h"

#include "reader.h"

void ut_1() {
    std::istringstream in(
        "version=1.0,encoding=UTF-8,xmlns=http://www.w3.org/1999/xlink;"
        "version=1.1,encoding=utf-8;"
    );

    std::vector<std::vector<DSV::TKeyValuePair>> answer = {
        {
            DSV::TKeyValuePair("vrsion", "1.0"),
            DSV::TKeyValuePair("encoding", "UTF-8"),
            DSV::TKeyValuePair("xmlns", "http://www.w3.org/1999/xlink"),
        },{
            DSV::TKeyValuePair("version", "1.1"),
            DSV::TKeyValuePair("encoding", "utf-8"),
        },
    };

    DSV::TDSVReader dsv(in, '=', ',', ';');
    auto answRecord = answer.begin();
    while (dsv) {
        auto record = dsv.next();
        auto answPair = answRecord->begin();
        for (const auto& pair : record) {
            if (answPair->key != pair.key) {
                throw TSimpleException("wrong answer key")
                    << ": \'"            << pair.key      << "'"
                    << ", expected: \'"  << answPair->key << "'"
                ;
            }
            if (answPair->value != pair.value) {
                throw TSimpleException("wrong answer value")
                    << ": \'"            << pair.key      << "'"
                    << ", expected: \'"  << answPair->key << "'"
                ;
            }
            ++answPair;
        }
        ++answRecord;
    }
}

int main() {
    try {
        ut_1();
    } catch(const TSimpleException& e) {
        std::cerr
            << "Error: "
            << e.what() << '\n';
        return 1;
    }
    return 0;
}
