#include "expansion.h"


Echo::Echo(
    std::unique_ptr<IElement> next_
    , std::string text_
)
    : next(std::move(next_))
    , text(std::move(text_))
{
}

void Echo::push(std::string prefix) {
    prefix += text;
    next->push(std::move(prefix));
}

Save::Save(
    std::vector<std::string>& dest_
)
    : dest(dest_)
{
}

void Save::push(std::string prefix) {
    dest.push_back(std::move(prefix));
}

Range::Range(
    std::unique_ptr<IElement> next_
    , int from_
    , int to_
)
    : next(std::move(next_))
    , from(from_)
    , to(to_)
{
}

void Range::push(std::string prefix) {
    for (int n = from; n <= to; ++n) {
        next->push(prefix + std::to_string(n));
    }
}

std::vector<std::string> BraceExpansion(std::string exp) {
    auto expanded = std::vector<std::string>{};
    std::unique_ptr<IElement> head = std::make_unique<Save>(expanded);
    if (exp.empty()) {
        return expanded;
    }
    size_t pos = exp.size();
    while (pos != std::string::npos) {
        auto right = exp.rfind('}', pos);
        if (right == std::string::npos) {
            head = std::make_unique<Echo>(
                std::move(head),
                exp.substr(0, pos)
            );
            break;
        }
        if (pos > right) {
            head = std::make_unique<Echo>(
                std::move(head),
                exp.substr(right + 1, pos - right - 1)
            );
        }
        auto coma = exp.rfind(',', right);
        if (coma == std::string::npos) {
            throw TSimpleException();
        }
        auto left = exp.rfind('{', coma);
        if (left == std::string::npos) {
            throw TSimpleException();
        }
        auto from = exp.substr(left + 1, coma - left - 1);
        auto to = exp.substr(coma + 1, right - coma - 1);
        head = std::make_unique<Range>(
            std::move(head),
            std::stoi(from),
            std::stoi(to)
        );
        pos = left;
    }
    head->push("");
    return expanded;
}
