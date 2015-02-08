#include <redbalck_tree.h>

TRbEdge* TRbTree::find(const std::string& key) {
    std::cerr << "find( " << key << " )" << std::endl;
    TRbEdge* runPtr = &root;
    while (1) {
        if (!runPtr->node) {
            return runPtr;
        }
        int compareRez = runPtr->node->Key().compare(key);
        std::cerr << "      compareRez: " << compareRez << std::endl;
        if (compareRez == 0) {
            return runPtr;
        } else if (compareRez > 0) {
            runPtr = &runPtr->node->lessEdge;
        } else {  // compareRez < 0
            runPtr = &runPtr->node->greatEdge;
        }
    }
}


void TRbTree::insert(const std::string& key) {
    std::cerr << "insert( " << key << " )" << std::endl;
    TRbEdge* found = find(key);
    if (found->node) {
        throw KeyError("inserting key already exists \"" + key + '"');
    }
    std::cerr << "found " << static_cast<bool>(found->node) << std::endl;
    found->node.reset(new TRbNode(key, found));
    std::cerr << "insert - end" << std::endl;
}


TRbEdge* findMin(TRbEdge* from) {
    std::cerr << "minNode( " << from->node->Key() << " )" << std::endl;
    while (from->node) {
        from = &from->node->lessEdge;
    }
    return from;
}


void TRbTree::remove(const std::string& str) {
    TRbEdge* found = find(str);
    if (found->node) {
        if (found->node->lessEdge.node) {
            if (found->node->greatEdge.node) {
                TRbEdge* minNode = findMin(&found->node->greatEdge);
                std::cerr << "      minNode: " << minNode << " )" << std::endl;
                std::swap(minNode->node, found->node->lessEdge.node);
                std::swap(found->node, found->node->greatEdge.node);
            } else {
                std::swap(found->node, found->node->lessEdge.node);
            }
        } else {
            if (found->node->greatEdge.node) {
                std::swap(found->node, found->node->greatEdge.node);
            }
        }

    }
}


void TRbTree::assign(const std::string& key) {
    TRbEdge* finded = find(key);
    finded->node.reset(new TRbNode(key, finded));
}


bool TRbTree::has(const std::string& str) {
    return static_cast<bool>(find(str)->node);
}

