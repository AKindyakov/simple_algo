#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <climits>

#include "SString.h"

const SString::size_type SString::min_alloc_size = 0xFF;

SString::SString() {
    memrealloc(min_alloc_size);
}

SString::SString(const SString& sstr) {
    assign(sstr);
}

SString::SString(const char* cstr) {
    assign(cstr);
}

SString::SString(size_type n, char ch) {
    resize(n, ch);
}

SString::SString(const SString& tstr, size_type start, size_type len) {
    if (start >= tstr.m_lenght) {
        throw std::out_of_range("SString::substr error, start must low then lenght");
    }
    const char* spt = tstr.m_cstring+start;
    if (start + len > tstr.m_lenght) {
        len = tstr.m_lenght-start;
    }
    resize(len);
    strncpy(m_cstring, spt, len);
}

SString::~SString() {
    delete[] m_cstring;
}

SString::size_type SString::lenght()const {
    return m_lenght;
}

SString::size_type SString::capacity()const {
    return m_allocated;
}

SString::size_type SString::maxsize()const {
    return UINT_MAX - 1;
}

void SString::resize(size_type n) {
    resize(n, 0);
}

void SString::memrealloc(size_type new_alloc) {
    if (new_alloc > maxsize()) {
        new_alloc = maxsize();
    }
    if (new_alloc != m_allocated) {
        m_allocated = new_alloc;
        char* newpt = new char[m_allocated];
        if (m_cstring != nullptr) {
            strcpy(newpt, m_cstring);
            delete[] m_cstring;
        }
        m_cstring = newpt;
    }
}

void SString::resize(size_type new_size, char ch) {
    if (new_size > maxsize()) {
        new_size = maxsize();
    }
    if (new_size > m_allocated) {
        memrealloc(m_allocated + new_size);
    }
    if (new_size > m_lenght) {
        memset(m_cstring + m_lenght, ch, new_size - m_lenght);
    }
    m_lenght = new_size;
    m_cstring[m_lenght] = 0;
}

void SString::shrink_to_fit() {
    memrealloc(m_lenght);
}

void SString::clear() {
    resize(0);
}

bool SString::empty()const {
    return m_lenght == 0;
}

SString::operator bool()const {
    return m_lenght != 0;
}

const char& SString::at(size_type pos)const {
    if (pos >= m_lenght) {
        throw std::out_of_range("SString::at error");
    }
    return m_cstring[pos];
}

char& SString::at(size_type pos) {
    if (pos >= m_lenght) {
        throw std::out_of_range("SString::at error");
    }
    return m_cstring[pos];
}

const char& SString::operator[](size_type pos)const {
    return m_cstring[pos];
}

char& SString::operator[](size_type pos) {
    return m_cstring[pos];
}

const char* SString::cstr()const {
    return static_cast<const char*>(m_cstring);
}

SString SString::substr(size_type start, size_type len)const {
    return SString(*this, start, len);
}

void SString::append(const SString& ss) {
    char* oldStartPt = &m_cstring[m_lenght];
    resize(ss.m_lenght + m_lenght);
    strcpy(oldStartPt, ss.m_cstring);
}

void SString::append(const char* cs) {
    char* oldStartPt = &m_cstring[m_lenght];
    resize(strlen(cs) + m_lenght);
    strcpy(oldStartPt, cs);
}

void SString::append(size_type n, char ch) {
    resize(m_lenght + n, ch);
}

void SString::push_back (char ch) {
    resize(m_lenght + 1, ch);
}

char SString::pop_back() {
    char ret = at(m_lenght - 1);
    resize(m_lenght - 1);
    return ret;
}

void SString::assign(const SString& ss) {
    resize(ss.lenght());
    strcpy(m_cstring, ss.cstr());
}

void SString::assign(const char* cs) {
    resize(strlen(cs));
    strcpy(m_cstring, cs);
}

void SString::assign(char ch) {
    clear();
    push_back(ch);
}

int SString::compare(const SString& ss)const {
    strcmp(m_cstring, ss.m_cstring);
}

int SString::compare(const char* cs)const {
    strcmp(m_cstring, cs);
}

SString& SString::operator= (const SString& ss) {
    assign(ss);
}

SString& SString::operator= (const char* cs) {
    assign(cs);
}

SString& SString::operator= (char ch) {
    assign(ch);
}

SString operator+(const SString& ss1, const SString& ss2) {
    SString rezSS(ss1);
    rezSS.append(ss2);
    return rezSS;
}

SString operator+(const char* cs1, const SString& ss2) {
    SString rezSS(cs1);
    rezSS.append(ss2);
    return rezSS;
}

SString operator+(const SString& ss1, const char* cs2) {
    SString rezSS(ss1);
    rezSS.append(cs2);
    return rezSS;
}

SString& SString::operator+=(const SString& ss) {
    append(ss);
    return *this;
}

SString& SString::operator+=(const char* cs) {
    append(cs);
    return *this;
}

SString& SString::operator+=(char ch) {
    push_back(ch);
    return *this;
}

bool operator==(const SString& ss1, const SString& ss2) {
    return 0 == ss1.compare(ss2);
}

bool operator==(const char* cs, const SString& ss) {
    return 0 == ss.compare(cs);
}

bool operator==(const SString& ss, const char* cs) {
    return 0 == ss.compare(cs);
}

bool operator!=(const SString& ss1, const SString& ss2) {
    return 0 != ss1.compare(ss2);
}

bool operator!=(const char* cs, const SString& ss) {
    return 0 != ss.compare(cs);
}

bool operator!=(const SString& ss, const char* cs) {
    return 0 != ss.compare(cs);
}

bool operator<(const SString& ss1, const SString& ss2) {
    return 0 < ss1.compare(ss2);
}

bool operator<(const char* cs, const SString& ss) {
    return 0 < ss.compare(cs);
}

bool operator<(const SString& ss, const char* cs) {
    return 0 > ss.compare(cs);
}

bool operator<=(const SString& ss1, const SString& ss2) {
    return 0 <= ss1.compare(ss2);
}

bool operator<=(const char* cs, const SString& ss) {
    return 0 <= ss.compare(cs);
}

bool operator<=(const SString& ss, const char* cs){
    return 0 >= ss.compare(cs);
}

bool operator>(const SString& ss1, const SString& ss2) {
    return 0 > ss1.compare(ss2);
}

bool operator>(const char* cs, const SString& ss) {
    return 0 > ss.compare(cs);
}

bool operator>(const SString& ss, const char* cs) {
    return 0 < ss.compare(cs);
}

bool operator>=(const SString& ss1, const SString& ss2) {
    return 0 >= ss1.compare(ss2);
}

bool operator>=(const char* cs, const SString& ss) {
    return 0 >= ss.compare(cs);
}

bool operator>=(const SString& ss, const char* cs) {
    return 0 <= ss.compare(cs);
}

std::ostream& operator<<(std::ostream& os, const SString& ss) {
    os << ss.cstr();
    return os;
}

std::istream& operator>>(std::istream& is, SString& ss) {
    ss.clear();
    char ch = is.get();
    while(ch != ' ' && ch != '\n' && ch != EOF) {
        ss.push_back(ch);
        ch = is.get();
    }
}

