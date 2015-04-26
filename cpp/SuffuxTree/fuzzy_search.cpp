#include "fuzzy_search.h"

//  std::vector<SearchAnswer>
//  TFuzzySearch::search(
//      const std::string& pattern
//  ) const
//  {
//      std::vector<size_t> answer;
//      std::vector<size_t> patternQueue;
//      std::vector<TEdge*> edgeQueue;
//
//      TEdge* edge = rootEdge;
//      size_t patternCursor = 0;
//
//          for (size_t i = 0; i < edge->subString.size(); ++i) {
//              char pCh = pattern[patternCursor];
//              if (pCh == '?' || pCh == edge->subString.at(i)) {
//                  ++patterncursor;
//              } else {
//                  // answer receiving
//                  std::vector<size_t> ends;
//                  traverseSubTree(edge, 0, ends);
//                  for (auto& e : ends) {
//                      answer.push_back(text.size() - e);
//                  }
//              }
//          }
//  }
//
//  void TFuzzySearch::traverseSubTree(const TEdge* edge, size_t depth, std::vector<size_t>& ends) {
//      depth += edge->size();
//      if (edge->endNode == nullptr) {
//          ends.push_back(depth);
//      } else {
//          for (auto& e : edge->endNode->edges) {
//              if (e != nullptr) {
//                  traverseSubTree(e.get(), depth, ends);
//              }
//          }
//      }
//  }

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
    const std::vector<TConstTreeCursor>& endPoints
) const {
    std::vector<TSubstring> rezult;
    return rezult;
}
