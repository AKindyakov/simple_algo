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
    //os << string(lvl*4, ' ') << "-";
    for( EdgeContainer::iterator it = edges.begin();
            it != edges.end(); ++it ) {
        it->second.showMe(str, lvl+1, os);
    }
}

void SuffTreeEdge::showMe( const string& str, int lvl, std::ostream& os ) {
    if( endPos == INT_MAX ) {
        endPos = str.size();
    }
    int len = endPos - startPos;
    os << string(lvl*4, ' ') << "| " 
       << str.substr(startPos, len) << '\n';
    if( to != NULL ) {
        to->showMe(str, lvl+1, os);
        os << '\n';
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
        root( new SuffTreeNode )    {
    blank->addEdge('a', root, 0, 0);
    root->parrent = blank->firstEdge();
}

void SuffTree::add( char ch ) {
    /**/ std::cout << "ch : " << ch << '\n';
    cursors.push_back( SuffTreeCursor(blank->firstEdge(), 0));
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( trackTheCursor( ch, &*cIt ) ) {
            list<SuffTreeCursor>::iterator delIt = cIt--;
            cursors.erase(delIt);
        }
    }
    str.push_back(ch);
    showMe(std::cout);
}

bool SuffTree::trackTheCursor(char ch, SuffTreeCursor* cursor ) {
    // Will you take red or blue pill ?
    // At the end of way?
    //**/ std::cout << "ch : " << ch << '\n';
    if( cursor->edge->endPos == cursor->cursor ) {
        EdgeContainer::iterator find = cursor->edge->to->findEdge(ch);
        if( find == cursor->edge->to->emptyEdge() ) {
            //**/ std::cout << "\tadd\n";
            cursor->edge->to->addEdge( ch, NULL, str.size(), INT_MAX ); 
            return true;
        }
        else {
            //**/ std::cout << "\twas found: " << ch << '\n';
            cursor->edge = &find->second;
            cursor->cursor = 0;
            return false;
        }
    }
    else {
        //**/ std::cout << "\tat : " << cursor->cursor << '\t'
        //**/           << str.size() << '\n';
        /**/ std::cout << '\t' 
        /**/           << str.at(cursor->edge->startPos+cursor->cursor) 
        /**/           << ch << '\n';
        if( str.at(cursor->edge->startPos + cursor->cursor) == ch ) {
            ++cursor->cursor;
            /**/ std::cout << "+: " << cursor->cursor << '\n'; 
            return false;
        }
        else {
            /**/ std::cout << "1: " << cursor->cursor << '\n'; 
            SuffTreeNode* nNode = new SuffTreeNode;
            
            nNode->addEdge( ch, NULL, str.size(), INT_MAX );
            
            nNode->addEdge( str.at(cursor->edge->startPos + cursor->cursor), 
                            cursor->edge->to, 
                            cursor->edge->startPos + cursor->cursor,
                            cursor->edge->endPos );
            
            nNode->parrent = cursor->edge;
            cursor->edge->to = nNode;
            cursor->edge->endPos = cursor->edge->startPos + cursor->cursor - 1;
            /**/ std::cout << "2: " << cursor->cursor << '\n'; 
            //cursor->edge->endPos = cursor->edge->startPos + 1;
            return true;
        }
    }
}

SuffTreeNode* SuffTree::splitEdge( SuffTreeCursor pos ) {
    /*if( pos.edge.endPos == pos.offset ) {
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
    return newNode; */
    return new SuffTreeNode;
}

void SuffTree::showMe( std::ostream& os ) {
    os << "Print tree:\n";
    blank->showMe(str, 0, os);
}
