class TFuzzySearch: public TTreeBase {
public:
    TFuzzySearch(const std::string& str)
        : TTreeBase(str)
    {
    }

    struct TSearchAnswer {
        size_t start;
        size_t length;
    }

    std::vector<TSearchAnswer> search(const std::string& pattern);
private:
};


