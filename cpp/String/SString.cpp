#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <climits>

#include "SString.h"

SString::size_type SString::min_alloc_size = 0xFF;

void SString::re_reserve(size_type new_size) {
    if (new_size > maxsize()) {
        new_size = maxsize();
    }
    if (new_size != m_allocated) {
        char* newpt = new char[new_size];
        m_allocated = new_size;
        strcpy(newpt, m_cstring);
        delete[] m_cstring;
        m_cstring = newpt;
    }
}

SString::SString()
        : m_lenght(0)
        , m_allocated(255) {
    m_cstring = new char[m_allocated];
    *m_cstring = 0;
}

SString::SString( const SString& sstr )
        : m_lenght( sstr.lenght() )
        , m_allocated( sstr.lenght() + min_alloc_size ) {
    m_cstring = new char[m_allocated];
    strcpy(m_cstring, sstr.m_cstring);
}

SString::SString( const char* cstr )
        : m_lenght( strlen(cstr) )
        , m_allocated( m_lenght + min_alloc_size ) {
    m_cstring = new char[m_allocated];
    strcpy(m_cstring, cstr);
}

SString::SString( size_type n, char ch )
        : m_lenght(n)
        , m_allocated( n + min_alloc_size ) {
    m_cstring = new char[m_allocated];
    memset(m_cstring, ch, n);
    m_cstring[n] = 0;
}

SString::SString( const SString& tstr, size_type start, size_type len ) {
    if( start >= tstr.m_lenght ) {
        throw std::out_of_range("SString::substr error, start must low then lenght");
    }
    const char* spt = tstr.m_cstring+start;
    if( start + len > tstr.m_lenght ) {
        len = tstr.m_lenght-start;
    }
    m_lenght = len;
    m_allocated = m_lenght + min_alloc_size;
    m_cstring = new char[m_allocated];
    strncpy(m_cstring, spt, len);
}

SString::~SString () {
    delete[] m_cstring;
}

SString::size_type SString::lenght()const {
    return m_lenght;
}

SString::size_type SString::capacity()const {
    return m_allocated;
}

SString::size_type SString::maxsize()const {
    return UINT_MAX-1;
}

void SString::resize( size_type n ) {
    resize(n, 0);
}

void SString::resize( size_type n, char ch ) {
    if( n > m_allocated ) {
        re_reserve(n + m_allocated);
    }
    size_type of = m_lenght;
    if( n+1 > m_lenght ) {
        memset( m_cstring + m_lenght, ch, n - m_lenght );
    }
    m_lenght = n;
    m_cstring[m_lenght] = 0;
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

const char& SString::at( size_type p )const {
    return at(p);
}

char& SString::at( size_type p ) {
    if( p >= m_lenght ) {
        throw std::out_of_range("SString::substr error, start must low then lenght");
    }
    return m_cstring[p];
}

const char* SString::cstr()const {
    return static_cast<const char*>(m_cstring);
}

SString SString::substr( size_type start, size_type len )const {
    return SString( *this, start, len );
}

void SString::append( const SString& ss ) {
    char* of = &m_cstring[m_lenght];
    size_type n = ss.m_lenght + m_lenght;
    resize( n );
    strcpy( of, ss.m_cstring );
}

void SString::append( const char* cs ) {
    char* of = &m_cstring[m_lenght];
    size_type n = strlen(cs) + m_lenght;
    resize( n );      // <- not optimal
    strcpy( of, cs );
}

void SString::append( size_type n, char ch ) {
    resize( m_lenght+n, ch );
}

void SString::push_back ( char ch ) {
    resize( m_lenght+1, ch );
}

char SString::pop_back() {
    char ret = this->at(m_lenght-1);
    resize( m_lenght-1 );
    return ret;
}

void SString::assign( const SString& ss ) {
    m_lenght = ss.lenght();
    resize( m_lenght ); // <- not optimal
    strcpy(m_cstring, ss.cstr());
}

void SString::assign( const char* cs ) {
    resize( strlen(cs) ); // <- not optimal
    strcpy( m_cstring, cs );
}

void SString::assign( char ch ) {
    clear();
    push_back(ch);
}

int SString::compare( const SString& ss )const {
    strcmp(m_cstring, ss.m_cstring);
}

int SString::compare( const char* cs)const {
    strcmp(m_cstring, cs);
}

SString& SString::operator= ( const SString& ss ) {
    assign( ss );
}

SString& SString::operator= ( const char* cs ) {
    assign( cs );
}

SString& SString::operator= ( char ch ) {
    assign( ch );
}

SString operator+( const SString& ss1, const SString& ss2 ) {
    SString rezSS(ss1);
    rezSS.append(ss2);
    return rezSS;
}

SString operator+( const char* cs1, const SString& ss2 ) {
    SString rezSS(cs1);
    rezSS.append(ss2);
    return rezSS;
}

SString operator+( const SString& ss1, const char* cs2 ) {
    SString rezSS(ss1);
    rezSS.append(cs2);
    return rezSS;
}

SString& SString::operator+=( const SString& ss ) {
    this->append(ss);
    return *this;
}

SString& SString::operator+=( const char* cs ) {
    this->append(cs);
    return *this;
}

SString& SString::operator+=( char ch ) {
    this->push_back(ch);
    return *this;
}

bool operator==( const SString& ss1, const SString& ss2 ) {
    return 0 == strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator==( const char* cs, const SString& ss ) {
    return 0 == strcmp( cs, ss.m_cstring );
}

bool operator==( const SString& ss, const char* cs ) {
    return 0 == strcmp( cs, ss.m_cstring );
}

bool operator!=( const SString& ss1, const SString& ss2 ) {
    return 0 != strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator!=( const char* cs, const SString& ss ) {
    return 0 != strcmp( cs, ss.m_cstring );
}

bool operator!=( const SString& ss, const char* cs ) {
    return 0 != strcmp( cs, ss.m_cstring );
}

bool operator<( const SString& ss1, const SString& ss2 ) {
    return 0 < strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator<( const char* cs, const SString& ss ) {
    return 0 < strcmp( cs, ss.m_cstring );
}

bool operator<( const SString& ss, const char* cs ) {
    return 0 > strcmp( cs, ss.m_cstring );
}

bool operator<=( const SString& ss1, const SString& ss2) {
    return 0 <= strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator<=( const char* cs, const SString& ss ) {
    return 0 <= strcmp( cs, ss.m_cstring );
}

bool operator<=( const SString& ss, const char* cs ){
    return 0 >= strcmp( cs, ss.m_cstring );
}

bool operator>( const SString& ss1, const SString& ss2 ) {
    return 0 > strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator>( const char* cs, const SString& ss ) {
    return 0 > strcmp( cs, ss.m_cstring );
}

bool operator>( const SString& ss, const char* cs ) {
    return 0 < strcmp( cs, ss.m_cstring );
}

bool operator>=( const SString& ss1, const SString& ss2 ) {
    return 0 >= strcmp( ss1.m_cstring, ss2.m_cstring );
}

bool operator>=( const char* cs, const SString& ss ) {
    return 0 >= strcmp( cs, ss.m_cstring );
}

bool operator>=( const SString& ss, const char* cs ) {
    return 0 <= strcmp( cs, ss.m_cstring );
}

std::ostream& operator<<( std::ostream& os, const SString& ss) {
    os << ss.m_cstring;
    return os;
}

std::istream& operator>>( std::istream& is, SString& ss) {
    ss.clear();
    char ch = is.get();
    while( ch != ' ' && ch != '\n' && ch != EOF ) {
        ss.push_back(ch);
        ch = is.get();
    }
}

