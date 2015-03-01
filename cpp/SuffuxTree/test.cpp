#include <iostream>
#include <exception>
#include "tree.h"
#include <vector>

#include "../SimpleAlgoUtil/simple_exception.h"

int main( int argN, char** argS ) {
    try {
        int samples = 0;
        std::cin >> samples;
        std::cin.ignore();
        if( samples < 1 || samples > 10) {
            throw SimpleException("Unexpected algo list", __LINE__);
        }

        //std::vector<SuffTree> tree(--samples);
        SuffTree tree[9];
        for( int i=0; i < samples-1; ++i ) {
            char ch = std::cin.get();
            while( ch != '\n' ) {
                tree[i].add(ch);
                ch = std::cin.get();
                //**/ tree[samples].showMe(std::cout);
            }
            tree[i].finishTree();
            //**/ std::cout << "\n\n---------------------\n";
            //**/ tree[i].showMe(std::cout);
        }
        //**/ std::cout << "Generate compleete\n";

        std::string lastStr;
        char ch = std::cin.get();
        while( ch != '\n' ) {
            lastStr.push_back(ch);
            ch = std::cin.get();
        }
        size_t slen = lastStr.size();
        int rstart=0, rend=slen;
        int maxLen = 0;
        for( size_t st=0; st < slen; ++st ) {
            //std::cout << "st: " << st << '\n';
            if( slen-st < maxLen ) {
                //**/ std::cout << "break: " << 1 << '\n';
                break;
            }
            int wrk_end=slen;
            for( int i=0; i<samples-1; ++i ) {
                wrk_end = tree[i].findSub(lastStr, st, wrk_end);
                //**/ std::cout << "st: " << st << " i: " << i
                //**/           << " [" << st << ' ' << wrk_end << "]\n";
                if( wrk_end - st <= maxLen ) {
                    //**/ std::cout << "break: " << 2 << '\n';
                    break;
                }
            }
            if( wrk_end - st > maxLen ) {
                maxLen = wrk_end - st;
                rstart = st;
                rend   = wrk_end;
                //**/ std::cout << "max: " << maxLen
                //**/           << " [" << rstart << ' ' << rend << "]\n";
            }
        }
        //**/ tree.showMe(std::cout);
        std::cout << lastStr.substr(rstart, rend-rstart) << '\n';
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
