#include "zfunction.h"

#include <iostream>
#include <sstream>
#include <string>

class utException: public std::exception {
public:
    utException() {}
    utException(const std::string& what)
        : whatHappen(what) {
    }

    template<typename T>
    utException& operator<<(const T& val) {
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
        utException::printArgs(ostr, args...);
        ostr << ")";
        return ostr.str();
    }
private:
    std::string whatHappen;

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
utException&
utException::operator<< <std::vector<size_t>>(
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

#include "../SimpleAlgoUtil/simple_exception.h"
#include "../SimpleAlgoUtil/unit_test.h"

void
testsZFunction() {
    TestSomeFunction(
        std::vector<size_t>{7, 0, 1, 0, 3, 0, 1, },
        zFunction,
        "abacaba"
    );
    TestSomeFunction(
        std::vector<size_t>{10, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        zFunction,
        "abcdefghij"
    );
    TestSomeFunction(
        std::vector<size_t>{9, 8, 7, 6, 5, 4, 3, 2, 1, },
        zFunction,
        "aaaaaaaaa"
    );
    TestSomeFunction(
        std::vector<size_t>{1, },
        zFunction,
        "a"
    );
    TestSomeFunction(
        std::vector<size_t>{},
        zFunction,
        ""
    );
    TestSomeFunction(
        std::vector<size_t>{7, 0, 4, 0, 2, 0, 0, },
        zFunction,
        "abababb"
    );
    TestSomeFunction(
        std::vector<size_t>{10, 0, 0, 6, 0, 0, 3, 0, 0, 0, },
        zFunction,
        "abcabcabcc"
    );
}

void
testZFunctionFind() {
    TestSomeFunction(
        std::vector<size_t>{2,},
        zFunctionPatternMatch,
        "must", "I must not fear."
    );
    TestSomeFunction(
        std::vector<size_t>{12,},
        zFunctionPatternMatch,
        "mind", "Fear is the mind-killer."
    );
    TestSomeFunction(
        std::vector<size_t>{0,},
        zFunctionPatternMatch,
        "Fear", "Fear is the little-death that brings total obliteration."
    );
    TestSomeFunction(
        std::vector<size_t>{15,},
        zFunctionPatternMatch,
        "fear.", "I will face my fear."
    );
    TestSomeFunction(
        std::vector<size_t>{30, 45},
        zFunctionPatternMatch,
        "me", "I will permit it to pass over me and through me."
    );
    TestSomeFunction(
        std::vector<size_t>{},
        zFunctionPatternMatch,
        "When", "And when it has gone past I will turn the inner eye to see its path."
    );
    TestSomeFunction(
        std::vector<size_t>{},
        zFunctionPatternMatch,
        "pain", "Where the fear has gone there will be nothing."
    );
    TestSomeFunction(
        std::vector<size_t>{2, 9, 10},
        zFunctionPatternMatch,
        "l", "Only I will remain."
    );
}

int main() {
    testsZFunction();
    testZFunctionFind();
    return 0;
}
