/**
*
*
*/

#ifndef SIMPLE_ALGO_HEAP_TREE_INCLEDED
#define SIMPLE_ALGO_HEAP_TREE_INCLEDED

#include <vector>
#include <cstdlib>

class HeapTree {
public:
    HeapTree();
    explicit HeapTree(int N);

    void add(int el);
    int getRoot();

    bool empty()const;
    size_t getAllocatedSize()const;
    
    void resize(size_t n);
    
    void clean();
    
private:
    std::vector<int> container;
    size_t last;

    size_t parrent(size_t pos)const;
    size_t firstChild(size_t pos)const;
    void fixDown(size_t pos);
    void fixUp(size_t pos);
    
    void ballanse(size_t pos);
};

#endif // SIMPLE_ALGO_HEAP_TREE_INCLEDED

