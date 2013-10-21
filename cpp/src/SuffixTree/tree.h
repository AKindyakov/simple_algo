#include <iostream>
#include <string>
#include <map>

using std::map;
using std::string;


class SuffTreeNode;

class SuffTreeEdge {
public:
    SuffTreeEdge()
        :   from(NULL), to(NULL), startPos(-1), endPos(-1) {}
    
    SuffTreeEdge( SuffTreeNode* _from, SuffTreeNode* _to, int start, int end )
        :   from(_from), to(_to), startPos(start), endPos(end) {}
    
    SuffTreeNode* from;
    SuffTreeNode* to;
    
    int startPos;
    int endPos;
    
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
    
    EdgeContainer edges;
    SuffTreeEdge* parrent;
};

struct SuffTreeCursor {
    SuffTreeEdge* edge;
    int cursor;
};

class SuffTree {
public:
    SuffTree();
    virtual ~SuffTree();
    
    void add(char ch);
    void showMe( std::ostream& os );
    
private:
    SuffTreeNode*  blank;
    SuffTreeNode*  root;
    string         str;
    SuffTreeCursor cursor;
    SuffTreeNode*  splitEdge( SuffTreeCursor pos );
};
