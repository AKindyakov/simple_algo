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

static const auto SeqDelimiter = std::string("..");
static const auto LeftBrace = std::string("{");
static const auto RightBrace = std::string("}");

std::vector<std::string> BraceExpansion(std::string exp) {
    auto expanded = std::vector<std::string>{};
    std::unique_ptr<IElement> head = std::make_unique<Save>(expanded);
    size_t pos = exp.size();
    while (pos != std::string::npos) {
        auto right = exp.rfind(RightBrace, pos);
        if (right == std::string::npos) {
            head = std::make_unique<Echo>(
                std::move(head),
                exp.substr(0, pos)
            );
            break;
        }
        if (right < pos) {
            head = std::make_unique<Echo>(
                std::move(head),
                exp.substr(
                    right + RightBrace.size(),
                    pos - right - RightBrace.size()
                )
            );
        }
        auto delim = exp.rfind(SeqDelimiter, right);
        if (delim == std::string::npos) {
            throw TSimpleException() << "Wrong sequence";
        }
        auto left = exp.rfind(LeftBrace, delim);
        if (left == std::string::npos) {
            throw TSimpleException() << "Wrong sequence";
        }
        auto from = exp.substr(
            left + LeftBrace.size(),
            delim - left - LeftBrace.size()
        );
        auto to = exp.substr(
            delim + SeqDelimiter.size(),
            right - delim - SeqDelimiter.size()
        );
        head = std::make_unique<Range>(
            std::move(head),
            std::stoi(from),
            std::stoi(to)
        );
        pos = left;
    }
    head->push(std::string{});
    return expanded;
}
