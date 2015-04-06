#include "tree.h"


namespace NSufixTree {

TEdge* TEdge::split(size_t cursor) {
    if (!subString.positionIsValid(cursor)) {
        throw TSimpleException()
            << "invalid position for split"
            << "; start: " << subString.start
            << "; cur: " << cursor
            << "; end: " << subString.end
        ;
    }

    TSubstring downPart(subString);
    downPart.start = downPart.start + cursor;
    subString.end = subString.start + cursor;

    //*dbg*/ std::cerr << "split through cur: " << cursor << std::endl;
    //*dbg*/ std::cerr << "up interval: "
    //*dbg*/     << "; start: " << subString.start
    //*dbg*/     << "; end: " << subString.end
    //*dbg*/     << std::endl
    //*dbg*/ ;
    //*dbg*/ std::cerr << "down interval: "
    //*dbg*/     << "; start: " << downPart.start
    //*dbg*/     << "; end: " << downPart.end
    //*dbg*/     << std::endl
    //*dbg*/ ;

    std::unique_ptr<TNode> newNode(new TNode(this));
    newNode->addEdge(downPart);
    newNode->get(downPart.head())->endNode.swap(endNode);
    endNode.swap(newNode);
    return endNode->get(downPart.head());
}

void TTreeBase::ukkonenRebuildTree() {
    for (size_t i = 0; i < text.size(); ++i) {
        //*dbg*/ std::cerr << "ukkonenPush i: " << i << " ch: " << text[i] << "\n";
        ukkonenPush(i);
        //*dbg*/ std::cerr << "\n";
        // show(std::cerr);
        //*dbg*/ std::cerr << "----------------------------------------------\n\n";
    }
    rootEdge.endNode->suffixLink = rootEdge.endNode.get();
}

void TTreeBase::ukkonenPush(size_t position) {
    cursors.emplace_back(TTreeCursor(&rootEdge));
    TNode* nodeForLink = nullptr;

    //*dbg*/ size_t counter = 0;
    for (auto& cursor : cursors) {
        if (cursor.deleted) {
            //*dbg*/ std::cerr << counter++ << ": skip deleted cursor\n";
            continue;
        }
        //*dbg*/ else {
        //*dbg*/     std::cerr << counter++ << ": cursor: \n";
        //*dbg*/ }
        int stepType = cursor.step(position);
        //*dbg*/ std::cerr << "step: " << stepType << "\n\n";

        if (stepType > 1) {
            TNode* currentNode = cursor.edge->parentNode;
            if (nodeForLink != nullptr && nodeForLink->suffixLink == nullptr) {
                //*dbg*/ std::cerr << "link\n";
                nodeForLink->suffixLink = currentNode;
            }
            nodeForLink = currentNode;
        }
        if (stepType == 2) {
            cursor.deleted = true;
        }
    }
}

int TTreeCursor::step(size_t position) {
    //*dbg*/ std::cerr << "step(\n"
    //*dbg*/     << "  pos: " << position << " -> '" << edge->subString.str.at(position) << "'\n"
    //*dbg*/     << "  cur: " << cursor   << "'\n"
    //*dbg*/     << "  sub: " << edge->subString.copy() << "\n"
    //*dbg*/     << ")" << std::endl
    //*dbg*/ ;

    if (cursor > edge->subString.size()) {
        //*dbg/ std::cerr << "respawn ("
        //*dbg/     << "\n  cursor: " << cursor
        //*dbg/     << "\n  size: " << edge->subString.size()
        //*dbg/     << "\n  sub: " << edge->subString.copy()
        //*dbg/     << "\n)" << std::endl
        //*dbg/ ;
        cursor = cursor - edge->subString.size();
        char prevEndChar = edge->subString.str[edge->subString.end];
        edge = edge->endNode->get(prevEndChar);
    }

    int stepType = 0;
    if (edge->subString.positionIsValid(cursor)) {
        //*dbg*/ std::cerr << "position is valid" << std::endl;
        if (edge->subString.at(cursor) == edge->subString.str[position]) {
            //! just follow
            //*dbg*/ std::cerr << "just follow" << std::endl;
            stepType = 1;
        } else {
            //*dbg*/ std::cerr << "split" << std::endl;
            edge->split(cursor);
            edge = edge->endNode->addEdge(TSubstring(edge->subString.str, position));
            stepType = 2;
            cursor = 0;
        }
    } else {
        if (edge->endNode == nullptr) {
            //! create node at the end
            //*dbg*/ std::cerr << "create end node" << std::endl;
            edge->endNode.reset(
                new TNode(edge)
            );
        }
        char ch = edge->subString.str[position];
        if (edge->endNode->has(ch)) {
            edge = edge->endNode->get(ch);
            //*dbg*/ std::cerr << "Yes! Third type" << std::endl;
            stepType = 3; // Yes! Third type of step
            cursor = 0;
        } else {
            //*dbg*/ std::cerr << "Add edge to node (" << edge->subString.copy() << ")\n";
            edge->endNode->addEdge(
                TSubstring(edge->subString.str, position)
            );
            edge = edge->endNode->get(ch);
            stepType = 2;
            cursor = 0;
        }
    }
    ++cursor;
    return stepType;
}

void TEdge::show(size_t lvl, std::ostream& os) const {
    size_t end = subString.end;
    if (end > subString.str.size()) {
        end = subString.str.size();
    }
    os << '[' << subString.start << ':' << end << "] " << subString.copy() << "\n";
    //*dbg*/ std::cerr << "edge show\n";
    if (endNode != nullptr) {
        endNode->show(lvl + 1, os);
    }
    //*dbg*/ std::cerr << "edge show end\n";
}

void TNode::show(size_t lvl, std::ostream& os) const {
    //*dbg*/ std::cerr << "node show\n";
    ++lvl;

    // os << " ----> " << (suffixLink == nullptr) << "\n";
    os << std::string(lvl, ' ') << "---> " << suffixLink->parent->subString.copy() << "\n";
    for (size_t i = 0; i < edges.size(); ++i) {
        if (nullptr != edges[i]) {
            os  << std::string(lvl, ' ')
                << "-("
                << static_cast<char>(FIRST_ABC_CHAR + i)
                << "): "
            ;
            edges[i]->show(lvl, os);
        }
    }
}

void TTreeBase::show(std::ostream& os) const {
    rootEdge.show(0, os);
}

}

