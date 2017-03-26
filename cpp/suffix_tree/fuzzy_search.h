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
        return findAllEnds(onlyMatch(pattern, onlyFirst), pattern.size());
    }

private:
    std::vector<TConstTreeCursor>
    onlyMatch(
        const std::string& pattern,
        bool onlyFirst
    ) const;

    std::vector<TSubstring>
    findAllEnds(
        const std::vector<TConstTreeCursor>& endPoints,
        size_t patternSize
    ) const;

private:
    char wildcard;
};


