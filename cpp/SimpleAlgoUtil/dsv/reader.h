#pragma once

#include <istream>
#include <array>
//#include <iostream>
#include <ctype.h>

std::string readToDelimiter(std::istream& in, std::istream::char_type delim) {
    std::string buf;
    while (in) {
        char ch = in.get();
        buf.push_back(ch);
        if (ch == delim) {
            return buf;
        }
    }
    return buf;
}

std::string readline(std::istream& in) {
    return readToDelimiter(in, in.widen('\n'));
}

size_t readToStops(std::istream& in, std::string stops, std::string& out) {
    while (in) {
        char ch = in.get();
        if (isascii(ch)) {
            size_t p = stops.find(ch);
            if (p != std::string::npos) {
                return p;
            }
            out.push_back(ch);
        }
    }
    return std::string::npos;
}

namespace DSVPrivate {
    using TDelimiters = std::string;
    enum EDelimiters: size_t {
        KEY_VALUE = 0,
        PAIR = 1,
        RECORD = 2
    };
}

class TDSVException: public std::exception {
private:
    std::string whatHappen;

public:
    TDSVException() {}
    TDSVException(const std::string& what)
        : whatHappen(what)
    {
    }

    const char* what() const throw() override {
        return whatHappen.c_str();
    }
};

class TDSVRecord;
class TDSVReader;

class TKeyValuePair {
public:
    std::string key;
    std::string value;
};

class TKVPairIterator {
private:
    TKeyValuePair pair;
    std::istream& input;
    const DSVPrivate::TDelimiters delimiters;
    enum EStatus {
        CONTINUE,
        LAST_PAIR,
        END
    };
    EStatus status = CONTINUE;
    friend TDSVRecord;

public:
    const TKeyValuePair& operator * () {
        return pair;
    }

    TKVPairIterator& operator ++ () {
        read();
        return *this;
    }

    bool operator != (const TKVPairIterator& right) {
        return status != right.status;
    }

private:
    TKVPairIterator(
        std::istream& in,
        DSVPrivate::TDelimiters _delimiters,
        bool ended = false
    )
    : input(in)
    , delimiters(_delimiters)
    , status(CONTINUE)
    {
        if (ended) {
            status = END;
        }
        read();
    }

    void read() {
        if (status > 0) {
            status = END;
            return;
        }
        pair.key.clear();
        size_t stoppedDelim = readToStops(input, delimiters, pair.key);
        if (stoppedDelim == DSVPrivate::TDelimiters::npos) {
            status = END;
            return;
        } else if (stoppedDelim != DSVPrivate::KEY_VALUE) {
            throw TDSVException("expected KEY_VALUE delimiter");
        } else if (pair.key.empty()) {
            throw TDSVException("empty key");
        }
        pair.value.clear();
        stoppedDelim = readToStops(input, delimiters, pair.value);
        if (stoppedDelim == DSVPrivate::TDelimiters::npos) {
            status = LAST_PAIR;
        } else if (stoppedDelim == DSVPrivate::RECORD) {
            status = LAST_PAIR;
        } else if (stoppedDelim == DSVPrivate::KEY_VALUE) {
            throw TDSVException("unexpected KEY_VALUE delimiter after value");
        } else if (stoppedDelim != DSVPrivate::PAIR) {
            throw TDSVException("expected PAIR delimiter");
        }
    }
};

class TDSVRecord {
private:
    std::istream& input;
    DSVPrivate::TDelimiters delimiters;

    TDSVRecord(
        std::istream& in,
        DSVPrivate::TDelimiters _delimiters
    )
    : input(in)
    , delimiters(_delimiters)
    {
    }

    friend TDSVReader;

public:

    TKVPairIterator begin() {
        return TKVPairIterator(input, delimiters);
    }

    TKVPairIterator end() {
        return TKVPairIterator(input, delimiters, true);
    }
};

class TDSVReader {
private:
    DSVPrivate::TDelimiters delimiters;
    std::istream& input;

public:
    TDSVReader(
        std::istream& in,
        const char keyValueDelimiter,
        const char pairDelimiter,
        const char recordDelimiter
    )
    : delimiters({keyValueDelimiter, pairDelimiter, recordDelimiter})
    , input(in)
    {
    }

    operator bool() const {
        return static_cast<bool>(input);
    }

    TDSVRecord next() {
        return TDSVRecord(input, delimiters);
    }
};



