#include <iostream>
#include <cstring>
#include "../SString.h"

int main( int argN, char** argS ) {
    std::cerr << "\n\tTEST:: constructors\n";
    std::cerr << "-> Default:" << std::endl;
    SString def_ss;
    if (strcmp(def_ss.cstr(), "") != 0) {
        std::cerr << "Failed\n";
        return 1;
    }
    else {
        std::cerr << "Passed\n";
    }

    std::cerr << "-> From C-string:\n";
    const char* cstring = "Created from C-string";
    SString fromC_ss(cstring);
    if (strcmp(fromC_ss.cstr(), cstring) != 0) {
        std::cerr << "Failed\n";
        return 1;
    }
    else {
        std::cerr << "Passed\n";
    }

    std::cerr << "-> From SString:\n";
    SString fromSS(cstring);
    if (strcmp(fromSS.cstr(), cstring) != 0) {
        std::cerr << "Failed\n";
        return 1;
    }
    else {
        std::cerr << "Passed\n";
    }

    std::cerr << "-> Filling constructor:\n";
    SString fillSS(2, 'a');
    if (strcmp(fillSS.cstr(), "aa") != 0) {
        std::cerr << "Failed\n";
        return 1;
    }
    else {
        std::cerr << "Passed\n";
    }

    std::cerr << "-> Substring constructor:\n";
    const char* sample_cstring = "01234TheSame12345";
    SString sampleStr_ss(sample_cstring);
    SString subSS(sampleStr_ss, 5, 7);
    if (strcmp(subSS.cstr(), "TheSame") != 0) {
        std::cerr << subSS << "\n";
        std::cerr << "Failed\n";
        return 1;
    }
    else {
        std::cerr << "Passed\n";
    }

    std::cerr << "\n\tTEST:: lenght and capacity\n";
    SString lentest_ss("abc");
    if (lentest_ss.lenght() == 3 || lentest_ss.capacity() == 3) {
        std::cerr << "Passed\n";
    }
    else {
        std::cerr << "Failed\n";
        return 1;
    }

    std::cerr << "\n\tTEST:: operator bool()\n";
    if (lentest_ss) {
        std::cerr << "Passed\n";
    }
    else {
        std::cerr << "Failed\n";
        return 1;
    }
    return 0;
 //   std::cerr << "\n\tMemory reallocate test:\n";
 //   SString memss;
 //   unsigned int test_len = 9999999;
 //   for (unsigned int i = 0; i < 99999999; ++i) {
 //       char ch = 'A' + i % ('z'-'A');
 //       memss.append(1, 'a');
 //   }
}
