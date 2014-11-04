#pragma once

#include "merge_sort.h"
#include "sort_error.h"

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>

/**
 * typename TObj - sorted type
 * typename TSerializer - serializer/desializer class,
 *      must have methods:
 *          TObj fromStream(std::istream& is, std::size_t& size) {
 *          void toStream(TObj, std::ostream&)
 * typename TComparator - compare
 *
 */
template<
    typename TObj,
    typename TSerializer,
    typename TComparator
>
class TExternalSorter {
public:
    TExternalSorter (
        TComparator itemComparator,
        TSerializer itemSerializer,
        std::size_t bufferSizeLimit = 1 << 29, // 512 MB
        std::size_t openedFilesLimit = 2 << 10, // 2048
        std::string tempDirectory = "/tmp"
    ) noexcept
        : compare(itemComparator)
        , serializer(itemSerializer)
        , filesLimit(openedFilesLimit)
        , tempDir(tempDirectory)
    {}

    ~TExternalSorter() {}

    void sort(
        std::istream& inFileStream,
        std::ostream& outFileStream
    );

    void sort(
        const std::string& inFileName,
        const std::string& outFileName
    ) {
        std::ifstream inFileStream(inFileName, std::fstream::in);
        std::ifstream outFileStream(outFileName, std::fstream::out);
        sort(inFileStream, outFileStream);
    }

private:
    TComparator compare;
    TSerializer serializer;
    std::size_t filesLimit;
    std::string tempDir;
    std::size_t bufferSize;
    void* buffer;

    std::vector<TObj> readChunk(std::istream& is, std::size_t chunkSize);

    void mergeSortedChunksToOne(
        std::vector<std::string>::const_iterator beginNames,
        std::vector<std::string>::const_iterator endNames,
        std::ostream& outFileStream
    );
    std::vector<std::string> mergeChunkFiles(const std::vector<std::string>& names);
    void removeTmpByNames(const std::vector<std::string>& names);
    std::string getNewTempFileName(unsigned long num);
};

template<
    typename TObj,
    typename TSerializer,
    typename TComparator
>
std::string
TExternalSorter<TObj, TSerializer, TComparator>::getNewTempFileName(unsigned long num) {
    std::ostringstream tmpPath;
    tmpPath << tempDir
            << "/external_sort_tmp_"
            << num
            << std::time(0);
    return tmpPath.str();
}

template<
    typename TObj,
    typename TSerializer,
    typename TComparator
>
std::vector<TObj>
TExternalSorter<TObj, TSerializer, TComparator>::readChunk(
    std::istream& is,
    std::size_t chunkSize
) {
    std::vector<TObj> chunk;
    std::size_t fullChunkSize = 0;
    do {
        std::size_t size = 0;
        chunk.push_back(serializer.fromStream(is, size));
        fullChunkSize += size;
    } while (
        !is.eof()
        && fullChunkSize < chunkSize
    );
    return chunk;
}

template<
    typename TObj,
    typename TSerializer,
    typename TComparator
>
void
TExternalSorter<TObj, TSerializer, TComparator>::mergeSortedChunksToOne(
    std::vector<std::string>::const_iterator beginNames,
    std::vector<std::string>::const_iterator endNames,
    std::ostream& outFileStream
) {
    std::map<TObj, std::size_t, TComparator> sortHeap(compare);
    std::vector<std::fstream> openedFiles(std::distance(beginNames, endNames));

    std::size_t i = 0;
    for (auto name = beginNames; name != endNames; ++name) {
        openedFiles[i++].open(name->c_str(), std::fstream::in);
        std::size_t size = 0;
        sortHeap[
            serializer.fromStream(openedFiles.back(), size)
        ] = openedFiles.size() - 1;
    }

    while (!sortHeap.empty()) {
        auto top = sortHeap.begin();
        serializer.toStream(top->first, outFileStream);

        std::size_t index = top->second;
        sortHeap.erase(top);

        auto& in = openedFiles[index];
        if (!in.eof()) {
            std::size_t size = 0;
            sortHeap[serializer.fromStream(in, size)] = index;
        }
    }
}

template<
    typename TObj,
    typename TSerializer,
    typename TComparator
>
std::vector<std::string>
TExternalSorter<TObj, TSerializer, TComparator>::mergeChunkFiles(
    const std::vector<std::string>& sortedChunkFileNames
) {
    std::vector<std::string> nextGenChunksNames;
    auto beginIter = sortedChunkFileNames.begin();
    while (beginIter != sortedChunkFileNames.end()) {
        auto endIter = sortedChunkFileNames.end();
        if (sortedChunkFileNames.size() > filesLimit) {
            endIter = sortedChunkFileNames.begin() + filesLimit;
        }
        nextGenChunksNames.push_back(
            getNewTempFileName(nextGenChunksNames.size())
        );
        std::ofstream out(nextGenChunksNames.back());
        mergeSortedChunksToOne(beginIter, endIter, out);
        beginIter = endIter;
    }
    return nextGenChunksNames;
}

template<
    typename TObj,
    typename TSerializer,
    typename TComparator
>
void
TExternalSorter<TObj, TSerializer, TComparator>::removeTmpByNames(
    const std::vector<std::string>& names
) {
    for (const auto& name : names) {
        if (std::remove(name.c_str()) != 0) {
            throw SortException("[external sort] ")
                << "Failed deleting temporary file: \""
                << name << "\"";
        }
    }
}

template<
    typename TObj,
    typename TSerializer,
    typename TComparator
>
void
TExternalSorter<TObj, TSerializer, TComparator>::sort(
    std::istream& inFileStream,
    std::ostream& outFileStream
) {
    std::vector<std::string> chunkFilesNames;
    do {
        auto chunk = readChunk(inFileStream, bufferSize);
        std::sort(chunk.begin(), chunk.end(), compare);

        std::string name = getNewTempFileName(chunkFilesNames.size());
        std::fstream fptr(name.c_str(), std::fstream::out);

        for (const auto& val : chunk) {
            serializer.toStream(val, fptr);
        }
        chunkFilesNames.push_back(std::move(name));
    } while (!inFileStream.eof());

    while (chunkFilesNames.size() > filesLimit) {
        std::vector<std::string> newGenChunksNames =
            mergeChunkFiles(chunkFilesNames);
        removeTmpByNames(chunkFilesNames);
        chunkFilesNames = std::move(newGenChunksNames);
    }
    mergeSortedChunksToOne(
        chunkFilesNames.begin(),
        chunkFilesNames.end(),
        outFileStream
    );
    removeTmpByNames(chunkFilesNames);
}
