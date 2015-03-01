#pragma once

#include <string>
#include <sstream>

class TSimpleException: public std::exception {
private:
    std::string whatHappen;

public:
    TSimpleException() {}
    TSimpleException(const std::string& what)
        : whatHappen(what) {
    }

    template<typename T>
    TSimpleException& operator<<(const T& val) {
        std::ostringstream ostr(whatHappen, std::ios_base::ate);
        ostr << val;
        whatHappen = ostr.str();
        return *this;
    }

    const char* what() const throw() override {
        return whatHappen.c_str();
    }

    template<
        typename... Args
        >
    static std::string
    argsToString(Args... args) {
        std::ostringstream ostr;
        ostr << "(";
        TSimpleException::printArgs(ostr, args...);
        ostr << ")";
        return ostr.str();
    }

private:
    static void printArgs(std::ostream& os){}

    template<
        typename Arg1,
        typename... Args
        >
    static void
    printArgs(
        std::ostream& os,
        Arg1 arg,
        Args&... args
    ) {
        os << '\"' << arg << "\", ";
        printArgs(os, args...);
    }

};

template<>
TSimpleException&
TSimpleException::operator<< < std::vector<size_t> >(
    const std::vector<size_t>& cnt
) {
    std::ostringstream ostr;
    ostr << "[";
    for (const auto& t : cnt) {
        ostr << t << ", ";
    }
    ostr << "]";
    whatHappen.append(ostr.str());
    return *this;
}

