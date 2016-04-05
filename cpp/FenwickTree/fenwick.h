#include "../SimpleAlgoUtil/simple_exception.h"

#include <cstdlib>
#include <vector>
namespace NFenwickTree {
template<
    typename Type
    , typename Add
    , typename Sub
    , Type Initial = 0
>
class TFenwickTree {
public:
    /**
    *
    */
    TFenwickTree();

    /**
    *
    */
    explicit TFenwickTree(std::vector<Type>&& src);

    /**
    *
    */
    explicit TFenwickTree(size_t length);

    /**
    *
    */
    template<typename InputIt>
    TFenwickTree(InputIt first, InputIt last);

    /**
    *
    */
    void Swap(size_t index, Type newValue);

    /**
    *
    */
    void Push(Type value);

    /**
    *
    */
    void Pop(Type value);

    /**
    * O(logN)
    */
    Type Get(size_t start, size_t end) const;

private:
    static inline size_t BitG(size_t index) {
        return index & (index + 1);
    }

    void Recount();
    void UpdateOne(size_t pIndex);
private:
    std::vector<Type> Array;
    std::vector<Type> Partial;
};

template<typename Type>
Type Add(Type one, Type two) {
    return one + two;
}

template<typename Type>
Type Sub(Type from, Type what) {
    return from - what;
}

template<
    typename Type
    , typename A
    , typename S
>
TFenwickTree<Type, A, S>
Create(std::vector<Type>&& arr, A add, S sub) {
    return TFenwickTree<Type, A, S>(std::move(arr));
}

template<
    typename Type
    , typename Add
    , typename Sub
    , Type Initial
>
TFenwickTree<Type, Add, Sub, Initial>::TFenwickTree(std::vector<Type>&& arr)
    : Array(std::move(arr))
{
    Recount();
}

template<
    typename Type
    , typename Add
    , typename Sub
    , Type Initial
>
void TFenwickTree<Type, Add, Sub, Initial>::Recount() {
    for (size_t pi = 0; pi < Partial.size(); ++pi) {
        UpdateOne(pi);
    }
}

template<
    typename Type
    , typename Add
    , typename Sub
    , Type Initial
>
void TFenwickTree<Type, Add, Sub, Initial>::UpdateOne(size_t pIndex) {
    size_t g = BitG(pIndex);
    //Type& p = Partial[pIndex];
    for (size_t gi = g; g <= pIndex; ++gi) {
         Partial[pIndex] = Add(Partial[pIndex], Array[gi]);
         //Partial[pIndex] = Partial[pIndex] + Array[gi];
    }
}

template<
    typename Type
    , typename Add
    , typename Sub
    , Type Initial
>
Type TFenwickTree<Type, Add, Sub, Initial>::Get(size_t start, size_t end) const {
    if (end == 0 || start == end) {
        return 0;
    }
    if (start < end) {
        throw TSimpleException("Wrong interval, start less then end")
            << "(" << start << " < " << end << ")";
    }
    Type ret = Initial;
    while (true) {
        ret = Add(ret, Partial[end]);
        end = BitG(end);
        if (end == 0) {
            break;
        }
        --end;
    }
    while (true) {
        ret = Sub(ret, Partial[start]);
        start = BitG(start);
        if (start == 0) {
            break;
        }
        --start;
    }
    return ret;
}
}
