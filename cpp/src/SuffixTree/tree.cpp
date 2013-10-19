#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

using std::list;
using std::vector;
using std::string;

const int CHAR_LIMIT = 26; // only 26 character in English alphabet
const char ASCII_a = 'a';

class SufTreeNode;

class SufTreeEdge {
public:
    SufTreeEdge();
    
private:
    SufTreeNode* from;
    SufTreeNode* to;
    
    int startPos;
    int endPos;
    
    char firstCh;
};

class SufTreeNode {
public:
    SufTreeNode();
private:
    SufTreeEdge edges[CHAR_LIMIT];
    SufTreeEdge parrent;
    SufTreeNode* suffLink;
};

class SufTreePosition {
public:
    SufTreeEdge edge;   
    int offset;
};

class SufTree {
public:
    SufTree();
    virtual ~SufTree();
    void add(char ch);
    void add(const string& str);
    
private:
    SuffTreeNode* root;
    SuffTreeNode* joker; //!< wtf !? - FIXME!
    string str;
    
    SufTreePosition curr;
    SufTreePosition getSuffix( const SuffTreePosition& pos );
};

SufTreeNode::SuffTreeNode() {
    for( int n=0; n < CHAR_LIMIT; ++n ) {
        edges[n].from = this;
        edges[n].to = NULL;
        edges[n].startPos = -1; 
        edges[n].endPos = 0;
        edges[n].first = i + ASCII_a;
    }
}

SufTree::SufTree() {

    root = new SufTreeNode;
    joker = new SufTreeNode;
    joker->suffLink = NULL;  
    joker->edges[0].to = joker;
    joker->parrent = joker->edges[0];
    for( int i=1; i<CHAR_LIMIT; ++i) {
        joker->edges[i].to = root;
    }
    
    root->parrent = joker->edges[1];
    root->suffLink = joker;
    cur.edge =  joker->edges[1];
    cur.offset = 0;
}


int main( int argN, char** argS ) {
    int inNum = 0;
    std::cin >> inNum;
    std::cin.ignore();
    std::vector<std::string> inString;
    
    for( int in = 0; in < inNum; ++in ) {
        inString.push_back(getLongLine(std::cin));
    }
    return 0;
}
