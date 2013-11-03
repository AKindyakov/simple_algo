#include <iostream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <climits>

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

typedef std::map<char, SuffTreeEdge> EdgeContainer;
typedef std::pair<char, SuffTreeEdge> EdgeValue;

class SuffTreeNode {
public:
    SuffTreeNode();
    
    void addEdge( char ch, SuffTreeNode* to, int start, int end );
    void addEdge( char ch, SuffTreeNode* to, int start, int end, int strCount );
    
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
    void showMe(const string& str, int lvl, std::ostream& os)const;
    
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
    void showMe( std::ostream& os )const;
    
private:
    SuffTreeNode*  blank;
    SuffTreeNode*  root;
    string         str;
    
    int strCount;
    
    list<SuffTreeCursor> cursors;
    
    bool trackTheCursor(char ch, SuffTreeCursor* cursor );
    bool checkTrackTheCursor(char ch, SuffTreeCursor* cursor );
}

SuffTreeNode::SuffTreeNode() {
}

int SuffTreeNode::greatestSubstring( int lvl, list<SubString>* outSub ) {
    int maxLen = 0;
    list<SubString> maxSub;
    for( EdgeContainer::iterator it = edges.begin();
            it != edges.end(); ++it ) {
        if( it->second.prevGuest == lvl ) {
            list<SubString> lSub;
            int lLen = 0;
            lLen += it->second.to->greatestSubstring(lvl, &lSub);
            lLen += it->second.sub.endPos - it->second.sub.startPos;
            lSub.push_front(it->second.sub);
            //**/ std::cout << "len[" << it->first << "]: " << lLen << '\n';
            if( lLen > maxLen ) {
                maxLen = lLen;
                maxSub.clear();
                maxSub.splice(maxSub.end(), lSub);
            }
        }
    }
    outSub->splice(outSub->end(), maxSub);
    return maxLen;
}

void SuffTreeNode::showMe( const string& str, int lvl, std::ostream& os )const {
    for( EdgeContainer::const_iterator it = edges.begin();
            it != edges.end(); ++it ) {
        it->second.showMe(str, lvl+1, os);
    }
}

void SuffTreeEdge::finish( const string& str ) {
    if( sub.endPos == INT_MAX ) {
        sub.endPos = str.size();
    }
    if( to != NULL ) {
        to->finish(str);
    }
    else {
        SuffTreeNode* nNode = new SuffTreeNode;
        nNode->parrent = this;
        to = nNode;
    }
}

void SuffTreeEdge::showMe( const string& str, int lvl, std::ostream& os )const {
    int len = sub.endPos;
    if( sub.endPos == INT_MAX ) {
        len = str.size();
    }
    len -= sub.startPos;
    os  << string(lvl*4, ' ') 
        << " [" << str.substr(sub.startPos, len) << ']'
        << "| " << prevGuest << " {" << sub.startPos << ' ' << sub.endPos << '}' 
        << '\n';
    if( to != NULL ) {
        to->showMe(str, lvl+1, os);
    }
}

void SuffTreeNode::addEdge( char ch, SuffTreeNode* to, int start, int end ) {
    edges.insert( EdgeValue(ch, SuffTreeEdge(this, to, start, end) ) );
}

void SuffTreeNode::addEdge( char ch, SuffTreeNode* to, int start, int end, int strCount ) {
    edges.insert( EdgeValue(ch, SuffTreeEdge(this, to, start, end, strCount) ) );
}

EdgeContainer::iterator SuffTreeNode::findEdge( char ch ) {
    return edges.find(ch);
}

void SuffTreeNode::finish( const string& str ) {
    for( EdgeContainer::iterator it = edges.begin();
            it != edges.end(); ++it ) {
        it->second.finish( str );
    }
}

SuffTree::~SuffTree() {
    // dont forget to destroing }=/  @>-`-,-
}

SuffTree::SuffTree()
    :   blank( new SuffTreeNode ),
        root( new SuffTreeNode ),
        strCount( 0 ) {
    blank->addEdge(0, root, 0, 0);
    root->parrent = blank->firstEdge();
}

void SuffTree::add( char ch ) {
    //**/ std::cout << "ch : " << ch << '\n';
    cursors.push_back( SuffTreeCursor(blank->firstEdge(), 0));
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( trackTheCursor( ch, &*cIt ) ) {
            list<SuffTreeCursor>::iterator delIt = cIt--;
            cursors.erase(delIt);
        }
    }
    //**/ std::cout << "\tch : " << ch << '\n';
    str.push_back(ch);
    //**/ std::cout << "\t\tch : " << ch << '\n';
}

bool SuffTree::trackTheCursor(char ch, SuffTreeCursor* cursor ) {
    // Will you take red or blue pill ?
    // At the end of way?
    //**/ std::cout << "ch : " << ch << '\n';
    if( cursor->edge->sub.endPos == cursor->cursor+cursor->edge->sub.startPos ) {
        EdgeContainer::iterator find = cursor->edge->to->findEdge(ch);
        if( find == cursor->edge->to->emptyEdge() ) {
            //**/ std::cout << "\tadd\n";
            cursor->edge->to->addEdge( ch, NULL, str.size(), INT_MAX ); 
        }
        else {
            //**/ std::cout << "\twas found: " << ch << '\n';
            cursor->edge = &find->second;
            cursor->cursor = 1;
            return false;
        }
    }
    else {
        //**/ std::cout << "\tat : " << cursor->cursor << '\t'
        //**/           << str.size() << '\n';
        //**/ std::cout << "\tCompare: " 
        //**/           << str.at(cursor->edge->sub.startPos+cursor->cursor) 
        //**/           << " - " << ch << '\n';
        if( str.at(cursor->edge->sub.startPos + cursor->cursor) == ch ) {
            ++cursor->cursor;
            //**/ std::cout << "+: " << cursor->cursor << '\n'; 
            return false;
        }
        else {
            //**/ std::cout << "cursor " << cursor->cursor << '\n'; 
            SuffTreeNode* nNode = new SuffTreeNode;
            
            nNode->addEdge( ch, NULL, str.size(), INT_MAX );
            
            nNode->addEdge( str.at(cursor->edge->sub.startPos + cursor->cursor), 
                            cursor->edge->to, 
                            cursor->edge->sub.startPos + cursor->cursor,
                            cursor->edge->sub.endPos );
            
            nNode->parrent = cursor->edge;
            cursor->edge->to = nNode;
            cursor->edge->sub.endPos = cursor->edge->sub.startPos + cursor->cursor;
        }
    }
    return true;
}

void SuffTree::check( char ch ) {
    //**/ std::cout << "check : " << ch << '\n';
    cursors.push_back( SuffTreeCursor(blank->firstEdge(), 0));
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( checkTrackTheCursor( ch, &*cIt ) ) {
            list<SuffTreeCursor>::iterator delIt = cIt--;
            //**/ std::cout << "del: " << delIt->cursor << '\n';
            cursors.erase(delIt);
        }
    }
    //**/ showMe(std::cout);
}

bool SuffTree::checkTrackTheCursor(char ch, SuffTreeCursor* cursor ) {
    //**/ std::cout << "\t-> " << ch << '\n';
    if( cursor->edge->sub.endPos == cursor->cursor+cursor->edge->sub.startPos ) {
        //**/ std::cout << "\tEnd of edge " << ch << '\n';
        EdgeContainer::iterator find = cursor->edge->to->findEdge(ch);
        if( find != cursor->edge->to->emptyEdge() ) {
            //**/ std::cout << "\twas found: " << ch << '\n';
            cursor->edge->prevGuest = strCount;
            if( find->second.prevGuest == strCount 
                || find->second.prevGuest == strCount-1 ) {
                //**/ std::cout << "go to: " << ch << "  increment\n";
                cursor->edge = &find->second;
                cursor->cursor = 1;
                return false;
            }
        }
        else {
            cursor->edge->prevGuest = strCount;
        }
    }
    else {
        //**/ std::cout << "\t Not End of edge: " << ch << '\n';
        //**/ std::cout << "\tat : " << cursor->cursor << '\t'
        //**/           << str.size() << '\n';
        //**/ std::cout << "\tCompare: " 
        //**/           << str.at(cursor->edge->sub.startPos+cursor->cursor) 
        //**/           << " - " << ch << '\n';
        if( str.at(cursor->edge->sub.startPos + cursor->cursor) == ch ) {
            ++cursor->cursor;
            //**/ std::cout << "+: " << cursor->cursor << '\n'; 
            return false;
        }
        else {
            //**/ std::cout << "\t\t End of match: " << ch << '\n';
            //**/ std::cout << "cursor " << cursor->cursor << '\n'; 
            SuffTreeNode* nNode = new SuffTreeNode;
            nNode->addEdge( str.at(cursor->edge->sub.startPos + cursor->cursor), 
                            cursor->edge->to, 
                            cursor->edge->sub.startPos + cursor->cursor,
                            cursor->edge->sub.endPos,
                            cursor->edge->prevGuest );
            
            nNode->parrent = cursor->edge;
            cursor->edge->to = nNode;
            cursor->edge->sub.endPos = cursor->edge->sub.startPos + cursor->cursor;
            cursor->edge->prevGuest = strCount;
        }
    }
    return true;
}

void SuffTree::finishTree() {
    blank->finish(str);
}

void SuffTree::endString() {
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        //**/ std::cout << cIt->cursor << ' ' << cIt->edge->sub.startPos << ' ' << cIt->edge->sub.endPos << '\n';
        if( cIt->edge->sub.startPos + cIt->cursor != cIt->edge->sub.endPos ) {
            //**/ std::cout << "split - > \n";
            SuffTreeNode* nNode = new SuffTreeNode;
            nNode->addEdge( str.at(cIt->edge->sub.startPos + cIt->cursor), 
                            cIt->edge->to, 
                            cIt->edge->sub.startPos + cIt->cursor,
                            cIt->edge->sub.endPos );
            nNode->parrent = cIt->edge;
            cIt->edge->to = nNode;
            cIt->edge->sub.endPos = cIt->edge->sub.startPos + cIt->cursor;
        }
        cIt->edge->prevGuest = strCount;
    }
    cursors.clear();
    ++strCount;
}

std::string SuffTree::getGreatSubstring() {
    string gsub;
    list< SubString > gLSub;
    root->greatestSubstring( strCount-1, &gLSub );
    for( std::list< SubString >::iterator it =  gLSub.begin();
            it != gLSub.end(); ++it ) {
        gsub.append( str.substr(it->startPos, it->endPos - it->startPos) );
        //**/ std::cout << "append\n" << it->startPos << it->endPos << '\n';
    }
    
    return gsub;
}

void SuffTree::showMe( std::ostream& os )const {
    blank->showMe(str, 0, os);
}

int main( int argN, char** argS ) {
    try {
        int samples = 0;
        std::cin >> samples;
        std::cin.ignore();
        
        SuffTree tree;
        char ch = std::cin.get();
        while( ch != '\n' ) {
            tree.add(ch);
            ch = std::cin.get();
        }
        //**/ tree.showMe(std::cout);
        tree.endString();
        tree.finishTree();
        
        while( --samples ) {
            ch = std::cin.get();
            while( ch != '\n' ) {
                tree.check(ch);
                ch = std::cin.get();
            }
            tree.endString();
            //**/ tree.showMe(std::cout);
            //**/ std::cout << "Great: [" << tree.getGreatSubstring() << "]\n";
        }
        //**/ tree.showMe(std::cout);
        std::cout << tree.getGreatSubstring() << '\n';
    }
    catch(const std::exception& e) {
        std::cerr << "Std error "
                  << e.what() << '\n';
    }
    catch(...) {
        std::cerr << "Samething wrong\n";
    }
   
    return 0;
};
