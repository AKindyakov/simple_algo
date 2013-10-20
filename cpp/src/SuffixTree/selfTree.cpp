#include <iostream>
#include <string>
#include <climits>

using std::string;

const char FIRST_CHAR = 'a';
const int  ALPHABETIC_SIZE = 26;

class SuffixNode;

class SuffixEdge {
public:
    SuffixEdge() {}
    void showMe( const string& str, std::ostream& os );
    
    SuffixNode* to;
    SuffixNode* from;
    int start;
    int end;
};

class SuffixNode {
public:
    SuffixNode() {
        for( int n=0; n < ALPHABETIC_SIZE; ++n ) {
            edges[n].from = this;
            edges[n].to   = NULL;
            edges[n].start = 0;
            edges[n].end   = 0;
        }
    }
    
    void showMe( const string& str, std::ostream& os ) {
        for( int n=0; n < ALPHABETIC_SIZE; ++n ) {
            edges[n].showMe(str, os);
        }
    }

    SuffixEdge edges[ALPHABETIC_SIZE];
    SuffixEdge* parrentEdge;
    SuffixNode* link;
};

void SuffixEdge::showMe( const string& str, std::ostream& os ) {
    if( end != start ) {
        int len = end;
        if( len == INT_MAX ) {
            len = str.size();
        }
        len -= start;
        os << str.substr(start, len) << '\n';
        if( to != NULL ) {
            to->showMe(str, os);
        }
    }
}

class SuffixTree {
public:
    SuffixTree() {
        root = new SuffixNode;
        blank = new SuffixNode;
        blank->edges[0].to = root;
        state.edge = blank->edges;
        state.cursor = 0;
    }
    
    void add(char ch) {
        int chIt = ch - FIRST_CHAR;
        
        //!> Если дошли до конца ребра
        if( state.edge->end == state.cursor ) {
            SuffixNode* nPt = state.edge->to;
            if( nPt->edges[chIt].to == NULL ) {
                nPt->edges[chIt].to = new SuffixNode;
                nPt->edges[chIt].from = nPt;
                nPt->edges[chIt].start = str.size();
                nPt->edges[chIt].end = INT_MAX;
            }
            else {
                state.edge = (nPt->edges + chIt);
                state.cursor = state.edge->start+1;
            }
        }
        else {
            //!> Еще на ребре
            
            // Входящий символ совпадает со следующим в ребре
            if( str.at(state.cursor) == ch ) {
                ++state.cursor;
            }
            else {
                SuffixTreeNode* nNode = splitEdge();
            }
        }
        str.push_back(ch);
    }
    
    void showMe( std::ostream& os ) {
        os << "begin:\n";
        root->showMe(str, os);
    }

private:
    SuffixNode* blank;
    SuffixNode* root;
    string str;

    struct SuffixCursor {
        SuffixEdge* edge;
        
        // Смещение относительно начала строки 
        // и принадлежащее подстроке ребра на
        // который указывает state
        int cursor;
    };
    SuffixCursor state;
};


int main( int argN, char** argS ) {
    
    SuffixTree tree;
    
    char ch = std::cin.get();
    while ( ch != '\n' ) {
        tree.add(ch);    
        ch = std::cin.get();
    }
    tree.showMe(std::cout);
    return 0;
}

