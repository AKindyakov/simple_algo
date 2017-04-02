#include "../simple_algo_util/simple_exception.h"

#include <memory>
#include <iostream>

class IElement {
public:
    virtual void push(std::string) = 0;
};

class Echo
    : public IElement
{
public:
    explicit Echo(
        std::unique_ptr<IElement> next_
        , std::string text_
    );

    void push(std::string prefix) override;

private:
    std::unique_ptr<IElement> next;
    std::string text;
};

class Save
    : public IElement
{
public:
    explicit Save(
        std::vector<std::string>& dest_
    );

    void push(std::string prefix) override;

private:
    std::vector<std::string>& dest;
};

class Range
    : public IElement
{
public:
    explicit Range(
        std::unique_ptr<IElement> next_
        , int from_
        , int to_
    );

    void push(std::string prefix) override;

private:
    std::unique_ptr<IElement> next;
    int from;
    int to;
};

std::vector<std::string> BraceExpansion(std::string exp);

