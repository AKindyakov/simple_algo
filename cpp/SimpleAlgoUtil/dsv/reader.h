#pragma once

#include <istream>
#include <array>
#include <ctype.h>

namespace DSV {

std::string
readToDelimiter(
    std::istream& in,
    std::istream::char_type delim
);

std::string
readline(
    std::istream& in
);

size_t
readToStops(
    std::istream& in,
    std::string stops,
    std::string& out
);

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
    TKeyValuePair() {};
    TKeyValuePair(
        const std::string& _key
        , const std::string& _value
    )
        : key(_key)
        , value(_value)
    {}

public:
    std::string key;
    std::string value;
};

class TKVPairIterator {
public:
    const TKeyValuePair& operator * ();
    TKVPairIterator& operator ++ ();
    bool operator != (const TKVPairIterator& right);

private:
    TKVPairIterator(
        std::istream& in,
        DSVPrivate::TDelimiters _delimiters,
        bool ended = false
    );
    void read();

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
};

class TDSVRecord {
public:
    TKVPairIterator begin();
    TKVPairIterator end();

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
};

class TDSVReader {
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

    operator bool() const;
    TDSVRecord next();

private:
    DSVPrivate::TDelimiters delimiters;
    std::istream& input;
};

}  // namspace DSV

