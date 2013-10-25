    #include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>

#include "tree.h"

SuffTreeEdge::SuffTreeEdge()
        :   from(NULL), to(NULL), startPos(-1), endPos(-1), counter(0) {}
    
SuffTreeEdge::SuffTreeEdge( SuffTreeNode* _from, SuffTreeNode* _to, int start, int end )
        :   from(_from), to(_to), startPos(start), endPos(end), counter(0) {}

SuffTreeNode::SuffTreeNode()
    :   parrent (NULL) {
    edges.clear();
}

SuffTreeNode::~SuffTreeNode() {
}

void SuffTreeNode::showMe( const string& str, int lvl, std::ostream& os ) {
    //os << string(lvl*4, ' ') << "-";
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
        os << '\n';
    }
}

SuffTreeEdge::~SuffTreeEdge() {
    if( to != NULL ) {
        delete to;
    }
}

void SuffTreeNode::addEdge( char ch, SuffTreeNode* to, int start, int end ) {
    std::cout << "Burn the heretik!\n";
    std::cout << "Kill the mutant!\n";
    //edges.insert(std::pair<char, SuffTreeEdge>(ch, SuffTreeEdge() ) );
    std::cout << ch << ' ' << edges.size() << '\n';
    //edges.insert(EdgeValue(ch, SuffTreeEdge(this, to, start, end)));
    edges[ch] = SuffTreeEdge(this, to, start, end);
    std::cout << "Purge the unclean!\n";
    std::cout << ch << ' ' << edges.size() << '\n';
}

SuffTree::~SuffTree() {
    // dont forget to destroing }=/  @>-`-,-
}

SuffTree::SuffTree()
    :   blank( new SuffTreeNode ),
        root( new SuffTreeNode ),
        strCount( 0 )  {
    blank->addEdge('a', root, 0, 0);
    root->parrent = &blank->edges['a'];
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
    //**/ for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
    //**/         cIt != cursors.end(); ++cIt ) { 
    //**/     std::cout << cIt->edge << ' ' << cIt->cursor << '\n';
    //**/ }
    str.push_back(ch);
    //**/ showMe(std::cout);
}

//bool SuffTree::trackTheCursor(char ch, SuffTreeCursor* cursor ) {
//    // Will you take red or blue pill ?
//    // At the end of way?
//    //**/ std::cout << "ch : " << ch << '\n';
//    if( cursor->edge->endPos == cursor->cursor ) {
//        EdgeContainer::iterator find = cursor->edge->to->findEdge(ch);
//        if( find == cursor->edge->to->emptyEdge() ) {
//            //**/ std::cout << "\tadd\n";
//            cursor->edge->to->addEdge( ch, NULL, str.size(), INT_MAX ); 
//            return true;
//        }
//        else {
//            //**/ std::cout << "\twas found: " << ch << '\n';
//            cursor->edge = &find->second;
//            cursor->cursor = 1;
//            return false;
//        }
//    }
//    else {
//        //**/ std::cout << "\tat : " << cursor->cursor << '\t'
//        //**/           << str.size() << '\n';
//        //**/ std::cout << "\tCompare: " 
//        //**/           << str.at(cursor->edge->startPos+cursor->cursor) 
//        //**/           << " - " << ch << '\n';
//        if( str.at(cursor->edge->startPos + cursor->cursor) == ch ) {
//            ++cursor->cursor;
//            //**/ std::cout << "+: " << cursor->cursor << '\n'; 
//            return false;
//        }
//        else {
//            //**/ std::cout << "cursor " << cursor->cursor << '\n'; 
//            SuffTreeNode* nNode = new SuffTreeNode;
//            
//            nNode->addEdge( ch, NULL, str.size(), INT_MAX );
//            
//            nNode->addEdge( str.at(cursor->edge->startPos + cursor->cursor), 
//                            cursor->edge->to, 
//                            cursor->edge->startPos + cursor->cursor,
//                            cursor->edge->endPos );
//            
//            nNode->parrent = cursor->edge;
//            cursor->edge->to = nNode;
//            cursor->edge->endPos = cursor->edge->startPos + cursor->cursor;
//            return true;
//        }
//    }
//} 

bool SuffTree::trackTheCursor(char ch, SuffTreeCursor* cursor ) {
    // Will you take red or blue pill ?
    // At the end of way?
    //**/ std::cout << "ch : " << ch << '\n';
    if( cursor->edge->endPos == cursor->cursor ) {
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
   //         cursor->edge->counter = strCount+1;
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
        std::cout << (cursor->edge->startPos + cursor->cursor) == ch ) {
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
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( cIt->edge->endPos != cIt->cursor ) { // At the middle of edge
            SuffTreeNode* nNode = new SuffTreeNode;
            nNode->addEdge( str.at(cIt->edge->startPos + cIt->cursor), 
                            cIt->edge->to, 
                            cIt->edge->startPos + cIt->cursor,
                            cIt->edge->endPos );
            
            nNode->parrent = cIt->edge;
        }
    }
    cursors.clear();
    ++strCount;
}

std::string SuffTree::getGreatSustring() {
    return string();
}

void SuffTree::showMe( std::ostream& os ) {
    os << "Print tree:\n";
    blank->showMe(str, 0, os);
}
