
#include <vector>
#include <cstdlib>

#include "heap.h"

HeapTree::HeapTree() : last(0) {}

HeapTree::HeapTree(int N)
    : container(N), last(0) {
}

void HeapTree::add(int el) {
    container.at(last++) = el;
    fixUp(last-1);
}

int HeapTree::getRoot() {
    std::swap(container[--last], container[0]);
    fixDown(0);
    return container[last];
}


void HeapTree::resize(size_t n) {
    container.resize(n);
}

void HeapTree::clean() {
    last = 0;
}

bool HeapTree::empty()const {
    return last == 0;
}

void showMe( std::ostream& os ) {
    
}

size_t HeapTree::parrent(size_t pos)const {
    return (pos+1)/2;
}

size_t HeapTree::firstChild(size_t pos)const {
    return pos*2+1;
}

void HeapTree::fixDown(size_t pos) {
    while( pos < last ) {
        size_t child = firstChild(pos);
        if( child < last && container[pos] < container[child] ) {
            std::swap(container[pos], container[child]);
            pos = child;
            continue;
        }
        else {
            if( ++child < last && container[pos] < container[child] ) {
                std::swap(container[pos], container[child]);
                pos = child;
                continue;
            }
        }
        break;
    }
}

void HeapTree::fixUp(size_t pos) {
    while( pos > 0 ) {
        size_t prt = parrent(pos);
        if( prt >= 0 && container[pos] > container[prt] ) {
            std::swap(container[pos], container[prt]);
            pos = prt;
            continue;
        }
        break;
    }
}

void HeapTree::ballanse(size_t pos) {
    if( pos < container.size() ) {
        fixUp(pos);
        fixDown(pos);
    }
}

