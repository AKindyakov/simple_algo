#include <iostream>
#include <string>
//#include <map>
#include <list>

using std::string;
using std::list;

const int ABC_SIZE = 26;
const int FIRST_ABC_CHAR = 'a';

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
    
    SuffTreeEdge( SuffTreeNode* _from, SuffTreeNode* _to, int start, int end, int count=0 )
        :   from(_from), to(_to),
            prevGuest(count) {
        sub.startPos = start;
        sub.endPos = end; 
    }
    
    void showMe(const string& str, int lvl, std::ostream& os)const;
    
    void finish(const string& str);
    
    SuffTreeNode* from;
    SuffTreeNode* to;
    
    SubString sub;
    int prevGuest;
};

class SuffTreeNode {
public:
    SuffTreeNode();
    
    void addEdge( char ch, SuffTreeNode* to, int start, int end, int strCount );
    
    SuffTreeEdge* findEdge( char ch );
        
    SuffTreeEdge* firstEdgePt() {
        return *edges;
    }
    
    int  greatestSubstring( int lvl, list<SubString>* outSub );
    void finish(const string& str);
    void showMe(const string& str, int lvl, std::ostream& os)const;
    
    SuffTreeEdge* edges[ ABC_SIZE ];
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
    
    std::string getGreatSubstring()const;
    void showMe( std::ostream& os )const;
    
private:
    SuffTreeNode*  blank;
    SuffTreeNode*  root;
    string         str;
    
    int strCount;
    
    list<SuffTreeCursor> cursors;
    
    bool trackTheCursor(char ch, SuffTreeCursor* cursor );
    bool checkTrackTheCursor(char ch, SuffTreeCursor* cursor );
};

