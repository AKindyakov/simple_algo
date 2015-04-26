#include "tree.h"

class TFuzzySearch: public TSuffixTreeBase {
public:
    explicit TFuzzySearch(const std::string& text, char _wildcard = '?')
        : TSuffixTreeBase(text)
        , wildcard(_wildcard)
    {
    }

    using TSubstring = NSufixTree::TSubstring;
    using TConstTreeCursor = NSufixTree::TConstTreeCusor;

    std::vector<TSubstring> search(const std::string& pattern) const {
        bool onlyFirst = false;
        return findAllEnds(onlyMatch(pattern, onlyFirst));
    }

    bool search(const std::string& pattern, TSubstring& answer) const {
        bool onlyFirst = true;
        std::vector<TConstTreeCursor> ends = onlyMatch(pattern, onlyFirst);
        if (ends.empty()) {
            return false;
        }
        answer = ends.front().edge->subString;
        answer.end = answer.start + ends.front().cursor;
        answer.start = answer.end - pattern.size();
        return true;
    }

private:
    std::vector<TConstTreeCursor>
    onlyMatch(
        const std::string& pattern,
        bool onlyFirst
    ) const;

    std::vector<TSubstring>
    findAllEnds(
        const std::vector<TConstTreeCursor>& endPoints
    ) const;

private:
    char wildcard;
};


