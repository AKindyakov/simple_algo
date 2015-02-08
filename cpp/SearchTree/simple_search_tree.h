#pragma once

#include "tree.h"

#include <memory>
#include <ostream>
#include <iostream>
#include <string>

class TSsEdge;
class TSsNode;

struct TSsEdge {
    TSsNode* parent = nullptr;
    std::unique_ptr<TSsNode> node = nullptr;
};

class TSsNode {
private:
    bool red = true;
    std::string sKey;

public:
    TSsEdge lessEdge;
    TSsEdge greatEdge;

    TSsEdge* sParent = nullptr;

public:
    explicit TSsNode(
        const std::string& key,
        TSsEdge* parent = nullptr
    )
        : sKey(key)
        , sParent(parent)
    {
        std::cerr << " + new TSsNode( " << sKey << " )" << std::endl;
    }

    ~TSsNode()
    {
        std::cerr << " - delete TSsNode( " << sKey << " )" << std::endl;
    }

    inline bool IsRed() { return red; }
    inline bool IsBlack() { return !red; }

    inline const std::string& Key() const { return sKey; }
    inline std::string& Key() { return sKey; }

public:
    //! Debug functions group
    void print(int deep, std::ostream& os) {
        os << std::string(deep*2, ' ') << "\\_" << sKey << '\n';
        if (lessEdge.node) {
            lessEdge.node->print(deep + 1, os);
        }
        if (greatEdge.node) {
            greatEdge.node->print(deep + 1, os);
        }
    }

    void inOrderPrint(std::string delimiter, std::ostream& os) {
        if (lessEdge.node) {
            lessEdge.node->inOrderPrint(delimiter, os);
        }
        os << delimiter << sKey;
        if (greatEdge.node) {
            greatEdge.node->inOrderPrint(delimiter, os);
        }
    }
};

class TSsTree:
    public ITree
{
private:
    TSsEdge root;

public:
    TSsTree()
    {
        std::cerr << "new TSsTree()" << std::endl;
    }

    ~TSsTree()
    {
        std::cerr << "delete TSsTree()" << std::endl;
    }

    void insert(const std::string& str) override;
    void remove(const std::string& str) override;
    void assign(const std::string& str) override;
    bool has(const std::string& str) override;

    void print(std::ostream& os) {
        std::cerr << "print (std::ostream& os)" << std::endl;
        root.node->print(0, os);
    }

    void inOrderPrint(std::ostream& os) {
        std::cerr << "inOrderPrint (std::ostream& os)" << std::endl;
        root.node->inOrderPrint(" ", os);
        os << std::endl;
    }

private:
    TSsEdge* find(const std::string& str);
};

