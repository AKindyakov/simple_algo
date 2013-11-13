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
    
    s1.assign("assign|s1");
    s2.assign(s1);
    s3.assign("assign|s3");
    s4.assign('4');
    s5.assign("assign|s5");
    
    std::cout << "|" << s1 << "|\n";
    std::cout << "|" << s2 << "|\n";
    std::cout << "|" << s3 << "|\n";
    std::cout << "|" << s4 << "|\n";
    std::cout << "|" << s5 << "|\n";
    
    s1.assign("The");
    s2.assign("goes");
    s3.assign("on");
    s4.assign("on");
    s5.assign("");
    
    s1.append(" road");
    s2.append(" ever");
    s3.append(" and");
    s4.append("...");
    s5.append("\n\t\tBilbo Baggins");
    
    std::cout << "+ |" << s1+" "+s2+" "+s2+" "+s3+" "+s4+s5 << "|\n";
    
    std::cout << "Enter two character seq:\n";
    std::cin >> s1;
    std::cin >> s2;
    std::cout << "|" << s1+s2 << "|\n";
    
    return 0;
}
