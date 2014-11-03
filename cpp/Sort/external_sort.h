#pragma once

#include "merge_sort.h"

#include <algorithm>
#include <ios>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <ctime>
#include <queue>

template<
    typename TObj,
    typename TComparator
>
class TExternalSorter {
public:
    TExternalSorter (
        TComparator keyComparator,
        std::size_t bufferSizeLimit = 1 << 29, // 512 MB
        std::size_t openedFilesLimit = 2 << 10, // 2048
        std::string tempDirectory = "/tmp"
    ) noexcept
        : comparator(keyComparator)
        , filesLimit(openedFilesLimit)
        , tempDir(tempDirectory)
    {}

    ~TExternalSorter() {}

    void
    sort(
        const char* fileName
    ) {
        sort(fileName, fileName);
    }

    void
    sort(
        const char* inFileName,
        const char* outFileName
    );

private:
    TComparator comparator;
    std::size_t filesLimit;
    std::string tempDir;
    std::size_t bufferSize;
    void* buffer;

    std::vector<TObj> readChunk(std::istream& is, std::size_t chunkSize);
};

template<
    typename TObj,
    typename TComparator >
std::vector<TObj>
TExternalSorter<TObj, TComparator>::readChunk(
    std::istream& is,
    std::size_t chunkSize
) {
    std::vector<TObj> chunk;
    std::size_t fullChunkSize = 0;
    while (
        !is.eof()
        && fullChunkSize < chunkSize
    ) {
        ++fullChunkSize;
        chunk.resize(chunk.size() + 1);
        is >> chunk.back();
    }
    return chunk;
}

template<
    typename TObj,
    typename TComparator
>
void
TExternalSorter<TObj, TComparator>::sort(
      const char* inFileName
    , const char* outFileName
) {
    std::size_t chunkSize = bufferSize / 2;
    std::ifstream inFile(inFileName, std::fstream::in);
    std::string s;
    inFile >> s;
    std::vector<std::string> tmpFiles;

    while (!inFile.eof()) {
        auto chunk = readChunk(inFile, 4);
        std::sort(chunk.begin(), chunk.end(), comparator);

        std::ostringstream tmpPath;
        tmpPath << tempDir
                << "/external_sort_tmp_"
                << inFileName
                << tmpFiles.size()
                << std::time(0);
        std::string name = tmpPath.str();
        std::fstream fptr(name.c_str(), std::fstream::out);

        for (const auto& val : chunk) {
            fptr << val;
        }
        fptr << std::endl;
        tmpFiles.push_back(std::move(name));
    }
    inFile.close();

    std::priority_queue<TObj, std::vector<TObj>, std::greater<TObj>> minHeap;
    for (const auto& pt : tmpFiles) {
        TObj m;
        pt >> m;
        minHeap.push(std::move(m));
    }
}

