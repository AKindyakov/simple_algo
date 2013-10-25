#include <iostream>
#include <string>
#include <map>
#include <list>

using std::map;
using std::string;
using std::list;


class SuffTreeNode;

class SuffTreeEdge {
public:
    SuffTreeEdge();
    
    SuffTreeEdge( SuffTreeNode* _from, SuffTreeNode* _to, int start, int end );
    
    ~SuffTreeEdge();
    
    void showMe(const string& str, int lvl, std::ostream& os);
    //SuffTreeEdge& operator=(const SuffTreeEdge& e) {
    //    from = e.from;
    //    to = e.to;
    // / 
    //    startPos = e.startPos;
    //    endPos  = e.endPos;
    //    counter = e.counter;
    //    return *this;
    //}
    
    SuffTreeNode* from;
    SuffTreeNode* to;
    
    int startPos;
    int endPos;
    int counter;
};

typedef std::map<char, SuffTreeEdge> EdgeContainer;
typedef std::pair<char, SuffTreeEdge> EdgeValue;

class SuffTreeNode {
public:
    SuffTreeNode();
    ~SuffTreeNode();
    
    void addEdge( char ch, SuffTreeNode* to, int start, int end );
    
    EdgeContainer::iterator findEdge( char ch ) {
        return edges.find(ch);
    }
    
    EdgeContainer::const_iterator findEdge( char ch )const {
        return edges.find(ch);
    }
        
    EdgeContainer::const_iterator emptyEdge()const {
        return edges.end();
    }

    // del me !!
    SuffTreeEdge* firstEdge() {
        return &edges.begin()->second;
    }
    
    EdgeContainer::iterator beginEdge() {
        return edges.begin();
    }
    
    void killEdge(EdgeContainer::iterator it) {
        edges.erase(it);
    }
    
    void showMe(const string& str, int lvl, std::ostream& os);
    
    EdgeContainer edges;
    SuffTreeEdge* parrent;
};

struct SuffTreeCursor {
    SuffTreeCursor ( SuffTreeEdge* _edge, int _cursor )
        :   edge(_edge), cursor(_cursor) {}
    SuffTreeEdge* edge;
    int cursor;
};

class SuffTree {
public:
    SuffTree();
    virtual ~SuffTree();
    
    void add(char ch);
    void endString();
    
    void eraseNotCommon( const SuffTree& tr );
    std::string getGreatSustring();
    
    void showMe( std::ostream& os );
    
private:
    SuffTreeNode*  blank;
    SuffTreeNode*  root;
    string         str;
    list<SuffTreeCursor> cursors;
    int strCount;
    
    bool trackTheCursor(char ch, SuffTreeCursor* cursor );
    bool compareNode( SuffTreeNode* node, const SuffTreeNode& cNode);
};

