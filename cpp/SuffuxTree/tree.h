#include <iostream>
#include <string>

namespace NSufixTree {

const size_t ABC_SIZE = 26;
const char FIRST_ABC_CHAR = 'a';

class TNode;

struct TSubstring {
    TSubstring(const std::string& base, size_t s = 0, size_t e = std::string::npos)
        : start(s), end(e)
    {
    }
    size_t start;
    size_t end;
    const std::string* str;
};

class TEdge {
public:
    TEdge()
        :   from(NULL), to(NULL),
            prevGuest(0) {
        sub.start = -1;
        sub.end = -1;
    }

    TEdge( TNode* _from, TNode* _to, int start, int end, int count=0 )
        :   from(_from), to(_to),
            prevGuest(count) {
        sub.start = start;
        sub.end = end;
    }

    char head() const;
    void showMe(size_t lvl, std::ostream& os) const;
    size_t match(const string& modelStr, size_t start, size_t end) const;

    void finish(const string& str);

private:
    TNode* parentNode;
    std::unique_ptr<TNode> endNode;
    TSubstring sub;
};

class TNode {
public:
    TNode();

    void addEdge( char ch, TNode* to, int start, int end, int strCount );

    TEdge* findEdge( char ch );

    TEdge* firstEdgePt() {
        return *edges;
    }

    int  greatestSubstring( int lvl, list<TSubstring>* outSub );
    int findSub( const string& modelStr, const string& str, int start, int end )const;
    void finish(const string& str);
    void showMe(const string& str, int lvl, std::ostream& os) const;

    TEdge* edges[ABC_SIZE];
    TEdge* parrent;
};

struct SuffTreeCursor {
    SuffTreeCursor ( TEdge* _edge, int _cursor )
        :   edge(_edge), cursor(_cursor) {}

    TEdge* edge;
    int cursor;
};

class TSuffixTree {
public:
    TSuffixTree(const std::string& str);
    virtual ~TSuffixTree();

    std::vector<size_t> match(const std::string& pattern) const;
    void show(std::ostream& os) const;

private:
    TNode root;
    std::string text;
};

}

