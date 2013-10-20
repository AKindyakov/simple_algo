#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>

using std::list;
using std::vector;
using std::string;

const int CHAR_LIMIT = 26; // only 26 character in English alphabet
const char ASCII_a = 'a';

class SuffTreeNode;

class SuffTreeEdge {
public:
    SuffTreeEdge(){};
    
    SuffTreeNode* from;
    SuffTreeNode* to;
    
    int startPos;
    int endPos;
    
    char firstCh;
};

class SuffTreeNode {
public:
    SuffTreeNode();
    
    SuffTreeEdge edges[CHAR_LIMIT];
    SuffTreeEdge parrent;
    SuffTreeNode* suffLink;
};

class SuffTreePosition {
public:
    SuffTreeEdge edge;   
    int offset;
};

class SuffTree {
public:
    SuffTree();
    virtual ~SuffTree();
    void add(char ch);
    void add(const string& str);
    void destroyNode( SuffTreeNode* node );
    
private:
    SuffTreeNode* root;
    SuffTreeNode* blank; //!< wtf !? - FIXME!
    string str;
    
    SuffTreePosition curr;
    SuffTreeNode* splitEdge( SuffTreePosition pos );
    SuffTreePosition getSuffix( const SuffTreePosition& pos );
};

SuffTreeNode::SuffTreeNode() {
    for( int n=0; n < CHAR_LIMIT; ++n ) {
        edges[n].from = this;
        edges[n].to = NULL;
        edges[n].startPos = -1; 
        edges[n].endPos = 0;
        edges[n].firstCh = n + ASCII_a;
    }
}

SuffTree::~SuffTree() {
    delete blank;
    destroyNode( root );
}

SuffTree::SuffTree() {

    root = new SuffTreeNode;
    blank = new SuffTreeNode;
    blank->suffLink    = NULL;  
    blank->edges[0].to = blank;
    blank->parrent     = blank->edges[0];
    for( int i=1; i<CHAR_LIMIT; ++i) {
        blank->edges[i].to = root;
    }
    
    root->parrent  = blank->edges[1];
    root->suffLink = blank;
    
    curr.edge   =  blank->edges[1];
    curr.offset = 0;
}

void SuffTree::add( char ch ) {
    char chIt = ch - ASCII_a;
    if( curr.edge.endPos == curr.offset ) {
        if(curr.edge.to->edges[chIt].to == NULL ) {
            curr.edge.to->edges[chIt].to = new SuffTreeNode;
            curr.edge.to->edges[chIt].firstCh  = ch;
            curr.edge.to->edges[chIt].startPos = str.size();
            curr.edge.to->edges[chIt].endPos   = INT_MAX;
            
            if( curr.edge.from == blank) {
                str.push_back(ch);
                return;
            }
            curr = getSuffix(curr);
        }
        curr.edge = curr.edge.to->edges[chIt];
        curr.offset = curr.edge.startPos + 1;
    }
    else {
        if( str.at( curr.offset ) == ch ) {
            ++curr.offset;
        }
        else {
            SuffTreeNode* newNode = splitEdge(curr);
            curr.edge = newNode->parrent;
            add(ch);
            return;
        }
    }
    str.push_back(ch);
}

SuffTreePosition SuffTree::getSuffix( const SuffTreePosition& pos ) {
    SuffTreeNode* curr = pos.edge.from->suffLink;
    if( curr == NULL ) {
        // root
        return pos;
    }
    int currOffset = pos.edge.startPos;
    SuffTreePosition res;
    
    // go down by tree, one iteration is down by one edge
    SuffTreeEdge currEdge = curr->edges[ str.at(currOffset) ];
    while( currOffset < pos.offset ) {
        currEdge = curr->edges[ str.at(currOffset) ];
        currOffset += currEdge.endPos - currEdge.startPos;
        curr = currEdge.to;
    }
    
    res.edge = currEdge;
    res.offset = pos.offset - currOffset + currEdge.endPos - currEdge.startPos + currEdge.startPos;
    return res;
}

SuffTreeNode* SuffTree::splitEdge( SuffTreePosition pos ) {
    if( pos.edge.endPos == pos.offset ) {
        // Это означает что делить и не надо, наша вершина это лист... просто возвращаем
        // указатель на него
        return pos.edge.to;
    }
    SuffTreeNode* newNode = new SuffTreeNode;
    SuffTreeEdge  newEdge;
    
    newEdge.startPos = pos.offset;
    newEdge.endPos   = pos.edge.endPos;
    newEdge.firstCh  = str.at(pos.offset);
    newEdge.from     = newNode;
    newEdge.to       = pos.edge.to;
    
    newNode->edges[str.at(pos.offset)] = newEdge;
    
    pos.edge.endPos = pos.offset;
    pos.edge.to = newNode;
    newNode->parrent = pos.edge;
    pos.edge.from->edges[pos.edge.firstCh] = pos.edge;

    newNode->suffLink = splitEdge(getSuffix(pos));
    return newNode;
}

void SuffTree::destroyNode( SuffTreeNode* node ) {
    if( node != NULL ) {
        for( int t = 0; t < CHAR_LIMIT; ++t ) {
            destroyNode( node->edges[t].to );
        }
        delete node;
    }
}

int main( int argN, char** argS ) {
    int inNum = 0;
    
    SuffTree tree;
    
    char ch = std::cin.get();
    while ( ch != '\n' ) {
        tree.add(ch);
        ch = std::cin.get();
    }
    return 0;
}
