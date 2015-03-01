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

template<>
utException&
utException::operator<< <std::vector<std::string>>(
    const std::vector<std::string>& cnt
) {
    std::ostringstream ostr;
    ostr << "[";
    for (const auto& t : cnt) {
        ostr << '\"' << t << "\", ";
    }
    ostr << "]";
    whatHappen.append(ostr.str());
    return *this;
}

void
testZFunction(
    const std::string& str
) {
    auto z = zFunction(str);
    std::cerr << "\n   ";
    for (size_t i = 0; i < str.size(); ++i) {
        std::cerr << i << ", ";
    }
    std::cerr << "\n   ";
    for (auto& c : str) {
        std::cerr << c << ", ";
    }
    std::cerr << "\n: [";
    for (auto& iz : z) {
        std::cerr << iz << ", ";
    }
    std::cerr << "]\n\n";
}

void
allTestsZFunction1() {
    testZFunction("abacaba");
    testZFunction("abcdefghij");
    testZFunction("aaaaaaaaa");
    testZFunction("a");
    testZFunction("");
    testZFunction("abababb");
    testZFunction("abcabcabcc");
}

template<
    typename AnswerType
    , typename TestedFunc
    , typename... Args
    >
void
testSmth(
    AnswerType rightAnswer
    , TestedFunc func
    , Args&... args
) {
    auto answer = func(args...);
    if (rightAnswer != answer) {
        throw utException("[testSmth]")
            << " function" << utException::argsToString(args...)
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
}

void
testsZFunction() {
    testSmth(
        std::vector<size_t>{7, 0, 1, 0, 3, 0, 1, },
        zFunction,
        "abacaba"
    );
    testSmth(
        std::vector<size_t>{10, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
        zFunction,
        "abcdefghij"
    );
    testSmth(
        std::vector<size_t>{9, 8, 7, 6, 5, 4, 3, 2, 1, },
        zFunction,
        "aaaaaaaaa"
    );
    testSmth(
        std::vector<size_t>{1, },
        zFunction,
        "a"
    );
    testSmth(
        std::vector<size_t>{},
        zFunction,
        ""
    );
    testSmth(
        std::vector<size_t>{7, 0, 4, 0, 2, 0, 0, },
        zFunction,
        "abababb"
    );
    testSmth(
        std::vector<size_t>{10, 0, 0, 6, 0, 0, 3, 0, 0, 0, },
        zFunction,
        "abcabcabcc"
    );
}

void
testZFunctionFind() {
    testSmth(
        std::vector<size_t>{2,},
        zFunctionPatternMatch,
        "must", "I must not fear."
    );
    testSmth(
        std::vector<size_t>{12,},
        zFunctionPatternMatch,
        "mind", "Fear is the mind-killer."
    );
    testSmth(
        std::vector<size_t>{0,},
        zFunctionPatternMatch,
        "Fear", "Fear is the little-death that brings total obliteration."
    );
    testSmth(
        std::vector<size_t>{15,},
        zFunctionPatternMatch,
        "fear.", "I will face my fear."
    );
    testSmth(
        std::vector<size_t>{30, 45},
        zFunctionPatternMatch,
        "me", "I will permit it to pass over me and through me."
    );
    testSmth(
        std::vector<size_t>{},
        zFunctionPatternMatch,
        "When", "And when it has gone past I will turn the inner eye to see its path."
    );
    testSmth(
        std::vector<size_t>{},
        zFunctionPatternMatch,
        "pain", "Where the fear has gone there will be nothing."
    );
    testSmth(
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
