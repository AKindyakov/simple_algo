#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using std::vector;
using std::string;


void getLargestCommonSubstring( string* result, const string& a, const string& b ) {
    const int aSize = a.size();
    const int bSize = b.size();
 
    typedef vector<int> SolutionT;
 
    const int solution_size = bSize + 1;
    SolutionT x( solution_size, 0 );
    SolutionT y( solution_size );
 
    SolutionT* previous = &x;
    SolutionT* current  = &y;
 
    int max_length   = 0;
    int result_index = 0;
 
    for( int i = aSize-1; i >= 0; --i ) {
        for( int j = bSize-1; j >= 0; --j ) {
            if( a[i] != b[j] ) {
                (*current)[j] = 0;
            }
            else {
                const int length = 1 + (*previous)[j + 1];
                if( length > max_length ) {
                    max_length = length;
                    result_index = i;
                }
                (*current)[j] = length;
            }
        }
        std::swap(previous, current);
    }
    *result = a.substr(result_index, max_length);
}


int main( int argN, char** argS ) {
    std::string a("asdfgqw000000asdfg");   
    std::string b("yuifgqooooasdfg");   
    std::string rez;
    getLargestCommonSubstring( &rez, a, b );
    std::cout << "Hello: " << rez << '\n';
    return 0;
}
