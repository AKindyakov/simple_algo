#include <cstdlib>
#include <vector>

template<
    typename Type,
    typename Direct,
    typename Reverse
>
class TFenwickTree {
public:
    TFenwickTree();
    explicit TFenwickTree(std::vector<Type>&& src);
    explicit TFenwickTree(size_t length);
    template<typename InputIt>
    TFenwickTree(InputIt first, InputIt last);

    void Swap(size_t index, Type newValue);
    void Push(Type value);
    void Pop(Type value);

    Type Get(size_t start, size_t end) const;

private:
    inline size_t BitG(size_t index) {
        return index & (index + 1);
    }

private:
    std::vector<Type> Array;
    std::vector<Type> Partial;
};
