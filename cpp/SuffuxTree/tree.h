#pragma once

#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../SimpleAlgoUtil/simple_exception.h"

namespace NSufixTree {

const char SENTINEL_CHAR = '`';
const char FIRST_ABC_CHAR = SENTINEL_CHAR;
const char LAST_ABC_CHAR = 'z';
const size_t ABC_SIZE = LAST_ABC_CHAR - SENTINEL_CHAR;

struct TSubstring {
    /**
    * in TSubstring abacabac:
    *    full string: <--abacabac-->
    *                    ^       ^
    *                   start   end
    */
    TSubstring(
        const std::string& _str,
        size_t _start = 0,
        size_t _end = std::string::npos
    )
        : str(&_str)
        , start(_start)
        , end(_end)
    {
        if (end < start) {
            throw TSimpleException()
                << "End of substring greater start"
                << ".   start: " << start
                << ".   end: " << end
                ;
        }
    }

    TSubstring& operator=(const TSubstring& model) {
        str = model.str;
        start = model.start;
        end = model.end;
        return *this;
    }

    bool positionIsValid(size_t pos) const {
        return pos < end - start && pos < str->size() - start;
    }

    char at(size_t pos) const {
        if (start + pos >= end) {
            throw TSimpleException("TSubstring::at() error");
        }
        return str->at(start + pos);
    }

    char head() const {
        return str->at(start);
    }

    std::string copy() const {
        return std::string(*str, start, size());
    }

    size_t size() const {
        return end - start;
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
        return subString.head();
    }

    char at(size_t pos) const {
        return subString.at(pos);
    }

    size_t size() const {
        return subString.size();
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
        : parent(_parrent)
    {
    }

    void show(size_t lvl, std::ostream& os) const;

    bool has(char ch) {
        return nullptr != edges[ch - FIRST_ABC_CHAR];
    }

    TEdge* get(char ch) {
        return edges[ch - FIRST_ABC_CHAR].get();
    }

    TEdge* addEdge(const TSubstring& sub) {
        //*dbg*/ std::cerr << "add: \'" << sub.head() << '\'' << std::endl;
        edges[sub.head() - FIRST_ABC_CHAR].reset(
            new TEdge(sub, this)
        );
        return edges[sub.head() - FIRST_ABC_CHAR].get();
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
    TEdge* parent = nullptr;

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

template<typename TTEdge = TEdge>
class TTreeCursor {
public:
    TTreeCursor(
        TTEdge* _edge,
        size_t _cursor = 0
    )
        : edge(_edge)
        , cursor(_cursor)
    {
    }

    ~TTreeCursor() {}

    bool end() const {
        return !edge->subString.positionIsValid(cursor);
    }

    size_t operator++() {
        return ++cursor;
    }

    char ch() const {
        return edge->subString.at(cursor);
    }

public:
    TTEdge* edge;
    size_t cursor;

};

using TConstTreeCusor = TTreeCursor<const TEdge>;

class TUkkonenBuildCursor
    : public TTreeCursor<TEdge>
{
public:
    TUkkonenBuildCursor(
        TEdge* _edge,
        size_t _cursor = 0
    )
        : TTreeCursor(_edge, _cursor)
    {
    }

    int step(size_t position);
    bool deleted = false;
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
        text.push_back(SENTINEL_CHAR);
        ukkonenRebuildTree();
    }

    virtual ~TTreeBase() {}
    void show(std::ostream& os) const;

private:
    void ukkonenRebuildTree();
    void ukkonenPush(std::deque<TUkkonenBuildCursor>&, size_t);

protected:
    std::string text;
    TEdge rootEdge;
};

}

using TSuffixTreeBase = NSufixTree::TTreeBase;

