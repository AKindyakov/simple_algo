#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <climits>

#include "tree.h"

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
            if( it->second.to != NULL ) {   
                lLen += it->second.to->greatestSubstring(lvl, &lSub);
            }
            lLen += it->second.sub.endPos - it->second.sub.startPos;
            lSub.push_front(it->second.sub);
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

void SuffTreeNode::showMe( const string& str, int lvl, std::ostream& os ) {
    std::cout << "SuffTreeNode::showMe\n";
    for( EdgeContainer::iterator it = edges.begin();
            it != edges.end(); ++it ) {
        std::cout << it->first << "\n";
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
}

void SuffTreeEdge::showMe( const string& str, int lvl, std::ostream& os ) {
    int len = sub.endPos;
    if( sub.endPos == INT_MAX ) {
        len = str.size();
    }
    len -= sub.startPos;
    os << string(lvl*4, ' ') << "| " << prevGuest << ' ' << sub.startPos << ' ' << sub.endPos
       << ' ' << str.substr(sub.startPos, len) << '\n';
    if( to != NULL ) {
        to->showMe(str, lvl+1, os);
    }
}

void SuffTreeNode::addEdge( char ch, SuffTreeNode* to, int start, int end ) {
    edges.insert( EdgeValue(ch, SuffTreeEdge(this, to, start, end) ) );
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
            return true;
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
            return true;
        }
    }
    return true;
}

void SuffTree::check( char ch ) {
    //**/ std::cout << "ch : " << ch << '\n';
    cursors.push_back( SuffTreeCursor(blank->firstEdge(), 0));
    for( list<SuffTreeCursor>::iterator cIt = cursors.begin();
            cIt != cursors.end(); ++cIt ) { 
        if( checkTrackTheCursor( ch, &*cIt ) ) {
            list<SuffTreeCursor>::iterator delIt = cIt--;
            cursors.erase(delIt);
        }
    }
}

bool SuffTree::checkTrackTheCursor(char ch, SuffTreeCursor* cursor ) {
    //**/ std::cout << "\t-> " << ch << '\n';
    if( cursor->edge->sub.endPos == cursor->cursor+cursor->edge->sub.startPos ) {
        //**/ std::cout << "\tEnd of edge " << ch << '\n';
        EdgeContainer::iterator find = cursor->edge->to->findEdge(ch);
        if( find != cursor->edge->to->emptyEdge() ) {
            //**/ std::cout << "\twas found: " << ch << '\n';
            if( find->second.prevGuest == strCount 
                || find->second.prevGuest == strCount-1 ) {
                //**/ std::cout << "increment\n";
                cursor->edge = &find->second;
                cursor->edge->prevGuest = strCount;
                cursor->cursor = 1;
                return false;
            }
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
                            cursor->edge->sub.endPos );
            
            nNode->parrent = cursor->edge;
            cursor->edge->to = nNode;
            cursor->edge->sub.endPos = cursor->edge->sub.startPos + cursor->cursor;
        }
    }
    return true;
}

void SuffTree::finishTree() {
    blank->finish(str);
}

void SuffTree::endString() {
    ++strCount;
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
        
    }
    cursors.clear();
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

void SuffTree::showMe( std::ostream& os ) {
    blank->showMe(str, 0, os);
}
