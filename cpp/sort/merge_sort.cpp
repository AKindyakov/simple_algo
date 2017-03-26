#include "merge_sort.h"
#include "insertion_sort.h"

#include <vector>

void
merge_range(
    Container& cnt,
    Container& buf,
    std::size_t firstStart,
    std::size_t firstEnd,
    std::size_t secondStart,
    std::size_t secondEnd
) {
    std::size_t firstSize = firstEnd - firstStart;
    buf.resize(firstSize);
    buf.assign(cnt.begin() + firstStart, cnt.begin() + firstEnd);

    std::size_t fiter = 0;
    std::size_t siter = secondStart;
    std::size_t inserter = firstStart;
    while (inserter < secondEnd) {
        if (fiter == firstSize) {
            break;
        } else if (siter == secondEnd) {
            cnt[inserter] = buf[fiter];
            ++fiter;
            ++inserter;
        } else if (cnt[siter] < buf[fiter]) {
            cnt[inserter] = cnt[siter];
            ++siter;
            ++inserter;
        } else {
            cnt[inserter] = buf[fiter];
            ++fiter;
            ++inserter;
        }
    }
}

void
pure_merge_sort(
    Container& cnt,
    std::size_t start,
    std::size_t end
) {
    std::size_t size = cnt.size();
    Container buf(size);

    std::size_t partSize = 1;
    while (partSize < size) {
        std::size_t step = 2 * partSize;
        std::size_t first = 0;
        std::size_t second = partSize;
        std::size_t endSecond = step;
        while (second < size) {
            if (endSecond > size) {
                endSecond = size;
            }
            merge_range(cnt, buf, first, second, second, endSecond);
            second += step;
            first += step;
            endSecond += step;
        }
        partSize = step;
    }
}

void
merge_sort(
    Container& cnt,
    std::size_t start,
    std::size_t end
) {
    std::size_t size = cnt.size();
    Container buf(size);
    std::size_t partSize = 8;
    for (std::size_t start = 0; start < size; ) {
        auto end = start + partSize;
        if (size < end) {
            end = size;
        }
        insertion_sort(cnt, start, end);
        start = end;
    }
    while (partSize < size) {
        std::size_t step = 2 * partSize;
        std::size_t first = 0;
        std::size_t second = partSize;
        std::size_t endSecond = step;
        while (second < size) {
            if (endSecond > size) {
                endSecond = size;
            }
            merge_range(cnt, buf, first, second, second, endSecond);
            second += step;
            first += step;
            endSecond += step;
        }
        partSize = step;
    }
}
