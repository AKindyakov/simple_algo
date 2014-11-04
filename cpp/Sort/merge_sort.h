#pragma once

#include "sort_error.h"
#include "insertion_sort.h"

#include <vector>
#include <iterator>
#include <limits>

class MergeSortException: public std::exception {
public:
    MergeSortException() {}
    MergeSortException(const std::string& what)
        : whatHappen("[merge sort exception] ") {
        whatHappen.append(what);
    }

    template<typename T>
    MergeSortException& operator<<(const T& val) {
        std::ostringstream ostr;
        ostr << val;
        whatHappen.append(ostr.str());
        return *this;
    }

    const char* what() const throw() override { return whatHappen.c_str(); }

private:
    std::string whatHappen;
};

using Container = std::vector<int>;

void
merge_range(
    Container& cnt,
    Container& buf,
    std::size_t firstStart,
    std::size_t firstEnd,
    std::size_t secondStart,
    std::size_t secondEnd
);

void
pure_merge_sort(
    Container& cnt,
    std::size_t start = 0,
    std::size_t end = std::numeric_limits<unsigned>::max()
);

void
merge_sort(
    Container& cnt,
    std::size_t start = 0,
    std::size_t end = std::numeric_limits<unsigned>::max()
);

template<
    typename TIterator,
    typename TBuffIterator,
    typename TComparator
>
void
merge_range(
    const TIterator leftBegin,
    const TIterator rightBegin,
    const TIterator rightEnd,
    const TBuffIterator bufferBegin,
    const TBuffIterator bufferEnd,
    TComparator comparator
) {
    if (std::distance(leftBegin, rightBegin)
        > std::distance(bufferBegin, bufferEnd)) {
        throw MergeSortException() << "too small buffer size";
    }

    TIterator endOfDataInBuffer = std::copy(leftBegin, rightBegin, bufferBegin);

    TBuffIterator bufferIter = bufferBegin;
    TIterator rightIter = rightBegin;
    TIterator inserter = leftBegin;

    while (inserter != rightEnd) {
        if (bufferIter == endOfDataInBuffer) {
            break;
        } else if (rightIter == rightEnd) {
            std::swap(*inserter, *bufferIter);
            ++bufferIter;
            ++inserter;
        } else if (comparator(*rightIter, *bufferIter)) {
            std::swap(*inserter, *rightIter);
            ++rightIter;
            ++inserter;
        } else {
            std::swap(*inserter, *bufferIter);
            ++bufferIter;
            ++inserter;
        }
    }
}

template<typename TIterator>
void rewindIterator(TIterator& it, const TIterator& end, std::size_t distance) {
    for (std::size_t counter = 0; counter < distance; ++counter) {
        ++it;
        if (it == end) {
            break;
        }
    }
}

template<
    typename TIterator,
    typename TComparator
>
void
merge_sort(
    TIterator start,
    TIterator end,
    TComparator comparator
) {
    // empiric coefficient - basis size
    const std::size_t PART_SIZE = 8;  // maybe need to be verify

    const size_t inSize = std::distance(start, end);
    typedef typename std::iterator_traits<TIterator>::value_type TKey;
    std::vector<TKey> buffer(inSize);

    // sort base chunks
    for (TIterator localEnd = start; localEnd != end; ) {
        TIterator localStart = localEnd;
        rewindIterator(localEnd, end, PART_SIZE);
        insertion_sort(localStart, localEnd, comparator);
    }

    // merge base chunks
    for (std::size_t partSize = PART_SIZE; partSize < inSize; ) {
        std::size_t step = partSize << 1;

        TIterator localLeftBegin  = start;
        TIterator localRightBegin = start;
        TIterator localEnd        = start;

        while (localRightBegin != end) {
            rewindIterator(localRightBegin, end, partSize);
            rewindIterator(localEnd, end, step);

            merge_range(
                localLeftBegin,
                localRightBegin,
                localEnd,
                buffer.begin(),
                buffer.end(),
                comparator
            );

            localLeftBegin  = localEnd;
            localRightBegin = localEnd;
            localEnd        = localEnd;
        }
        partSize = step;
    }
}
