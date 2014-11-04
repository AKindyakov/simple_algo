#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

template<
    typename TKey,
    typename TComparator,
    size_t heapOrder = 1,
    typename TContainer = std::vector<TKey>
>
class Heap {
public:
    explicit Heap(TComparator comparator)
        : compare(comparator) {}

    explicit Heap(TComparator comparator, const TContainer& from)
        : storage(from)
        , compare(comparator) {
        for (std::size_t i = storage.size(); i != 0; --i) {
            siftDown(i - 1);
        }
    }

    explicit Heap(TComparator comparator, TContainer&& from)
        : storage(from)
        , compare(comparator) {
        for (std::size_t i = storage.size(); i != 0; --i) {
            siftDown(i - 1);
        }
    }

    TKey& top() {
        return storage.front();
    }

    const TKey& top() const {
        return storage.front();
    }

    void pop() {
        std::swap(storage.front(), storage.back());
        storage.pop_back();
        siftDown();
    }

    void push(const TKey& key) const {
        storage.push_back(key);
        siftUp();
    }

    void push(TKey&& key) const {
        storage.push_back(key);
        siftUp();
    }

private:
    TContainer storage;
    TComparator compare;

private:
    std::size_t getParent(std::size_t child) {
        return (child - 1) >> heapOrder;
    }

    std::size_t getFirstChild(std::size_t parent) {
        return (parent << heapOrder) + 1;
    }

    std::size_t getMinChild(std::size_t parent) {
        const std::size_t end = storage.size();
        std::size_t firstChild = std::min(
            getFirstChild(parent),
            end
        );
        std::size_t endOfChild = std::min(
            firstChild + (1 << heapOrder),
            end
        );
        std::size_t m = firstChild;
        for (std::size_t i = firstChild; i < endOfChild; ++i) {
            if (compare(storage[i], storage[m])) {
                m = i;
            }
        }
        return m;
    }

    void siftUp() {
        if (storage.empty()) {
            return;
        }
        std::size_t child = storage.size() - 1;
        while (child != 0) {
            std::size_t parent = getParent(child);
            if (compare(storage[child], storage[parent])) {
                std::swap(storage[child], storage[parent]);
            } else {
                break;
            }
            child = parent;
        }
    }

    void siftDown(std::size_t parent = 0) {
        std::size_t end = storage.size();
        while (parent < end) {
            std::size_t child = getMinChild(parent);
            if (child >= end) {  // there are no valid childrens
                break;
            }
            if (compare(storage[child], storage[parent])) {
                std::swap(storage[child], storage[parent]);
            } else {
                break;
            }
            parent = child;
        }
    }
};
