#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>

#include "tree.h"

SuffTreeNode::SuffTreeNode() {
}

void SuffTreeNode::addEdge( char ch, SuffTreeNode* to, int start, int end ) {
    edges.insert( EdgeValue(ch, SuffTreeEdge(this, to, start, end) ) );
}

SuffTree::~SuffTree() {
    // dont forget to destroing }=/  @>-`,-
}

SuffTree::SuffTree()
    :   blank( new SuffTreeNode ),
        root( new SuffTreeNode )    {
    blank->addEdge('a', root, 0, 0);
    root->parrent = blank->firstEdge();
    
    cursor.edge = blank->firstEdge();
    cursor.cursor = 0;
}

void SuffTree::add( char ch ) {
    // Will you take red or blue pill ?
    
    // At the end of way?
    if( cursor.edge->endPos == cursor.cursor ) {
        EdgeContainer::iterator find = cursor.edge->to->findEdge(ch);
        
        if( find == cursor.edge->to->emptyEdge() ) {
            cursor.edge->to->addEdge( ch, NULL, str.size(), INT_MAX ); 
        }
    }
    else {
        if( str.at( cursor.cursor ) == ch ) {
        }
        else {
        }
    }
    str.push_back(ch);
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

