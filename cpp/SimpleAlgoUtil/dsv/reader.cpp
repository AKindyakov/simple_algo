#include "reader.h"

namespace DSV {

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

const TKeyValuePair& TKVPairIterator::operator * () {
    return pair;
}

TKVPairIterator& TKVPairIterator::operator ++ () {
    read();
    return *this;
}

bool TKVPairIterator::operator != (const TKVPairIterator& right) {
    return status != right.status;
}

 TKVPairIterator::TKVPairIterator(
    std::istream& in,
    DSVPrivate::TDelimiters _delimiters,
    bool ended
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


void TKVPairIterator::read() {
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

TKVPairIterator TDSVRecord::begin() {
    return TKVPairIterator(input, delimiters);
}

TKVPairIterator TDSVRecord::end() {
    return TKVPairIterator(input, delimiters, true);
}

TDSVReader::operator bool() const {
    return static_cast<bool>(input);
}

TDSVRecord TDSVReader::next() {
    return TDSVRecord(input, delimiters);
}

}  // namepace DSV

