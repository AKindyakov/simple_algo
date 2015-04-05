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

    std::cerr << "split through cur: " << cursor << std::endl;
    std::cerr << "up interval: "
        << "; start: " << subString.start
        << "; end: " << subString.end
        << std::endl
    ;
    std::cerr << "down interval: "
        << "; start: " << downPart.start
        << "; end: " << downPart.end
        << std::endl
    ;

    std::unique_ptr<TNode> newNode(new TNode(this));
    newNode->addEdge(downPart);
    newNode->get(downPart.head())->endNode.swap(endNode);
    endNode.swap(newNode);
    return endNode->get(downPart.head());
}

void TTreeBase::ukkonenRebuildTree() {
    for (size_t i = 0; i < text.size(); ++i) {
        std::cerr << "ukkonenPush i: " << i << " ch: " << text[i] << "\n";
        ukkonenPush(i);
        std::cerr << "\n";
        show(std::cerr);
        std::cerr << "----------------------------------------------\n\n";
    }
}

void TTreeBase::ukkonenPush(size_t position) {
    cursors.emplace_back(TTreeCursor(&rootEdge));
    TNode* nodeForLink = nullptr;

    size_t counter = 0;
    for (auto& cursor : cursors) {
        if (cursor.deleted) {
            std::cerr << counter++ << ": skip deleted cursor\n";
            continue;
        } else {
            std::cerr << counter++ << ": cursor: \n";
        }
        int stepType = cursor.step(position);
        std::cerr << "step: " << stepType << "\n\n";

        if (stepType > 1) {
            std::cerr << "link\n";
            TNode* currentNode = cursor.edge->parentNode;
            if (nodeForLink != nullptr && nodeForLink->suffixLink == nullptr) {
                nodeForLink->suffixLink = currentNode;
            }
            nodeForLink = currentNode;
        }
        if (stepType == 2) {
            cursor.deleted = true;
        }
        if (stepType == 3) {
            break;
        }
    }
}

int TTreeCursor::step(size_t position) {
    std::cerr << "step(\n"
        << "  pos: " << position << " -> '" << edge->subString.str.at(position) << "'\n"
        << "  cur: " << cursor   << "'\n"
        << "  sub: " << edge->subString.copy() << "\n"
        << ")" << std::endl
    ;

    if (cursor > edge->subString.size()) {
        std::cerr << "respawn ("
            << "\n  cursor: " << cursor
            << "\n  size: " << edge->subString.size()
            << "\n  sub: " << edge->subString.copy()
            << "\n)" << std::endl
        ;
        cursor = cursor - edge->subString.size();
        char prevEndChar = edge->subString.str[edge->subString.end];
        edge = edge->endNode->get(prevEndChar);
    }

    int stepType = 0;
    if (edge->subString.positionIsValid(cursor)) {
        std::cerr << "position is valid" << std::endl;
        if (edge->subString.at(cursor) == edge->subString.str[position]) {
            //! just follow
            std::cerr << "just follow" << std::endl;
            stepType = 1;
        } else {
            std::cerr << "split" << std::endl;
            edge->split(cursor);
            edge = edge->endNode->addEdge(TSubstring(edge->subString.str, position));
            stepType = 2;
            cursor = 0;
        }
    } else {
        if (edge->endNode == nullptr) {
            //! create node at the end
            std::cerr << "create end node" << std::endl;
            edge->endNode.reset(
                new TNode(edge)
            );
        }
        char ch = edge->subString.str[position];
        if (edge->endNode->has(ch)) {
            edge = edge->endNode->get(ch);
            std::cerr << "Yes! Third type" << std::endl;
            stepType = 3; // Yes! Third type of step
            cursor = 0;
        } else {
            std::cerr << "Add edge to node (" << edge->subString.copy() << ")\n";
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
    os << '[' << subString.start << ':' << end << "] " << subString.copy() << std::endl;
    //*dbg*/ std::cerr << "edge show\n";
    if (endNode != nullptr) {
        endNode->show(lvl + 1, os);
    }
    //*dbg*/ std::cerr << "edge show end\n";
}

void TNode::show(size_t lvl, std::ostream& os) const {
    //*dbg*/ std::cerr << "node show\n";
    ++lvl;
    for (size_t i = 0; i < edges.size(); ++i) {
        if (nullptr != edges[i]) {
            os  << std::string(lvl, ' ')
                << "-("
                << static_cast<char>(FIRST_ABC_CHAR + i)
                << "): "
            ;
            edges[i]->show(lvl, os);
            // os << '\n';
        } else {
            // os << "-";
            // os << '\n';
        }
    }
}

void TTreeBase::show(std::ostream& os) const {
    rootEdge.show(0, os);
}

}

