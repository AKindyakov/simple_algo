#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace NSufixTree {

const size_t ABC_SIZE = 26;
const char FIRST_ABC_CHAR = 'a';

struct TSubstring {
    TSubstring(
        const std::string* _str,
        size_t _start = 0,
        size_t _end = std::string::npos
    )
        : str(_str)
        , start(_start)
        , end(_end)
    {
    }

    const std::string* str;
    size_t start;
    size_t end;
};

class TNode;

class TEdge {
public:
    TEdge(
        const TSubstring& sub,
        TNode* parent
    )
        : parentNode(parent)
        , subString(sub)
    {
    }

    char head() const {
        return subString.str->at(subString.start);
    }

    void showMe(size_t lvl, std::ostream& os) const;
    size_t match(const TSubstring& sub) const;

    TNode* parentNode = nullptr;
    std::unique_ptr<TNode> endNode;
    TSubstring subString;
};

class TNode {
public:
    void showMe(size_t lvl, std::ostream& os) const;

    std::array<std::unique_ptr<TEdge>, ABC_SIZE> edges;
    TEdge* parrent = nullptr;
    TNode* suffixLink = nullptr;
};

struct SuffTreeCursor {
    SuffTreeCursor ( TEdge* _edge, int _cursor )
        :   edge(_edge), cursor(_cursor) {}

    TEdge* edge;
    int cursor;
};

class TTreeBase {
public:
    TTreeBase(const std::string& str)
        : text(str)
    {
        ukkonenRebuildTree();
    }

    virtual ~TTreeBase() {}

    void show(std::ostream& os) const;

private:
    void ukkonenRebuildTree();

    TNode root;
    std::string text;
};

}

using TSuffixTree = NSufixTree::TTreeBase;

