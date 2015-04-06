#include "fuzzy_search.h"

std::vector<SearchAnswer>
TFuzzySearch::search(
    const std::string& pattern
) const
{
    std::vector<size_t> answer;

    std::vector<size_t> patternStack;
    std::vector<TEdge*> edgeStack;

    TEdge* edge = rootEdge;
    size_t patternCursor = 0;

        for (size_t i = 0; i < edge->subString.size(); ++i) {
            char pCh = pattern[patternCursor];
            if (pCh == '?' || pCh == edge->subString.at(i)) {
                ++patterncursor;
            } else {
                // answer receiving
                std::vector<size_t> ends;
                traverseSubTree(edge, 0, ends);
                for (auto& e : ends) {
                    answer.push_back(text.size() - e);
                }
            }
        }
}

void TFuzzySearch::traverseSubTree(const TEdge* edge, size_t depth, std::vector<size_t>& ends) {
    depth += edge->size();
    if (edge->endNode == nullptr) {
        ends.push_back(depth);
    } else {
        for (auto& e : edge->endNode->edges) {
            if (e != nullptr) {
                traverseSubTree(e.get(), depth, ends);
            }
        }
    }
}
