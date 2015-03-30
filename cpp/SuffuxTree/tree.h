#pragma once

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../SimpleAlgoUtil/simple_exception.h"

namespace NSufixTree {

const size_t ABC_SIZE = 26;
const char FIRST_ABC_CHAR = 'a';

struct TSubstring {
    TSubstring(
        const std::string& _str,
        size_t _start = 0,
        size_t _end = std::string::npos
    )
        : str(_str)
        , start(_start)
        , end(_end)
    {
    }

    bool positionIsValid(size_t pos) const {
        return pos < end && pos < str.size();
    }

    char head() const {
        return str[start];
    }

    std::string copy() const {
        return std::string(
            str,
            start,
            end - start
        );
    }

    const std::string& str;
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
        return subString.head();
    }

    TEdge* split(size_t position);

    void show(size_t lvl, std::ostream& os) const;

    TNode* parentNode = nullptr;
    std::unique_ptr<TNode> endNode;
    TSubstring subString;
};

class TNode {
public:
    TNode(TEdge* _parrent)
        : parrent(_parrent)
    {
    }

    void show(size_t lvl, std::ostream& os) const;

    bool has(char ch) {
        return nullptr != edges[ch - FIRST_ABC_CHAR];
    }

    TEdge* get(char ch) {
        return edges[ch - FIRST_ABC_CHAR].get();
    }

    void addEdge(const TSubstring& sub) {
        edges[sub.head() - FIRST_ABC_CHAR].reset(
            new TEdge(sub, this)
        );
    }

    void addLink(TNode* node) {
        if (suffixLink == nullptr) {
            suffixLink = node;
        } else {
            throw TSimpleException()
                << "Wrong attempt to redefine the suffix link"
            ;
        }
    }

    std::array<std::unique_ptr<TEdge>, ABC_SIZE> edges;
    TEdge* parrent = nullptr;

    /*
    * Определение:
    * Пусть x\alpha обозначает произвольную строку, где x - ее первый символ, а \alpha
    * - оставшаяся подстрока(возможно пустая). Если для внутренней вершины v с путевой
    * меткой x\alpha существует другая вершина s(v) с путевой меткой \alpha, то ссылка
    * из v в s(v) называется суффиксной ссылкой.

    * Лемма (Существование суффиксных ссылок):
    * Для любой внутренней вершины v суффиксного дерева существует суффиксная ссылка,
    * ведущая в некоторую внутреннюю вершину u.
    */
    TNode* suffixLink = nullptr;
};

class TTreeCursor {
public:
    TTreeCursor(
        TEdge* _edge,
        size_t _cursor = 0
    )
        : edge(_edge)
        , cursor(_cursor)
    {
    }

    int step(size_t position);

    TEdge* edge;
    size_t cursor;
};

class TTreeBase {
public:
    TTreeBase(const std::string& str)
        : text(str)
        , rootEdge(
            TSubstring(text, 0, 0),
            nullptr
        )
    {
        ukkonenRebuildTree();
        std::cerr << "build finish\n";
    }

    virtual ~TTreeBase() {}

    void show(std::ostream& os) const;

private:
    void ukkonenRebuildTree();
    void ukkonenPush(size_t position);

    std::string text;
    TEdge rootEdge;

    //! building vars
    std::deque<TTreeCursor> cursors;
};

}

using TSuffixTree = NSufixTree::TTreeBase;

