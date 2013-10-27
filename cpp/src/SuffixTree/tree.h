#include <iostream>
#include <string>
#include <map>
#include <list>

using std::map;
using std::string;
using std::list;


class SuffTreeNode;

struct SubString {
    int startPos;
    int endPos;
};

class SuffTreeEdge {
public:
    SuffTreeEdge()
        :   from(NULL), to(NULL), 
            prevGuest(0) {
        sub.startPos = -1;
        sub.endPos = -1; 
    }
    
    SuffTreeEdge( SuffTreeNode* _from, SuffTreeNode* _to, int start, int end )
        :   from(_from), to(_to),
            prevGuest(0) {
        sub.startPos = start;
        sub.endPos = end; 
    }
    
    void showMe(const string& str, int lvl, std::ostream& os);
    
    void finish(const string& str);
    
    SuffTreeNode* from;
    SuffTreeNode* to;
    
    SubString sub;
    int prevGuest;
};

typedef std::map<char, SuffTreeEdge> EdgeContainer;
typedef std::pair<char, SuffTreeEdge> EdgeValue;

class SuffTreeNode {
public:
    SuffTreeNode();
    
    void addEdge( char ch, SuffTreeNode* to, int start, int end );
    
    EdgeContainer::iterator findEdge( char ch );
        
    EdgeContainer::const_iterator emptyEdge() {
        return edges.end();
    }
    
    SuffTreeEdge* firstEdge() {
        return &edges.begin()->second;
    }
    
    EdgeContainer::iterator firstEdgeIt() {
        return edges.begin();
    }
    
    int  greatestSubstring( int lvl, list<SubString>* outSub );
    void finish(const string& str);
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
    void finishTree();
    
    void check(char ch);
    void endString();
    
    std::string getGreatSubstring();
    void showMe( std::ostream& os );
    
private:
    SuffTreeNode*  blank;
    SuffTreeNode*  root;
    string         str;
    
    int strCount;
    
    list<SuffTreeCursor> cursors;
    
    bool trackTheCursor(char ch, SuffTreeCursor* cursor );
    bool checkTrackTheCursor(char ch, SuffTreeCursor* cursor );
};

