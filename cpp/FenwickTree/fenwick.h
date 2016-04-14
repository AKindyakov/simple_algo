#include "../SimpleAlgoUtil/simple_exception.h"

#include <cstdlib>
#include <vector>

namespace NFenwickTree {

template<typename Type>
class TAdd {
public:
    const Type operator()(Type one, Type two) const {
        return one + two;
    }
};

template<typename Type>
class TSub {
public:
    const Type operator()(Type from, Type what) const {
        return from - what;
    }
};

template<
    typename Type
    , typename _Add=TAdd<Type>
    , typename _Sub=TSub<Type>
>
class TFenwickTree {
public:
    /**
    *
    */
    explicit TFenwickTree();

    /**
    *
    */
    explicit TFenwickTree(std::vector<Type>&& src);

    /**
    *
    */
    explicit TFenwickTree(size_t length, Type value);

    /**
    *
    */
    template<typename InputIt>
    explicit TFenwickTree(InputIt first, InputIt last);

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
    Type Pop();

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
    _Add Add;
    _Sub Sub;
    std::vector<Type> Array;
    std::vector<Type> Partial;
};

template<
    typename Type
    , typename _Add
    , typename _Sub
>
TFenwickTree<Type, _Add, _Sub>::TFenwickTree()
{
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
TFenwickTree<Type, _Add, _Sub>::TFenwickTree(
    std::vector<Type>&& arr
)
    : Array(std::move(arr))
    , Partial(Array)
{
    Recount();
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
TFenwickTree<Type, _Add, _Sub>::TFenwickTree(
    size_t length
    , Type value
)
    : Array(length, value)
    , Partial(Array)
{
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
template<typename InputIt>
TFenwickTree<Type, _Add, _Sub>::TFenwickTree(
    InputIt first
    , InputIt last
)
    : TFenwickTree(std::vector<Type>(first, last))
{
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
void TFenwickTree<Type, _Add, _Sub>::Swap(
    size_t index
    , Type newValue
) {
    Type oldValue = Array[index];
    Array[index] = newValue;
    for (size_t i = index; i < Array.size(); i = i | (i + 1)) {
        Type& p = Partial[i];
        p = Sub(p, oldValue);
        p = Add(p, newValue);
    }
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
void TFenwickTree<Type, _Add, _Sub>::Push(Type value) {
    Array.push_back(value);
    Partial.push_back(value);
    UpdateOne(Array.size() - 1);
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
Type TFenwickTree<Type, _Add, _Sub>::Pop() {
    Type value = Array.back();
    Array.pop_back();
    Partial.pop_back();
    return value;
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
void TFenwickTree<Type, _Add, _Sub>::Recount() {
    for (size_t pi = 0; pi < Partial.size(); ++pi) {
        UpdateOne(pi);
    }
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
void TFenwickTree<Type, _Add, _Sub>::UpdateOne(size_t pIndex) {
    Type& p = Partial[pIndex];
    for (size_t gi = BitG(pIndex); gi < pIndex; ++gi) {
        p = Add(p, Array[gi]);
    }
}

template<
    typename Type
    , typename _Add
    , typename _Sub
>
Type TFenwickTree<Type, _Add, _Sub>::Get(size_t start, size_t end) const {
    if (end == 0 || start == end) {
        return 0;
    }
    if (start > end) {
        throw TSimpleException("Wrong interval, start less then end")
            << "(" << start << " > " << end << ")";
    }
    if (end > Array.size()) {
        end = Array.size();
    }
    Type ret = Partial[--end];
    while (true) {
        end = BitG(end);
        if (end == 0) {
            break;
        }
        ret = Add(ret, Partial[--end]);
    }

    while (start--) {
        ret = Sub(ret, Partial[start]);
        start = BitG(start);
    }
    return ret;
}
}
