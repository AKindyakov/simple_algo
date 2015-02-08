#include "simple_search_tree.h"

#include <exception>
#include <iostream>
#include <memory>


TSsEdge* TSsTree::find(const std::string& key) {
    std::cerr << "find( " << key << " )" << std::endl;
    TSsEdge* runPtr = &root;
    while (1) {
        if (!runPtr->node) {
            return runPtr;
        }
        int compareRez = runPtr->node->Key().compare(key);
        if (compareRez == 0) {
            return runPtr;
        } else if (compareRez > 0) {
            runPtr = &runPtr->node->lessEdge;
        } else {  // compareRez < 0
            runPtr = &runPtr->node->greatEdge;
        }
    }
}


void TSsTree::insert(const std::string& key) {
    std::cerr << "insert( " << key << " )" << std::endl;
    TSsEdge* found = find(key);
    if (found->node) {
        throw KeyError("inserting key already exists \"" + key + '"');
    }
    std::cerr << "      found: " << static_cast<bool>(found->node) << std::endl;
    found->node.reset(new TSsNode(key, found));
}


TSsEdge* findMin(TSsEdge* from) {
    std::cerr << "minNode( " << from->node->Key() << " )" << std::endl;
    while (from->node) {
        from = &from->node->lessEdge;
    }
    return from;
}

void TSsTree::remove(const std::string& str) {
    TSsEdge* found = find(str);
    if (found->node) {
        if (found->node->lessEdge.node) {
            if (found->node->greatEdge.node) {
                TSsEdge* minNode = findMin(&found->node->greatEdge);
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

void TSsTree::assign(const std::string& key) {
    TSsEdge* finded = find(key);
    finded->node.reset(new TSsNode(key, finded));
}

bool TSsTree::has(const std::string& str) {
    return static_cast<bool>(find(str)->node);
}

