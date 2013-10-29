#include <iostream>
#include <exception>
#include "tree.h"
#include <vector>

#include "../SimpleAlgoException/simpleException.h"

int main( int argN, char** argS ) {
    try {
        int samples = 0;
        std::cin >> samples;
        std::cin.ignore();
        if( samples < 1 ) {
            throw SimpleException("Unexpected algo list", __LINE__);
        }
        
        std::vector<SuffTree> tree(--samples);
        char ch = std::cin.get();
        while( samples-- ) {
            std::cout << samples << " create\n";
            ch = std::cin.get();
            while( ch != '\n' ) {
                tree[samples].add(ch);
                ch = std::cin.get();
            }
            tree[samples].finishTree();
            //**/ tree.showMe(std::cout);
        }
        /**/ std::cout << "Generate compleete\n";
        
        std::string lastStr;
        ch = std::cin.get();
        while( ch != '\n' ) {
            lastStr.push_back(ch);
            ch = std::cin.get();
        }
        size_t slen = lastStr.size();
        int rstart=0, rend=0;
        int maxLen = 0;
        for( size_t st=0; st < slen; ++st ) {
            if( slen-st < maxLen ) {
                break;
            }
            int wrk_end=slen;
            for( std::vector<SuffTree>::const_iterator it = tree.begin();
                    it != tree.end(); ++it ) {
                wrk_end = it->findSub(lastStr, st, wrk_end);
                if( wrk_end - st < maxLen ) {
                    break;
                }
            }
            if( wrk_end - st > maxLen ) {
                maxLen = wrk_end - st;
                rstart = st;
                rend   = wrk_end;
            }
        }
        //**/ tree.showMe(std::cout);
        //std::cout << tree.getGreatSubstring() << '\n';
        std::cout << lastStr.substr(rstart, rend-rstart);
    }
    catch(const std::exception& e) {
        std::cerr << "Std error "
                  << e.what() << '\n';
    }
    catch(...) {
        std::cerr << "Samething wrong\n";
    }
   
    return 0;
}
