#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <climits>

#include "tree.h"

#include "../SimpleAlgoException/simpleException.h"

SuffTreeNode::SuffTreeNode() {
    for( int eg = 0; eg < ABC_SIZE; ++eg ) {
        edges[eg] = NULL;
    }
}

int SuffTreeNode::greatestSubstring( int lvl, list<SubString>* outSub ) {
    int maxLen = 0;
    list<SubString> maxSub;
    for( int i = 0; i < ABC_SIZE; ++i ) {
        SuffTreeEdge* pt = edges[i];
        if( pt != NULL && pt->prevGuest == lvl ) {
            list<SubString> lSub;
            int lLen = 0;
            lLen += pt->to->greatestSubstring(lvl, &lSub);
            lLen += pt->sub.endPos - pt->sub.startPos;
            lSub.push_front(pt->sub);
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
    for( int i = 0; i < ABC_SIZE; ++i ) {
        if( edges[i] != NULL ) {
            edges[i]->showMe(str, lvl+1, os);
        }
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

void SuffTreeNode::addEdge( char ch, SuffTreeNode* to, int start, int end, int strCount ) {
    ch -= FIRST_ABC_CHAR;
    //if( ch >= ABC_SIZE ) {
    //    throw SimpleException("Wrong input character", __LINE__); 
    //}
    edges[ ch ] = new SuffTreeEdge(this, to, start, end, strCount);
}

SuffTreeEdge* SuffTreeNode::findEdge( char ch ) {
    ch -= FIRST_ABC_CHAR;
    //if( ch >= ABC_SIZE ) {
    //    throw SimpleException("Wrong input character", __LINE__); 
    //}
    return edges[ch];
}

void SuffTreeNode::finish( const string& str ) {
    for( int i = 0; i < ABC_SIZE; ++i ) {
        if( edges[i] != NULL ) {
            edges[i]->finish( str );
        }
    }
}

SuffTree::~SuffTree() {
    // dont forget to destroing }=/  @>-`-,-
}

SuffTree::SuffTree()
    :   blank( new SuffTreeNode ),
        root( new SuffTreeNode ),
        strCount( 0 ) {
    blank->addEdge(FIRST_ABC_CHAR, root, 0, 0, 0);
    root->parrent = blank->findEdge(FIRST_ABC_CHAR);
}

void SuffTree::add( char ch ) {
    //**/ std::cout << "ch : " << ch << ' ' << blank->findEdge(FIRST_ABC_CHAR) << '\n';
    cursors.push_back( SuffTreeCursor(blank->findEdge(FIRST_ABC_CHAR), 0));
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( trackTheCursor( ch, &*cIt ) ) {
            list<SuffTreeCursor>::iterator delIt = cIt--;
            cursors.erase(delIt);
        }
    }
    str.push_back(ch);
}

bool SuffTree::trackTheCursor(char ch, SuffTreeCursor* cursor ) {
    // Will you take red or blue pill ?
    // At the end of way?
    //**/ std::cout << "ch : " << ch << '\n';
    if( cursor->edge->sub.endPos == cursor->cursor+cursor->edge->sub.startPos ) {
        SuffTreeEdge* find = cursor->edge->to->findEdge(ch);
        if( find == NULL ) {
            //**/ std::cout << "\tadd\n";
            cursor->edge->to->addEdge( ch, NULL, str.size(), INT_MAX, 0 ); 
        }
        else {
            //**/ std::cout << "\twas found: " << ch << '\n';
            cursor->edge = find;
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
            
            nNode->addEdge( ch, NULL, str.size(), INT_MAX, 0 );
            
            nNode->addEdge( str.at(cursor->edge->sub.startPos + cursor->cursor), 
                            cursor->edge->to, 
                            cursor->edge->sub.startPos + cursor->cursor,
                            cursor->edge->sub.endPos, 0 );
            
            nNode->parrent = cursor->edge;
            cursor->edge->to = nNode;
            cursor->edge->sub.endPos = cursor->edge->sub.startPos + cursor->cursor;
        }
    }
    return true;
}

void SuffTree::check( char ch ) {
    //**/ std::cout << "check : " << cursors.size() << '\n';
    cursors.push_back( SuffTreeCursor(blank->findEdge(FIRST_ABC_CHAR), 0));
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( checkTrackTheCursor( ch, &*cIt ) ) {
            list<SuffTreeCursor>::iterator delIt = cIt--;
            cursors.erase(delIt);
        }
    }
    //**/ showMe(std::cout);
}

bool SuffTree::checkTrackTheCursor(char ch, SuffTreeCursor* cursor ) {
    //**/ std::cout << "\t-> " << ch << '\n';
    if( cursor->edge->sub.endPos == cursor->cursor+cursor->edge->sub.startPos ) {
        //**/ std::cout << "\tEnd of edge " << ch << '\n';
        SuffTreeEdge* find = cursor->edge->to->findEdge(ch);
        if( find != NULL ) {
            //**/ std::cout << "\twas found: " << ch << '\n';
            cursor->edge->prevGuest = strCount;
            if( find->prevGuest == strCount 
                || find->prevGuest == strCount-1 ) {
                //**/ std::cout << "go to: " << ch << "  increment\n";
                cursor->edge = find;
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
                            cIt->edge->sub.endPos, 
                            cIt->edge->prevGuest );
            nNode->parrent = cIt->edge;
            cIt->edge->to = nNode;
            cIt->edge->sub.endPos = cIt->edge->sub.startPos + cIt->cursor;
        }
        cIt->edge->prevGuest = strCount;
    }
    cursors.clear();
    ++strCount;
}

std::string SuffTree::getGreatSubstring()const {
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
