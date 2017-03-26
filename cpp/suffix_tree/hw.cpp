#include <deque>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include "../simple_algo_util/simple_exception.h"

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

namespace NSufixTree {

TEdge* TEdge::split(size_t cursor) {
    if (!subString.positionIsValid(cursor)) {
        throw TSimpleException()
            << "invalid position for split"
            << "; start: " << subString.start
            << "; cur: " << cursor
            << "; end: " << subString.end
        ;
    }

    TSubstring downPart(subString);
    downPart.start = downPart.start + cursor;
    subString.end = subString.start + cursor;

    //*dbg*/ std::cerr << "split through cur: " << cursor << std::endl;
    //*dbg*/ std::cerr << "up interval: "
    //*dbg*/     << "; start: " << subString.start
    //*dbg*/     << "; end: " << subString.end
    //*dbg*/     << std::endl
    //*dbg*/ ;
    //*dbg*/ std::cerr << "down interval: "
    //*dbg*/     << "; start: " << downPart.start
    //*dbg*/     << "; end: " << downPart.end
    //*dbg*/     << std::endl
    //*dbg*/ ;

    std::unique_ptr<TNode> newNode(new TNode(this));
    newNode->addEdge(downPart);
    newNode->get(downPart.head())->endNode.swap(endNode);
    endNode.swap(newNode);
    return endNode->get(downPart.head());
}

void TTreeBase::ukkonenRebuildTree() {
    std::deque<TUkkonenBuildCursor> cursors;
    for (size_t i = 0; i < text.size(); ++i) {
        //*dbg*/ std::cerr << "ukkonenPush i: " << i << " ch: " << text[i] << "\n";
        ukkonenPush(cursors, i);
        //*dbg*/ std::cerr << "\n";
        // show(std::cerr);
        //*dbg*/ std::cerr << "----------------------------------------------\n\n";
    }
    rootEdge.endNode->suffixLink = rootEdge.endNode.get();
}

void
TTreeBase::ukkonenPush(
    std::deque<TUkkonenBuildCursor>& cursors,
    size_t position
) {
    cursors.emplace_back(TUkkonenBuildCursor(&rootEdge));
    TNode* nodeForLink = nullptr;

    while (cursors.front().deleted) {
        cursors.pop_front();
    }
    //*dbg*/ size_t counter = 0;
    for (auto& cursor : cursors) {
        if (cursor.deleted) {
            //*dbg*/ std::cerr << counter++ << ": skip deleted cursor\n";
            /*dbg*/ throw TSimpleException("impossible situation");
            continue;
        }
        //*dbg*/ else {
        //*dbg*/     std::cerr << counter++ << ": cursor: \n";
        //*dbg*/ }
        int stepType = cursor.step(position);
        //*dbg*/ std::cerr << "step: " << stepType << "\n\n";

        if (stepType > 1) {
            TNode* currentNode = cursor.edge->parentNode;
            if (nodeForLink != nullptr && nodeForLink->suffixLink == nullptr) {
                //*dbg*/ std::cerr << "link\n";
                nodeForLink->suffixLink = currentNode;
            }
            nodeForLink = currentNode;
        }
        if (stepType == 2) {
            cursor.deleted = true;
        }
    }
}

int TUkkonenBuildCursor::step(size_t position) {
    //*dbg*/ std::cerr << "step(\n"
    //*dbg*/     << "  pos: " << position << " -> '" << edge->subString.str->at(position) << "'\n"
    //*dbg*/     << "  cur: " << cursor   << "'\n"
    //*dbg*/     << "  sub: " << edge->subString.copy() << "\n"
    //*dbg*/     << ")" << std::endl
    //*dbg*/ ;

    if (cursor > edge->size()) {
        //*dbg/ std::cerr << "respawn ("
        //*dbg/     << "\n  cursor: " << cursor
        //*dbg/     << "\n  size: " << edge->subString.size()
        //*dbg/     << "\n  sub: " << edge->subString.copy()
        //*dbg/     << "\n)" << std::endl
        //*dbg/ ;
        cursor = cursor - edge->size();
        char prevEndChar = edge->subString.str->at(edge->subString.end);
        edge = edge->endNode->get(prevEndChar);
    }

    int stepType = 0;
    if (edge->subString.positionIsValid(cursor)) {
        //*dbg*/ std::cerr << "position is valid" << std::endl;
        if (edge->subString.at(cursor) == edge->subString.str->at(position)) {
            //! just follow
            //*dbg*/ std::cerr << "just follow" << std::endl;
            stepType = 1;
        } else {
            //*dbg*/ std::cerr << "split" << std::endl;
            edge->split(cursor);
            edge = edge->endNode->addEdge(TSubstring(*edge->subString.str, position));
            stepType = 2;
            cursor = 0;
        }
    } else {
        if (edge->endNode == nullptr) {
            //! create node at the end
            //*dbg*/ std::cerr << "create end node" << std::endl;
            edge->endNode.reset(
                new TNode(edge)
            );
        }
        char ch = edge->subString.str->at(position);
        if (edge->endNode->has(ch)) {
            edge = edge->endNode->get(ch);
            //*dbg*/ std::cerr << "Yes! Third type" << std::endl;
            stepType = 3; // Yes! Third type of step
            cursor = 0;
        } else {
            //*dbg*/ std::cerr << "Add edge to node (" << edge->subString.copy() << ")\n";
            edge->endNode->addEdge(
                TSubstring(*edge->subString.str, position)
            );
            edge = edge->endNode->get(ch);
            stepType = 2;
            cursor = 0;
        }
    }
    ++cursor;
    return stepType;
}

void TEdge::show(size_t lvl, std::ostream& os) const {
    size_t end = subString.end;
    const std::string* fullStrPtr = subString.str;
    if (end > fullStrPtr->size()) {
        end = fullStrPtr->size();
    }
    os << '[' << subString.start << ':' << end << "] " << subString.copy() << "\n";
    //*dbg*/ std::cerr << "edge show\n";
    if (endNode != nullptr) {
        endNode->show(lvl + 1, os);
    }
    //*dbg*/ std::cerr << "edge show end\n";
}

void TNode::show(size_t lvl, std::ostream& os) const {
    //*dbg*/ std::cerr << "node show\n";
    ++lvl;

    // os << " ----> " << (suffixLink == nullptr) << "\n";
    os << std::string(lvl, ' ') << "---> " << suffixLink->parent->subString.copy() << "\n";
    for (size_t i = 0; i < edges.size(); ++i) {
        if (nullptr != edges[i]) {
            os  << std::string(lvl, ' ')
                << "-("
                << static_cast<char>(FIRST_ABC_CHAR + i)
                << "): "
            ;
            edges[i]->show(lvl, os);
        }
    }
}

void TTreeBase::show(std::ostream& os) const {
    rootEdge.show(0, os);
}

}

class TFuzzySearch: public TSuffixTreeBase {
public:
    explicit TFuzzySearch(const std::string& text, char _wildcard = '?')
        : TSuffixTreeBase(text)
        , wildcard(_wildcard)
    {
    }

    using TSubstring = NSufixTree::TSubstring;
    using TConstTreeCursor = NSufixTree::TConstTreeCusor;

    std::vector<TSubstring> search(const std::string& pattern) const {
        bool onlyFirst = false;
        return findAllEnds(onlyMatch(pattern, onlyFirst), pattern.size());
    }

    bool search(const std::string& pattern, TSubstring& answer) const {
        bool onlyFirst = true;
        std::vector<TConstTreeCursor> ends = onlyMatch(pattern, onlyFirst);
        if (ends.empty()) {
            return false;
        }
        answer = ends.front().edge->subString;
        answer.end = answer.start + ends.front().cursor;
        answer.start = answer.end - pattern.size();
        return true;
    }

private:
    std::vector<TConstTreeCursor>
    onlyMatch(
        const std::string& pattern,
        bool onlyFirst
    ) const;

    std::vector<TSubstring>
    findAllEnds(
        const std::vector<TConstTreeCursor>& endPoints,
        size_t patternSize
    ) const;

private:
    char wildcard;
};

std::vector<TFuzzySearch::TConstTreeCursor>
TFuzzySearch::onlyMatch(
    const std::string& pattern,
    bool onlyFirst
) const {
    std::deque<TConstTreeCursor> treeQueue = {
        TConstTreeCursor(&rootEdge)
    };
    std::deque<size_t> patternQueue = {0};

    std::vector<TConstTreeCursor> matched;

    while (!treeQueue.empty()) {
        size_t deep = patternQueue.back();
        TConstTreeCursor cursor = treeQueue.back();
        while (true) {
            if (deep >= pattern.size()) {
                matched.push_back(cursor);
                break;
            }
            char pch = pattern[deep];
            if (cursor.end()) {
                if (pch == wildcard) {
                    if (cursor.edge->endNode) {
                        for (const auto& edge : cursor.edge->endNode->edges) {
                            if (edge) {
                                patternQueue.push_front(deep);
                                treeQueue.push_front(TConstTreeCursor(edge.get()));
                            }
                        }
                    }
                    break;
                } else {
                    auto next = cursor.edge->endNode->get(pattern[deep]);
                    if (next == nullptr) {
                        break;
                    } else {
                        cursor = TConstTreeCursor(next);
                    }
                }
            } else {
                if (pch != cursor.ch() && pch != wildcard) {
                    break;
                }
            }
            ++cursor;
            ++deep;
        }
        patternQueue.pop_back();
        treeQueue.pop_back();
    }
    return matched;
}

std::vector<TFuzzySearch::TSubstring>
TFuzzySearch::findAllEnds(
    const std::vector<TConstTreeCursor>& endPoints,
    size_t patternSize
) const {
    std::vector<TSubstring> rezult;

    for (const auto& point : endPoints) {
        std::deque<TConstTreeCursor> nodeQueue = {point};
        std::deque<size_t> deepQueue = {0};

        while (!nodeQueue.empty()) {
            size_t deep = deepQueue.back();
            TConstTreeCursor cursor = nodeQueue.back();
            deepQueue.pop_back();
            nodeQueue.pop_back();
            while (true) {
                if (cursor.end()) {
                    if (cursor.edge->endNode) {
                        size_t t = 0;
                        for (const auto& edge : cursor.edge->endNode->edges) {
                            if (edge) {
                                ++t;
                                deepQueue.push_front(deep);
                                nodeQueue.push_front(TConstTreeCursor(edge.get()));
                            }
                        }
                        if (t == 0) {
                            throw TSimpleException("realy?");
                        }
                    } else {
                        rezult.push_back(
                            TSubstring(
                                text,
                                text.size() - deep - patternSize,
                                text.size() - deep
                            )
                        );
                    }
                    break;
                }
                ++cursor;
                ++deep;
            }
        }

    }
    return rezult;
}

int main(int /*argn*/, const char** /*args*/) {
    std::string text;
    std::string pattern;
    std::cin >> pattern;
    std::cin >> text;

    std::cerr << "pattern: " << pattern << std::endl;
    std::cerr << "text: " << text << std::endl;

    TFuzzySearch searcher(text, '?');
    std::vector<TFuzzySearch::TSubstring> rez = searcher.search(pattern);
    std::vector<size_t> starts;
    for (const auto& r : rez) {
        starts.push_back(r.start);
        std::cerr << "r: " << r.copy() << std::endl;
    }
    std::sort(starts.begin(), starts.end());
    std::cout << starts.size() << std::endl;
    for (const auto& s : starts) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    return 0;
}
