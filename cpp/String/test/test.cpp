#include <iostream>
#include "../SString.h"

int main( int argN, char** argS ) {
    std::cout << "s1 creating:" << std::endl;
    SString s1;

    std::cout << "s2 creating:" << std::endl;
    SString s2( "const char* cstr" );

    std::cout << "s3 creating:" << std::endl;
    SString s3( 256, '?' );

    std::cout << "s4 creating:" << std::endl;
    SString s4( s2 );

    std::cout << "s5 creating:" << std::endl;
    SString s5( s3, 1, 7 );

    std::cout << "Default constructor:      |" << s1.cstr() << "|\n";
    std::cout << "Copy cstring constructor: |" << s2.cstr() << "|\n";
    std::cout << "Copy constructor:         |" << s4.cstr() << "|\n";
    std::cout << "Substring constructor:    |" << s5.cstr() << "|\n";

    s1.resize(1, 'a');
    s1.resize(2);
    s3.resize(12);

    std::cout << "resize: |" << s1 << "|\n";
    std::cout << "resize: |" << s3 << "|\n";

    s1.assign("assign|s1 - success");
    s2.assign(s1);
    s3.assign("assign|s3 - success");
    s4.assign('4');
    s5.assign("assign|s5 - success");

    std::cout << "|" << s1 << "|\n";
    std::cout << "|" << s2 << "|\n";
    std::cout << "|" << s3 << "|\n";
    std::cout << "|" << s4 << "|\n";
    std::cout << "|" << s5 << "|\n";

    std::cout << "\nTest: try to assign the SString..." << std::endl;
    s1.assign(SString("The"));
    std::cout << "\nTest: try to assign the C-string..." << std::endl;
    s2.assign("goes");
    s3.assign("on");
    s4.assign("on");
    std::cout << "\nTest: try to assign the empty C-string..." << std::endl;
    s5.assign("");

    std::cout << "\nTest: try to append SString..." << std::endl;
    s1.append(SString(" road"));
    std::cout << "\nTest: try to append C-string..." << std::endl;
    s2.append(" ever");
    s3.append(" and");
    s4.append("...");
    s5.append("\n\t\t\tBilbo Baggins");

    std::cout << "\nTest: try addition C-string + SString..." << std::endl;
    s1 = " " + s2;

    std::cout << "\nTest: try addition char + SString..." << std::endl;
    s1 = ' ' + s2;

    std::cout << "\nTest: try addition SString + SString..." << std::endl;
    s1 = s1 + s2;

    std::cout << "\nTest: try to multiply addition..." << std::endl;
    s1 = s1 + " " + s2 + " " + s2 + " " + s3 + " " + s4 + s5 + "|";
    std::cout << "\tResult: " << s1 << std::endl;

    std::cout << "\nEnter two character seq:\n";
    std::cin >> s1;
    std::cin >> s2;
    std::cout << "|" << s1 + s2 << "|\n";

    std::cout << "\nMemory reallocate test:\n";
    SString memss;
    unsigned int test_len = 9999999;
    for (unsigned int i = 0; i < 99999999; ++i) {
        char ch = 'A' + i % ('z'-'A');
        memss.append(1, ch);
    }
    std::cout << "\nTest with operator bool() ";
    if (memss) {
        std::cout << "are passed\n";
        std::cout << memss.lenght() << std::endl;
    }
    else {
        std::cout << "are failed\n";
    }
    return 0;
}
