#pragma once

#include <sstream>
#include <string>
#include <stdexcept>

class SortException: public std::exception {
public:
    SortException() {}
    SortException(const std::string& what)
        : whatHappen(what) {
    }

    template<typename T>
    SortException& operator<<(const T& val) {
        std::ostringstream ostr;
        ostr << val;
        whatHappen.append(ostr.str());
        return *this;
    }

    const char* what() const throw() override { return whatHappen.c_str(); }

private:
    std::string whatHappen;
};
