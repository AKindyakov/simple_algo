#include "merge_sort.h"

#include <iostream>
#include <vector>

void merge_range(
    Container& cnt,
    Container& buf,
    size_t firstStart,
    size_t firstEnd,
    size_t secondStart,
    size_t secondEnd
) {
    size_t firstSize = firstEnd - firstStart;
    buf.resize(firstSize);
    buf.assign(cnt.begin() + firstStart, cnt.begin() + firstEnd);

    //size_t compareCounter = 0;
    size_t fiter = 0;
    size_t siter = secondStart;
    size_t inserter = firstStart;
    while (inserter < secondEnd) {
        if (fiter == firstSize) {
            break;
        } else if (siter == secondEnd) {
            cnt[inserter] = buf[fiter];
            // std::cerr << "cnt[ " << inserter << " ] = " << buf[fiter] << '\n';
            ++fiter;
            ++inserter;
        } else if (cnt[siter] < buf[fiter]) {
            // ++compareCounter;
            cnt[inserter] = cnt[siter];
            // std::cerr << "cnt[ " << inserter << " ] = " << cnt[siter] << '\n';
            ++siter;
            ++inserter;
        } else {
            // ++compareCounter;
            cnt[inserter] = buf[fiter];
            // std::cerr << "cnt[ " << inserter << " ] = " << buf[fiter] << '\n';
            ++fiter;
            ++inserter;
        }
    }
    // std::cerr << "compareCounter: " << compareCounter << '\n';
}

void pure_merge_sort(Container& cnt) {
    size_t size = cnt.size();
    Container buf(size);

    size_t partSize = 1;
    while (partSize < size) {
        size_t step = 2 * partSize;
        size_t first = 0;
        size_t second = partSize;
        size_t endSecond = step;
        while (second < size) {
            if (endSecond > size) {
                endSecond = size;
            }
            // std::cerr << " first : " <<  first  << '\n';
            // std::cerr << " second: " << second << '\n';
            // std::cerr << " end   : " << endSecond << '\n';
            merge_range(cnt, buf, first, second, second, endSecond);
            second += step;
            first += step;
            endSecond += step;
        }
        partSize = step;
    }
}

void merge_sort(Container& cnt) {
    size_t size = cnt.size();
    Container buf(size);

    size_t partSize = 1;
    while (partSize < size) {
        size_t step = 2 * partSize;
        size_t first = 0;
        size_t second = partSize;
        size_t endSecond = step;
        while (second < size) {
            if (endSecond > size) {
                endSecond = size;
            }
            // std::cerr << " first : " <<  first  << '\n';
            // std::cerr << " second: " << second << '\n';
            // std::cerr << " end   : " << endSecond << '\n';
            merge_range(cnt, buf, first, second, second, endSecond);
            second += step;
            first += step;
            endSecond += step;
        }
        partSize = step;
    }
}
