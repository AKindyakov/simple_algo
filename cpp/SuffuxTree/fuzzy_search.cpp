#include "fuzzy_search.h"

std::vector<TFuzzySearch::TConstTreeCursor>
TFuzzySearch::onlyMatch(
    const std::string& pattern,
    bool onlyFirst
) const {
    std::deque<TConstTreeCursor> treeQueue = {
        TConstTreeCursor(&rootEdge)
    };
    std::deque<size_t> patternQueue = {0};

    std::vector<TConstTreeCursor> matched;

    while (!treeQueue.empty()) {
        size_t deep = patternQueue.back();
        TConstTreeCursor cursor = treeQueue.back();
        while (true) {
            if (deep >= pattern.size()) {
                matched.push_back(cursor);
                break;
            }
            char pch = pattern[deep];
            if (cursor.end()) {
                if (pch == wildcard) {
                    if (cursor.edge->endNode) {
                        for (const auto& edge : cursor.edge->endNode->edges) {
                            if (edge) {
                                patternQueue.push_front(deep);
                                treeQueue.push_front(TConstTreeCursor(edge.get()));
                            }
                        }
                    }
                    break;
                } else {
                    auto next = cursor.edge->endNode->get(pattern[deep]);
                    if (next == nullptr) {
                        break;
                    } else {
                        cursor = TConstTreeCursor(next);
                    }
                }
            } else {
                if (pch != cursor.ch() && pch != wildcard) {
                    break;
                }
            }
            ++cursor;
            ++deep;
        }
        patternQueue.pop_back();
        treeQueue.pop_back();
    }
    return matched;
}

std::vector<TFuzzySearch::TSubstring>
TFuzzySearch::findAllEnds(
    const std::vector<TConstTreeCursor>& endPoints,
    size_t patternSize
) const {
    std::vector<TSubstring> rezult;

    for (const auto& point : endPoints) {
        std::deque<TConstTreeCursor> nodeQueue = {point};
        std::deque<size_t> deepQueue = {0};

        while (!nodeQueue.empty()) {
            size_t deep = deepQueue.back();
            TConstTreeCursor cursor = nodeQueue.back();
            deepQueue.pop_back();
            nodeQueue.pop_back();
            while (true) {
                if (cursor.end()) {
                    if (cursor.edge->endNode) {
                        size_t t = 0;
                        for (const auto& edge : cursor.edge->endNode->edges) {
                            if (edge) {
                                ++t;
                                deepQueue.push_front(deep);
                                nodeQueue.push_front(TConstTreeCursor(edge.get()));
                            }
                        }
                        if (t == 0) {
                            throw TSimpleException("realy?");
                        }
                    } else {
                        rezult.push_back(
                            TSubstring(
                                text,
                                text.size() - deep - patternSize,
                                text.size() - deep
                            )
                        );
                    }
                    break;
                }
                ++cursor;
                ++deep;
            }
        }

    }
    return rezult;
}

