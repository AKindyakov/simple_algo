#include <iostream>
#include "../ZeroTerminatedStr.h"

int main( int argN, char** argS ) {
    ZeroTerminatedStr s1;
    ZeroTerminatedStr s2( "const char* cstr" );
    ZeroTerminatedStr s3( s2.maxsize(), '?' );
    ZeroTerminatedStr s4( s2 );
    ZeroTerminatedStr s5( s2, 1, 7 );
    
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
    
    std::cout << "|" << s1 << "|\n";
    std::cout << "|" << s2 << "|\n";
    std::cout << "|" << s3 << "|\n";
    std::cout << "|" << s4 << "|\n";
    std::cout << "|" << s5 << "|\n";
    
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
