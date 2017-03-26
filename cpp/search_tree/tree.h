#pragma once

#include <exception>
#include <string>

class KeyError:
    public std::exception
{
private:
    std::string message;

public:
    KeyError() {}
    KeyError(std::string msg)
        : message(msg)
    {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class NotImplementedError:
    public std::exception
{
private:
    std::string message;

public:
    NotImplementedError() {}
    NotImplementedError(std::string msg)
        : message(msg)
    {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ITree {
public:
    virtual void insert(const std::string& str) = 0;
    virtual void remove(const std::string& str) = 0;
    virtual void assign(const std::string& str) = 0;
    virtual bool has(const std::string& str) = 0;
};

