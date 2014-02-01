#include <iostream>
#include "../SString.h"

int main( int argN, char** argS ) {
    SString s1("##");
    SString s2("s2");
    std::cerr << "s1: /" << s1 << "/\n";
    std::cerr << "s2: /" << s2 << "/\n";
    std::cerr << "s3 = s1 + '|' + \" the end\"" << std::endl;
    SString s3 = 's' + s1;
    std::cerr << "s1: /" << s1 << "/\n";
    std::cerr << "s2: /" << s2 << "/\n";
    std::cerr << "s3: /" << s3 << "/\n";
    return 0;
}
