#pragma once

#include "merge_sort.h"

#include <algorithm>
#include <ios>
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
        std::size_t chunksLimit = 2 << 10, // 2048
        const char* tempDirectory = "/var/tmp"
    ) noexcept
        : comparator(keyComparator)
        , chunks(chunksLimit)
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
    std::size_t chunks;
    const char* tempDir;
    std::size_t bufferSize;
    void* buffer;

    std::vector<TObj> readChunk(std::istream& is, std::size_t chunkSize);
};

template<
    typename TObj,
    typename TComparator
>
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
    std::size_t chunkSize = bufferSize * 2 / 3;
    std::ifstream inFile(inFileName, std::fstream::in);
    std::vector<std::fstream> tmpFiles;

    size_t chunkNum = 0;
    while (!inFile.eof()) {
        auto chunk(readChunk(inFile, chunkSize));
        std::sort(chunk.begin(), chunk.end(), comparator);

        std::ostringstream tmpPath(tempDir);
        tmpPath << "/external_sort_tmp_" << chunkNum++ << '_' << std::time(0);
        std::fstream fptr(tmpPath.str(), std::fstream::in | std::fstream::out);

        for (auto&& val : chunk) {
            fptr << val;
        }
        fptr.seekg(0);
        tmpFiles.push_back(std::move(fptr));
    }
    inFile.close();

    std::priority_queue<TObj, std::vector<TObj>, std::greater<TObj>> minHeap;
    for (auto&& pt : tmpFiles) {
        TObj m;
        pt >> m;
        minHeap.push(std::move(m));
    }
}

