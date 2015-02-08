#pragma once

#include "tree.h"

class TRbEdge;
class TRbNode;

struct TRbEdge {
    TRbNode* parent = nullptr;
    std::unique_ptr<TRbNode> node = nullptr;
};

class TRbNode {
private:
    bool red = true;
    std::string sKey;

public:
    TRbEdge lessEdge;
    TRbEdge greatEdge;

    TRbEdge* sParent = nullptr;

public:
    explicit TRbNode(
        const std::string& key,
        TRbEdge* parent = nullptr
    )
        : sKey(key)
        , sParent(parent)
    {
        std::cerr << " + new TRbNode( " << sKey << " )" << std::endl;
    }

    ~TRbNode()
    {
        std::cerr << " - delete TRbNode( " << sKey << " )" << std::endl;
    }

    inline bool IsRed() { return red; }
    inline bool IsBlack() { return !red; }

    inline const std::string& Key() const { return sKey; }
    inline std::string& Key() { return sKey; }

public:
    //! Debug functions group
    void print(int deep, std::ostream& os) {
        os << std::string(deep, ' ') << '+' << sKey << '\n';
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

class TRbTree:
    public ITree
{
private:
    //std::shared_ptr<TRbNode> root;
    TRbEdge root;

public:
    TRbTree()
    {
        std::cerr << "new TRbTree()" << std::endl;
    }

    ~TRbTree()
    {
        std::cerr << "delete TRbTree()" << std::endl;
    }

    void insert(const std::string& str) override;
    void remove(const std::string& str) override;
    void assign(const std::string& str) override;
    bool has(const std::string& str) override;

    void print(std::ostream& os) {
        std::cerr << "print ()" << std::endl;
        root.node->print(0, os);
    }

    void inOrderPrint(std::ostream& os) {
        std::cerr << "inOrderPrint:" << std::endl;
        root.node->inOrderPrint(" ", os);
        os << std::endl;
    }

private:
    TRbEdge* find(const std::string& str);
};

