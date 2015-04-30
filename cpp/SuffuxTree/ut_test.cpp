#include "fuzzy_search.h"
#include "tree.h"

#include "../SimpleAlgoUtil/simple_exception.h"
#include "../SimpleAlgoUtil/unit_test.h"

#include <exception>
#include <iostream>
#include <vector>
#include <unordered_set>

void
mississippiTest() {
    std::string str = "mississippi";
    std::string rightAnswer =
        "[0:0] \n"
        "  ---> \n"
        "  -(`): [11:12] `\n"
        "  -(i): [1:2] i\n"
        "    ---> \n"
        "    -(`): [11:12] `\n"
        "    -(p): [8:12] ppi`\n"
        "    -(s): [2:5] ssi\n"
        "      ---> si\n"
        "      -(p): [8:12] ppi`\n"
        "      -(s): [5:12] ssippi`\n"
        "  -(m): [0:12] mississippi`\n"
        "  -(p): [8:9] p\n"
        "    ---> \n"
        "    -(i): [10:12] i`\n"
        "    -(p): [9:12] pi`\n"
        "  -(s): [2:3] s\n"
        "    ---> \n"
        "    -(i): [4:5] i\n"
        "      ---> i\n"
        "      -(p): [8:12] ppi`\n"
        "      -(s): [5:12] ssippi`\n"
        "    -(s): [3:5] si\n"
        "      ---> i\n"
        "      -(p): [8:12] ppi`\n"
        "      -(s): [5:12] ssippi`\n"
    ;
    TSuffixTreeBase stree(str);
    std::stringstream out;
    stree.show(out);
    std::string answer = out.str();
    if (rightAnswer != answer) {
        throw TSimpleException("[mississippi test]")
            << " Wrong answer: " << answer
            << " Expected: " << rightAnswer;
    }
}

void
fuzzySearchTest() {
    //                     0
    TFuzzySearch searcher("thisitemletsyoutestyourstandardalgorithmskills", '?');
    std::vector<TFuzzySearch::TSubstring> rez = searcher.search("l?");
    std::unordered_set<size_t> rightAnswerStarts = {10, 39, 51, 52};
    std::unordered_set<std::string> rightAnswerStrs = {"le", "lg", "ll", "ls"};

    std::unordered_set<size_t> starts;
    std::unordered_set<std::string> strs;
    for (const auto& r : rez) {
        starts.insert(r.start);
        strs.insert(r.copy());
    }
    if (strs != rightAnswerStrs) {
        throw TSimpleException("wrong string answer");
    }
    if (starts != rightAnswerStarts) {
        throw TSimpleException("wrong position answer");
    }
}

int main(int /*argn*/, const char** /*args*/) {
    try {
        mississippiTest();
        fuzzySearchTest();
    }
    catch(const TSimpleException& e) {
        std::cerr
            << "TSimpleException error "
            << e.what() << '\n';
        return 1;
    }
    catch(const std::exception& e) {
        std::cerr
            << "Std error "
            << e.what() << '\n';
        return 2;
    }
    catch(...) {
        std::cerr << "Unexpected error";
        return 3;
    }
    return 0;
}
