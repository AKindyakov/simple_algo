#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>

#include "tree.h"

SuffTreeNode::SuffTreeNode() {
}

void SuffTreeNode::showMe( const string& str, int lvl, std::ostream& os ) {
    for( EdgeContainer::iterator it = edges.begin();
            it != edges.end(); ++it ) {
        it->second.showMe(str, lvl+1, os);
    }
}

void SuffTreeEdge::showMe( const string& str, int lvl, std::ostream& os ) {
    int len = endPos;
    if( endPos == INT_MAX ) {
        len = str.size();
    }
    len -= startPos;
    os << string(lvl*4, ' ') << "| " 
       << str.substr(startPos, len) << '\n';
    if( to != NULL ) {
        to->showMe(str, lvl+1, os);
        //os << "|\n";
    }
}

void SuffTreeNode::addEdge( char ch, SuffTreeNode* to, int start, int end ) {
    edges.insert( EdgeValue(ch, SuffTreeEdge(this, to, start, end) ) );
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
    //**/ std::cout << "--------------------------------------------------------------------\n";
    //**/ for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
    //**/         cIt != cursors.end(); ++cIt ) { 
    //**/     std::cout << cIt->edge << ' ' << cIt->cursor << '\n';
    //**/ }
    
    str.push_back(ch);
    //**/ showMe(std::cout);
}

bool SuffTree::trackTheCursor(char ch, SuffTreeCursor* cursor ) {
    // Will you take red or blue pill ?
    // At the end of way?
    //**/ std::cout << "ch : " << ch << '\n';
    if( cursor->edge->endPos == cursor->cursor+cursor->edge->startPos ) {
        EdgeContainer::iterator find = cursor->edge->to->findEdge(ch);
        if( find == cursor->edge->to->emptyEdge() ) {
            //**/ std::cout << "\tadd\n";
            if( strCount == 0 ) {
                cursor->edge->to->addEdge( ch, NULL, str.size(), INT_MAX ); 
            }
            return true;
        }
        else {
            //**/ std::cout << "\twas found: " << ch << '\n';
            cursor->edge = &find->second;
            cursor->edge->count = strCount + 1;
            cursor->cursor = 1;
            return false;
        }
    }
    else {
        //**/ std::cout << "\tat : " << cursor->cursor << '\t'
        //**/           << str.size() << '\n';
        //**/ std::cout << "\tCompare: " 
        //**/           << str.at(cursor->edge->startPos+cursor->cursor) 
        //**/           << " - " << ch << '\n';
        if( str.at(cursor->edge->startPos + cursor->cursor) == ch ) {
            ++cursor->cursor;
            //**/ std::cout << "+: " << cursor->cursor << '\n'; 
            return false;
        }
        else {
            //**/ std::cout << "cursor " << cursor->cursor << '\n'; 
            SuffTreeNode* nNode = new SuffTreeNode;
            
            nNode->addEdge( ch, NULL, str.size(), INT_MAX );
            
            nNode->addEdge( str.at(cursor->edge->startPos + cursor->cursor), 
                            cursor->edge->to, 
                            cursor->edge->startPos + cursor->cursor,
                            cursor->edge->endPos );
            
            nNode->parrent = cursor->edge;
            cursor->edge->to = nNode;
            cursor->edge->endPos = cursor->edge->startPos + cursor->cursor;
            return true;
        }
    }
}

void SuffTree::endString() {
    ++strCount;
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( cIt->cursor != cIt->edge->startPos-cIt->edge->endPos ) {
            SuffTreeNode* nNode = new SuffTreeNode;
            nNode->addEdge( str.at(cIt->edge->startPos + cIt->cursor), 
                            cIt->edge->to, 
                            cIt->edge->startPos + cIt->cursor,
                            cIt->edge->endPos );
            nNode->parrent = cIt->edge;
        }
        
    }
    cursors.clear();
}

std::string SuffTree::getGreatSubstring() {
    return std::string("Cowards die in shame");
}
void SuffTree::showMe( std::ostream& os ) {
    blank->showMe(str, 0, os);
}
