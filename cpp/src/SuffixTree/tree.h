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
    SuffTreeEdge()
        :   from(NULL), to(NULL), startPos(-1), endPos(-1) {}
    
    SuffTreeEdge( SuffTreeNode* _from, SuffTreeNode* _to, int start, int end )
        :   from(_from), to(_to), startPos(start), endPos(end) {}
    
    void showMe(const string& str, int lvl, std::ostream& os);
    SuffTreeNode* from;
    SuffTreeNode* to;
    
    int startPos;
    int endPos;
    
    int count;
    
    // Do you realy need it ?
    // char firstCh;
};

typedef std::map<char, SuffTreeEdge> EdgeContainer;
typedef std::pair<char, SuffTreeEdge> EdgeValue;

class SuffTreeNode {
public:
    SuffTreeNode();
    
    void addEdge( char ch, SuffTreeNode* to, int start, int end );
    
    EdgeContainer::iterator findEdge( char ch ) {
        return edges.find(ch);
    }
        
    EdgeContainer::const_iterator emptyEdge() {
        return edges.end();
    }
    
    SuffTreeEdge* firstEdge() {
        return &edges.begin()->second;
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
    
    std::string getGreatSubstring();
    void showMe( std::ostream& os );
    
private:
    SuffTreeNode*  blank;
    SuffTreeNode*  root;
    string         str;
    
    int strCount;
    
    list<SuffTreeCursor> cursors;
    
    bool trackTheCursor(char ch, SuffTreeCursor* cursor );
};

