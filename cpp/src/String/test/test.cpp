#include <iostream>
#include "../SString.h"

int main( int argN, char** argS ) {
    SString s1;
    SString s2( "const char* cstr" );
    SString s3( 277, '?' );

    SString s4( s2 );
    SString s5( s2, 1, 7 );
    
    std::cout << "|" << s1.cstr() << "|\n";
    std::cout << "|" << s2.cstr() << "|\n";
    std::cout << "|" << s3.cstr() << "|\n";
    std::cout << "|" << s4.cstr() << "|\n";
    std::cout << "|" << s5.cstr() << "|\n";
    
    s1.resize(1, 'a');
    s1.resize(2);
    s3.resize(12);
    
    std::cout << "|" << s1.cstr() << "|\n";
    std::cout << "|" << s3.cstr() << "|\n";
    
    s1.assign("assign|s1");
    s2.assign(s1);
    s3.assign("assign|s3");
    s4.assign('4');
    s5.assign("assign|s5");
    
    std::cout << "|" << s1.cstr() << "|\n";
    std::cout << "|" << s2.cstr() << "|\n";
    std::cout << "|" << s3.cstr() << "|\n";
    std::cout << "|" << s4.cstr() << "|\n";
    std::cout << "|" << s5.cstr() << "|\n";
    
    s1.assign("s1");
    s2.assign("s2");
    s3.assign("s3");
    s4.assign("s4");
    s5.assign("s5");
    
    std::cout << "|" << s1+s2 << "|\n";
    std::cout << "|" << s2+"er" << "|\n";
    std::cout << "|" << "er"+s3 << "|\n";
    
    std::cout << "Enter:\n";
    std::cin >> s1;
    std::cin >> s2;
    std::cout << "|" << s1+s2 << "|\n";
    
    return 0;
}
